#pragma once
#include <map>

class Quest;
class Monster;
class BattleEvent;

class Player
{
public:
	Player();
	~Player() {}

	bool CheckPlayerAlive();

	void ReadQuest(int questId);
	bool AcceptQuest(int questId);
	bool ClearQuest(int questId);
	void ProvideReward(Quest* quest);

	void StartBattle(int monsterId);
	void ProcessBattle();
	bool HandleBattleEvent(BattleEvent& event);
	void BattlePlayerTurn(BattleEvent& event);
	void UpdateKillQuestProgress(int monsterId);
	
	void DecreaseHP(int damage);

	int GetLevel();
	int GetGrade();
	int GetExp();
	int GetGold();
	int GetSpeed();
	int GetAtk();
	int GetDef();
	int GetHP();
	int GetMP();

	void SetLevel(int level);
	void SetGrade(int level);
	void SetExp(int exp);
	void SetGold(int gold);
	void SetSpeed(int speed);
	void SetAtk(int atk);
	void SetDef(int def);
	void SetHp(int hp);
	void SetMp(int mp);

private:
	std::map<int, Quest*> questMap_;
	Monster* monster_;

	int playerLevel_;
	int playerGrade;
	int playerExp_;
	int playerGold_;

	int playerSpeed_;
	int playerAtk_;
	int playerDef_;
	int playerHP_;
	int playerMP_;
};