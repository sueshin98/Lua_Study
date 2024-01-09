#include "CLua.hpp"

namespace CLua
{
	sol::state lua;

	void CLua::Init()
	{
		lua.open_libraries();
	}

	void CLua::RegisterClass()
	{
		lua.new_usertype<Player>("Player",
			"GetPlayerLevel", &Player::GetPlayerLevel,
			"SetPlayerLevel", &Player::SetPlayerLevel,
			"GetPlayerGrade", &Player::GetPlayerGrade,
			"SetPlayerGrade", &Player::SetPlayerGrade
		);

		lua.new_usertype<Quest>("Quest",
			"CheckKillTarget", &Quest::CheckKillTarget,
			"GetQuestID", &Quest::GetQuestID,
			"GetType", &Quest::GetType,
			"GetKillTargetList", &Quest::GetKillTargetList,
			"GetName", &Quest::GetName,
			"GetDescription", &Quest::GetDescription,
			"SetQuestID", &Quest::SetQuestID,
			"SetType", &Quest::SetType,
			"SetKillTargetList", &Quest::SetKillTargetList,
			"SetName", &Quest::SetName,
			"SetDescription", &Quest::SetDescription
		);
	}

	void CLua::RegisterScripts()
	{
		lua.script_file("scripts/monster.lua");
		lua.script_file("scripts/item.lua");
		lua.script_file("scripts/quest1.lua");
	}

	void CLua::RunScript(std::string fileName)
	{
		lua.script_file(fileName);
	}

	void CLua::EnalbeFileWatcher()
	{
		auto watcher = wtr::watch(
			"./scripts",
			[](wtr::event const& ev)
			{
				if (ev.effect_type == wtr::event::effect_type::modify && ev.path_name.extension() == ".lua") {
					std::cout << "File modified: " << ev.path_name << std::endl;
					lua.safe_script_file(ev.path_name.string());
				}
			}
		);

		while (true) {}
	}

	Quest* CLua::GetQuest(QuestID questId)
	{
		auto questName = magic_enum::enum_name<QuestID>(questId).data();
		
		auto quest = new Quest(questId, questName);

		quest->SetDescription(lua[questName]["description"]);

		std::string questRarityString = lua[questName]["rarity"];
		auto questRarity = magic_enum::enum_cast<QuestRarity>(questRarityString).value();
		quest->SetRarity(questRarity);

		std::string questTypeString = lua[questName]["type"];
		auto questType = magic_enum::enum_cast<QuestType>(questTypeString).value();
		quest->SetType(questType);

		switch (questType)
		{
			case QuestType::Kill:
			{
				std::map<MonsterID, QuestKillTarget> questTargetList;
				sol::table targets = lua[questName]["killTarget"];
				for (auto& target : targets)
				{
					sol::table targetInfo = target.second.as<sol::table>();

					QuestKillTarget questTarget;
					questTarget.targetAmount = targetInfo["amount"];
					auto targetId = targetInfo["id"];

					questTargetList.emplace(targetId, questTarget);
				}
				quest->SetKillTargetList(questTargetList);
			}
			case QuestType::Collect:
			{
			}
		}

		QuestReward questReward;
		auto reward = lua[questName]["reward"];
		if (reward["exp"] != NULL) {
			questReward.expReward = reward["exp"];
		}
		if (reward["gold"] != NULL) {
			questReward.goldReward = reward["gold"];
		}
		if (reward["item"] != NULL) {
			sol::table itemReward = reward["item"];
			for (auto& item : itemReward)
			{
				sol::table itemInfo = item.second.as<sol::table>();
				questReward.itemReward.push_back({ itemInfo["id"], itemInfo["amount"]});
			}
		}
		quest->SetReward(questReward);

		return quest;
	}

	bool CLua::CheckAcceptQuest(const char* questName, Player* player)
	{
		sol::function CheckAcceptQuest;

		CheckAcceptQuest = lua[questName]["checkAcceptQuest"];

		auto result = CheckAcceptQuest(player);

		return result;
	}

	bool CLua::CheckClearQuest(const char* questName, Quest* quest)
	{
		sol::function CheckClearQuest;

		CheckClearQuest = lua[questName]["checkClearQuest"];

		auto result = CheckClearQuest(*quest);

		return result;
	}
}