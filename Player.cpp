#include "Player.hpp"
#include "CLua.hpp"
#include "Quest.hpp"
#include "Monster.hpp"
#include "BattleEvent.hpp"

Player::Player()
{
	playerLevel_ = 1;
	playerGrade = 1;
}

bool Player::CheckPlayerAlive()
{
	return (playerHP_ > 0);
}

/// <summary>
/// 
/// </summary>

void Player::ReadQuest(int questId)
{
	auto quest = CLua::GetQuest(questId);

	std::cout << "==================================" << std::endl;
	std::cout << "[" << quest.GetName() << "]" << std::endl;
	std::cout << "	" << quest.GetDescription() << std::endl;
	std::cout << std::endl;

	auto questType = quest.GetType();

	std::cout << "퀘스트 목표" << std::endl;
	auto& targetList = quest.GetKillTargetList();
	if (targetList.empty() == false) {
		for (auto& target : targetList) {
			std::cout << "	" << CLua::GetMonsterName(target.first) << " : " << target.second.targetAmount << std::endl;
		}
		std::cout << std::endl;
	}

	auto questReward = quest.GetReward();
	std::cout << "퀘스트 보상" << std::endl;
	std::cout << "	exp : " << questReward.expReward << std::endl;
	std::cout << "	gold : " << questReward.goldReward << std::endl;
	std::cout << "	item : ";
	for (auto& item : questReward.itemReward) {
		std::cout << CLua::GetItemName(std::get<0>(item)) << "(" << std::get<1>(item) << ") ";
	}
	std::cout << std::endl << "==================================" << std::endl;
}

bool Player::AcceptQuest(int questId)
{
	auto result = CLua::CheckAcceptQuest(questId, this);

	if (result == true) {
		auto quest = new Quest(CLua::GetQuest(questId));

		questMap_.emplace(questId, quest);

		std::cout << "Quest Accepted!" << std::endl;
	}
	else {
		std::cout << "Cannot Accept!" << std::endl;
		return false;
	}

	return true;
}

bool Player::ClearQuest(int questId)
{
	auto questPair = questMap_.find(questId);
	if (questPair == questMap_.end()) {
		std::cout << "Not Accepted Quest!" << std::endl;
		return false;
	}

	auto quest = questPair->second;
	auto result = CLua::CheckClearQuest(questId, this, quest);
	if (result == false) {
		std::cout << "Quest completion conditions have not been met" << std::endl;
		return false;
	}

	std::cout << "Quest " << quest->GetName() << " Clear!" << std::endl;

	// 보상 지급
	ProvideReward(quest);

	questMap_.erase(questPair);
	delete(quest);	

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

void Player::UpdateKillQuestProgress(int monsterId)
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

void Player::DecreaseHP(int damage)
{
	playerHP_ -= damage;
}

bool Player::HandleBattleEvent(BattleEvent& battleEvent)
{
	auto event = battleEvent.GetEvent();
	switch (event)
	{
		case BATTLE_EVENT::MonsterDead:
		{
			CLua::ProvideBattleReward(this, monster_);
			UpdateKillQuestProgress(monster_->GetMonsterID());
			break;
		}
		case BATTLE_EVENT::PlayerDead:
		{
			std::cout << "Player Win!" << std::endl;
			break;
		}
		case BATTLE_EVENT::MonsterRun:
		{
			std::cout << "Monster Run!" << std::endl;
			break;
		}
		case BATTLE_EVENT::PlayerRun:
		{
			std::cout << "Player Run!" << std::endl;
			break;
		}
	}

	return (event != BATTLE_EVENT::None);
}

void Player::BattlePlayerTurn(BattleEvent& event)
{

}

void Player::ProcessBattle()
{
	BattleEvent event;

	while (monster_->CheckMonsterAlive() && CheckPlayerAlive()) {
		auto isPlayerFirst = CLua::CheckBattleTurn(this, monster_);

		if (isPlayerFirst == false) {
			CLua::BattleMonsterTurn(this, monster_, event);
			if (HandleBattleEvent(event)) {
				break;
			}
			BattlePlayerTurn(event);
			if (HandleBattleEvent(event)) {
				break;
			}
		}
		else {
			BattlePlayerTurn(event);
			if (HandleBattleEvent(event)) {
				break;
			}
			CLua::BattleMonsterTurn(this, monster_, event);
			if (HandleBattleEvent(event)) {
				break;
			}
		}
	}
}

void Player::StartBattle(int monsterId)
{
	auto monster = new Monster(CLua::GetMonster(monsterId));
	monster_ = monster;

	CLua::InitBattle(this, monster);

	ProcessBattle();
}


/// <summary>
/// 
/// </summary>

int Player::GetLevel()
{
	return playerLevel_;
}

int Player::GetGrade()
{
	return playerGrade;
}

int Player::GetExp()
{
	return playerExp_;
}

int Player::GetGold()
{
	return playerGold_;
}

int Player::GetSpeed()
{
	return playerSpeed_;
}

int Player::GetAtk()
{
	return playerAtk_;
}

int Player::GetDef()
{
	return playerDef_;
}

int Player::GetHP()
{
	return playerHP_;
}

int Player::GetMP()
{
	return playerMP_;
}


/// <summary>
/// 
/// </summary>

void Player::SetLevel(int level)
{
	playerLevel_ = level;
}

void Player::SetGrade(int level)
{
	playerGrade = level;
}

void Player::SetExp(int exp)
{
	playerExp_ = exp;
}

void Player::SetGold(int gold)
{
	playerGold_ = gold;
}

void Player::SetSpeed(int speed)
{
	playerSpeed_ = speed;
}

void Player::SetAtk(int atk)
{
	playerAtk_ = atk;
}

void Player::SetDef(int def)
{
	playerDef_ = def;
}

void Player::SetHp(int hp)
{
	playerHP_ = hp;
}

void Player::SetMp(int mp)
{
	playerMP_ = mp;
}