#pragma once
#include <map>
#include <list>
#include <string>

class Quest;
class Monster;
class Field;
class BattleEvent;

class Player
{
public:
	Player();
	~Player() {}

	bool CheckPlayerAlive();
	void AddItem(int itemId, int amount);
	void IncreaseExp(int exp);
	void IncreaseGold(int gold);
	void DecreaseHP(int damage);

	void ReadQuest(int questId);
	bool AcceptQuest(int questId);
	bool ClearQuest(int questId);
	void ProvideReward(Quest* quest);

	bool EnterField(int fieldId);
	void ExitField();
	Monster* GetFieldMonster(int index);
	std::list<std::string> GetFieldMonsterList();


	void StartBattle(Monster* monster);
	void ProcessBattle();
	void FinishBattle(BattleEvent& event);
	void BattlePlayerTurn(BattleEvent& event);
	void UpdateKillQuestProgress(int monsterId);

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
	Field* field_;
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