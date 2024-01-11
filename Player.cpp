#include "Player.hpp"
#include "CLua.hpp"
#include "Quest.hpp"
#include "Monster.hpp"
#include "Field.hpp"
#include "BattleEvent.hpp"

Player::Player()
{
	playerLevel_ = 1;
	playerGrade = 1;
	playerExp_ = 0;
	playerGold_ = 0;
	playerAtk_ = 10;
	playerDef_ = 5;
	playerSpeed_ = 10;
	playerHP_ = 100;
	playerMP_ = 100;
}

bool Player::CheckPlayerAlive()
{
	return (playerHP_ > 0);
}

void Player::DecreaseHP(int damage)
{
	playerHP_ -= damage;
}

void Player::AddItem(int itemId, int amount)
{
	std::cout << "아이템 [" << CLua::GetItemName(itemId) << "] " << amount << "개 획득!" << std::endl;
}

void Player::IncreaseExp(int exp)
{
	std::cout << "경험치 " << exp << " 획득!" << std::endl;
	playerExp_ += exp;

	if (exp >= 100) {
		std::cout << "레벨업!" << std::endl;
		playerLevel_++;
		playerExp_ -= 100;
	}
}

void Player::IncreaseGold(int gold)
{
	std::cout << "골드 " << gold << " 획득!" << std::endl;
	playerGold_ += gold;
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
	if (quest.GetNormalTarget().empty() == false) {
		std::cout << "	" << quest.GetNormalTarget() << std::endl;
	}	
	std::cout << std::endl;

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
	std::cout << "input \"exit\" to return" << std::endl;

	std::string input;
	
	while (std::cout << ">> " && std::getline(std::cin, input) && input != "exit")
	{

	}
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
			if (target != targetList.end()) {
				target->second.targetCount++;

				std::cout << CLua::GetMonsterName(target->first) << " : ";
				std::cout << target->second.targetCount << " / " << target->second.targetAmount << std::endl;

				if (CLua::CheckClearQuest(quest->GetQuestID(), this, quest) == true) {
					std::cout << "퀘스트 " << quest->GetName() << " 목표 달성!" << std::endl;
				}
			}
		}
	}
}

/// <summary>
/// Field
/// </summary>

bool Player::EnterField(int fieldId)
{
	if (field_ != NULL) {
		if (field_->GetID() == fieldId) {
			return true;
		}
		else {
			std::cout << "Already Entered Another Field" << std::endl;
			return false;
		}
	}

	auto result = CLua::CheckEnterField(fieldId, this);

	if (result == true) {
		auto field = new Field(CLua::GetField(fieldId));

		field_ = field;

		std::cout << "Enter Field!" << std::endl;
	}
	else {
		std::cout << "Cannot Enter!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		return false;
	}

	return true;
}

void Player::ExitField()
{
	if (field_ == NULL) {
		std::cout << "Not Entered Field" << std::endl;
		return;
	}

	std::cout << "Exit Field!" << std::endl;

	delete(field_);
	field_ = NULL;
}

Monster* Player::GetFieldMonster(int index)
{
	auto monsterList = field_->GetMonsterList();

	return monsterList[index];
}

std::list<std::string> Player::GetFieldMonsterList()
{
	auto monsterList = field_->GetMonsterList();

	auto monsterNameList = std::list<std::string>();

	for (auto monster : monsterList) {
		monsterNameList.push_back(monster->GetName());
	}

	return monsterNameList;
}


/// <summary>
/// Battle
/// </summary>

void Player::BattlePlayerTurn(BattleEvent& event)
{
	if (monster_->CheckMonsterAlive() == false || CheckPlayerAlive() == false) {
		return;
	} 

	event.HandleBattleProcessEvent();
	
	if (monster_->CheckMonsterAlive() == false) {
		event.MonsterDead();
	}
	else if (CheckPlayerAlive() == false) {
		event.PlayerDead();
	}
}

void Player::ProcessBattle()
{
	BattleEvent event(this, monster_);

	while (monster_->CheckMonsterAlive() && CheckPlayerAlive()) {
		system("cls");
		std::cout << "[Player] HP : " << playerHP_ << std::endl;
		std::cout << "[Monster] HP : " << monster_->GetHP() << std::endl;

		std::cout << "플레이어의 행동을 선택해주십시오." << std::endl;
		std::cout << "=================================" << std::endl;
		std::cout << "1.공격 / 2.스킬 / 3.아이템 / 4.도망" << std::endl;
		std::cout << "=================================" << std::endl;

		std::cout << ">> ";
		std::string input;
		std::getline(std::cin, input);
		
		try {
			auto inputNum = std::stoi(input);

			switch (inputNum)
			{
				case 1:
				{
					event.SetEvent(BATTLE_EVENT::PlayerAttack);
					break;
				}
				case 2:
				{
					event.SetEvent(BATTLE_EVENT::PlayerSkill);
					break;
				}
				case 3:
				{
					event.SetEvent(BATTLE_EVENT::PlayerItem);
					break;
				}
				case 4:
				{
					event.SetEvent(BATTLE_EVENT::PlayerTryRun);
					break;
				}
				default:
				{
					std::cout << "Invalid Input" << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}
			}

			auto isPlayerFirst = CLua::CheckBattleTurn(this, monster_);

			if (isPlayerFirst == true) {
				std::cout << "플레이어 선공!" << std::endl;
				BattlePlayerTurn(event);
				CLua::BattleMonsterTurn(this, monster_, event);
			}
			else {
				std::cout << "플레이어 후공!" << std::endl;
				CLua::BattleMonsterTurn(this, monster_, event);
				BattlePlayerTurn(event);
			}
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		catch (std::exception& e)
		{
			std::cout << "Invalid Input" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	FinishBattle(event);
}

void Player::StartBattle(Monster *monster)
{
	monster_ = monster;

	std::cout << monster->GetName() << " 와(과)의 전투 개시" << std::endl;
	CLua::InitBattle(this, monster);

	std::this_thread::sleep_for(std::chrono::seconds(1));
	ProcessBattle();
}

void Player::FinishBattle(BattleEvent& event)
{
	std::cout <<  "전투 종료!" << std::endl;

	event.HandleBattleResultEvent();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	field_->MonsterDead(monster_);
	monster_ = NULL;
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