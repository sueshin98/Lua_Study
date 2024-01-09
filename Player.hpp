#pragma once
#include "Define.hpp"

class Player
{
public:
	Player();
	~Player() {}

	void ReadQuest(QuestID questId);
	bool AcceptQuest(QuestID questId);
	bool ClearQuest(QuestID questId);
	void ProvideReward(Quest* quest);

	void UpdateKillQuestProgress(MonsterID monsterId);

	int GetPlayerLevel();
	int GetPlayerGrade();
	int GetPlayerExp();
	int GetPlayerGold();

	void SetPlayerLevel(int level);
	void SetPlayerGrade(int level);
	void SetPlayerExp(int exp);
	void SetPlayerGold(int gold);

private:
	std::map<QuestID, Quest*> questMap_;

	int playerLevel_;
	int playerGrade;
	int playerExp_;
	int playerGold_;
};