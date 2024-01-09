#include "Player.hpp"
#include "CLua.hpp"


Player::Player()
{
	playerLevel_ = 1;
	playerGrade = 1;
}

void Player::ReadQuest(QuestID questId)
{
	auto quest = CLua::GetQuest(questId);

	std::cout << "questName : " << quest->GetName() << std::endl;
	std::cout << "questDescription : " << quest->GetDescription() << std::endl;

	auto questType = quest->GetType();
	switch (questType)
	{
		case QuestType::Kill:
		{
			std::cout << "questGoal : Kill Monster" << std::endl;
			auto& targetList = quest->GetKillTargetList();

			for (auto& target : targetList) {
				std::string targetName(magic_enum::enum_name<MonsterID>(target.first));
				std::cout << "targetName : " << targetName << std::endl;
				std::cout << "targetAmount : " << target.second.targetAmount << std::endl;
			}
		}
	}

	auto questReward = quest->GetReward();
	std::cout << "questReward - exp : " << questReward.expReward << std::endl;
	std::cout << "questReward - gold : " << questReward.goldReward << std::endl;
	for (auto& item : questReward.itemReward) {
		std::string itemName(magic_enum::enum_name<ItemID>(std::get<0>(item)));
		std::cout << "questReward - Item : " << itemName << "(" << std::get<1>(item) << ")" << std::endl;
	}

	delete(quest);
}

bool Player::AcceptQuest(QuestID questId)
{
	auto result = CLua::CheckAcceptQuest(magic_enum::enum_name<QuestID>(questId).data(), this);

	if (result == true) {
		auto quest = CLua::GetQuest(questId);
		questMap_.emplace(questId, quest);

		std::cout << "Quest Accepted!" << std::endl;
	}
	else {
		std::cout << "Cannot Accept!" << std::endl;
		return false;
	}

	return true;
}

bool Player::ClearQuest(QuestID questId)
{
	auto questPair = questMap_.find(questId);

	if (questPair == questMap_.end()) {
		std::cout << "Not Accepted Quest!" << std::endl;
		return false;
	}

	auto quest = questPair->second;

	auto result = CLua::CheckClearQuest(magic_enum::enum_name<QuestID>(questId).data(), quest);
	if (result == true)	{
		std::cout << "Quest " << quest->GetName() << " Clear!" << std::endl;

		// 보상 지급
		ProvideReward(quest);

		questMap_.erase(questPair);
		delete(quest);	
	}
	else {
		std::cout << "Quest completion conditions have not been met" << std::endl;
		return false;
	}

	return true;
}

void Player::ProvideReward(Quest* quest)
{
	auto reward = quest->GetReward();

	if (reward.expReward != 0) {
		playerExp_ += reward.expReward;
	}

	if (reward.goldReward != 0) {
		playerGold_ += reward.goldReward;
	}

	if (reward.itemReward.empty() == false) {
		// 아이템 추가	
	}
}

void Player::UpdateKillQuestProgress(MonsterID monsterId)
{
	for (auto& questPair : questMap_) {
		auto quest = questPair.second;
		if (quest->GetType() == QuestType::Kill) {
			auto& targetList = quest->GetKillTargetList();

			auto target = targetList.find(monsterId);
			if (target != targetList.end())
			{
				target->second.targetCount++;

				std::cout << target->second.targetCount << std::endl;
			}
		}
	}
}

/// <summary>
/// 
/// </summary>

int Player::GetPlayerLevel()
{
	return playerLevel_;
}

int Player::GetPlayerGrade()
{
	return playerGrade;
}

int Player::GetPlayerExp()
{
	return playerExp_;
}

int Player::GetPlayerGold()
{
	return playerGold_;
}

/// <summary>
/// 
/// </summary>

void Player::SetPlayerLevel(int level)
{
	playerLevel_ = level;
}

void Player::SetPlayerGrade(int level)
{
	playerGrade = level;
}

void Player::SetPlayerExp(int exp)
{
	playerExp_ = exp;
}

void Player::SetPlayerGold(int gold)
{
	playerGold_ = gold;
}