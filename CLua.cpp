#include "CLua.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Quest.hpp"
#include "BattleEvent.hpp"

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
			"DecreaseHP", &Player::DecreaseHP,

			"GetLevel", &Player::GetLevel,
			"GetGrade", &Player::GetGrade,
			"GetHP", &Player::GetHP,
			"GetMP", &Player::GetMP,
			"GetSpeed", &Player::GetSpeed,
			"GetAtk", &Player::GetAtk,
			"GetDef", &Player::GetDef,
			"GetExp", &Player::GetExp,
			"GetGold", &Player::GetGold,
			
			"SetLevel", &Player::SetLevel,
			"SetGrade", &Player::SetGrade,
			"SetHP", &Player::SetHp,
			"SetMP", &Player::SetMp,
			"SetSpeed", &Player::SetSpeed,
			"SetAtk", &Player::SetAtk,
			"SetDef", &Player::SetDef,
			"SetExp", &Player::SetExp,
			"SetGold", &Player::SetGold
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

		lua.new_usertype<Monster>("Monster"
			/*"CheckMonsterAlive", &Monster::CheckMonsterAlive,
			"Attack", &Monster::Attack,
			"Guard", &Monster::Guard,
			"TryRun", &Monster::TryRun,

			"GetMonsterID", &Monster::GetMonsterID,
			"GetName", &Monster::GetName,
			"GetState", &Monster::GetState,
			"GetSpeed", &Monster::GetSpeed,
			"GetAttack", &Monster::GetAttack,
			"GetDefense", &Monster::GetDefense,
			"GetHP", &Monster::GetHP,
			"GetMP", &Monster::GetMP,
			"GetName", &Monster::GetName,

			"SetMonsterID", &Monster::SetMonsterID,
			"SetName", &Monster::SetName,
			"SetState", &Monster::SetState,
			"SetSpeed", &Monster::SetSpeed,
			"SetAttack", &Monster::SetAttack,
			"SetDefense", &Monster::SetDefense,
			"SetHP", &Monster::SetHP,
			"SetMP", &Monster::SetMP,
			"SetName", &Monster::SetName*/
		);

		lua.new_usertype<BattleEvent>("BattleEvent",
			"GetEvent", &BattleEvent::GetEvent,
			"SetEvent", &BattleEvent::SetEvent,
			"MonsterDead", &BattleEvent::MonsterDead,
			"PlayerDead", &BattleEvent::PlayerDead,
			"MonsterRun", &BattleEvent::MonsterRun,
			"PlayerRun", &BattleEvent::PlayerRun
		);
	}

	void CLua::RegisterScripts()
	{
		for (const auto& entry : std::filesystem::directory_iterator("./scripts/Base/")) {
			if (entry.path().extension() == ".lua") {
				std::cout << entry.path().string() << std::endl;
				lua.safe_script_file(entry.path().string());
			}
		}

		for (const auto& entry : std::filesystem:: recursive_directory_iterator("./scripts/")) {
			if (entry.path().extension() == ".lua" && entry.path().parent_path() != "./scripts/Base") {
				std::cout << entry.path().string() <<  std::endl;
				lua.safe_script_file(entry.path().string());
			}
		}
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
					std::this_thread::sleep_for(std::chrono::seconds(1));
					lua.safe_script_file(ev.path_name.string());
				}
			}
		);

		while (true) {
			//std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	Quest CLua::GetQuest(int questId)
	{	
		auto questName = GetQuestName(questId);
		Quest quest(questId, questName);

		quest.SetDescription(lua[questName]["description"]);

		int questRarity = lua[questName]["rarity"];
		quest.SetRarity(static_cast<QuestRarity>(questRarity));

		int questType = lua[questName]["type"];
		quest.SetType(static_cast<QuestType>(questType));

		if (questType == lua["quest"]["type"]["Kill"])
		{
			std::map<int, QuestKillTarget> questTargetList;
			sol::table targets = lua[questName]["killTarget"];
			for (auto& target : targets)
			{
				sol::table targetInfo = target.second.as<sol::table>();

				QuestKillTarget questTarget;
				questTarget.targetAmount = targetInfo["amount"];
				auto targetId = targetInfo["id"];

				questTargetList.emplace(targetId, questTarget);
			}
			quest.SetKillTargetList(questTargetList);
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
		quest.SetReward(questReward);

		return quest;
	}

	bool CLua::CheckAcceptQuest(int questId, Player* player)
	{
		sol::function CheckAcceptQuest;

		CheckAcceptQuest = lua[GetQuestName(questId)]["checkAcceptQuest"];

		auto result = CheckAcceptQuest(player);

		return result;
	}

	bool CLua::CheckClearQuest(int questId, Player* player, Quest* quest)
	{
		sol::function CheckClearQuest;

		CheckClearQuest = lua[GetQuestName(questId)]["checkClearQuest"];

		auto result = CheckClearQuest(player, quest);

		return result;
	}

	/// <summary>
	/// 
	/// </summary>

	Monster CLua::GetMonster(int monsterId)
	{
		auto monsterName = GetMonsterName(monsterId);
		Monster monster(monsterId, monsterName);

		monster.SetSpeed(lua[monsterName]["speed"]);
		monster.SetAttack(lua[monsterName]["attack"]);
		monster.SetDefense(lua[monsterName]["defense"]);
		monster.SetHP(lua[monsterName]["hp"]);
		monster.SetMP(lua[monsterName]["mp"]);

		return monster;
	}

	void CLua::InitBattle(Player* player, Monster* monster)
	{
		sol::function InitBattle;

		InitBattle = lua[monster->GetName()]["initBattle"];

		InitBattle(player, monster);
	}

	bool CLua::CheckBattleTurn(Player* player, Monster* monster)
	{
		sol::function CheckBattleTurn;

		CheckBattleTurn = lua[monster->GetName()]["checkBattleTurn"];

		auto result = CheckBattleTurn(player, monster);

		return result;
	}

	void CLua::BattleMonsterTurn(Player* player, Monster* monster, BattleEvent& event)
	{
		sol::function BattleMonsterTurn;

		BattleMonsterTurn = lua[monster->GetName()]["battleMonsterTurn"];

		BattleMonsterTurn(player, monster, event);
	}

	void CLua::ProvideBattleReward(Player* player, Monster* monster)
	{
		sol::function ProvideBattleReward;

		ProvideBattleReward = lua[monster->GetName()]["provideBattleReward"];

		ProvideBattleReward(player);

	}


	/// <summary>
	/// 
	/// </summary>

	int CLua::GetQuestID(std::string questName)
	{
		auto questId = lua["quest"]["id"][questName];

		if (questId.valid() == false) {
			return -1;
		}

		return questId.get<int>();
	}

	int CLua::GetMonsterID(std::string monsterName)
	{
		auto monsterId = lua["monster"]["id"][monsterName];

		if (monsterId.valid() == false) {
			return -1;
		}

		return monsterId.get<int>();
	}

	std::string CLua::GetQuestName(int questId)
	{
		sol::table questIdTable = lua["quest"]["id"];

		for (auto& pair : questIdTable) {
			int id = pair.second.as<int>();
			if (id == questId) {
				return pair.first.as<std::string>();
			}
		}

		throw std::exception("Quest not found");
	}

	std::string CLua::GetMonsterName(int monsterId)
	{
		sol::table monsterIdTable = lua["monster"]["id"];

		for (auto& pair : monsterIdTable) {
			int id = pair.second.as<int>();
			if (id == monsterId) {
				return pair.first.as<std::string>();
			}
		}

		throw std::exception("Monster not found");
	}

	std::string CLua::GetItemName(int itemId)
	{
		sol::table itemIdTable = lua["item"]["id"];

		for (auto& pair : itemIdTable) {
			int id = pair.second.as<int>();
			if (id == itemId) {
				return pair.first.as<std::string>();
			}
		}

		throw std::exception("Item not found");
	}
}