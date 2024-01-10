#pragma once
#include <string>

enum class MONSTER_STATE
{
	Normal,
	Fear,
	Excitement
};

class Player;

class Monster
{
public:
	Monster(int monsterId, std::string monsterName);
	~Monster() {}

	bool CheckMonsterAlive();
	void Attack(Player* player);
	void Guard();
	bool TryRun(Player* player);

	int GetMonsterID();
	std::string GetName();
	MONSTER_STATE GetState();
	int GetLevel();
	int GetSpeed();
	int GetAttack();
	int GetDefense();
	int GetHP();
	int GetMP();

	void SetMonsterID(int monsterId);
	void SetName(std::string monsterName);
	void SetState(MONSTER_STATE state);
	void SetLevel(int level);
	void SetSpeed(int speed);
	void SetAttack(int atk);
	void SetDefense(int def);
	void SetHP(int hp);
	void SetMP(int mp);

private:
	int monsterId_;
	std::string monsterName_;
	MONSTER_STATE monsterState_;

	int monsterLevel_;
	int monsterSpeed_;
	int monsterAtk_;
	int monsterDef_;
	int monsterHP_;
	int monsterMP_;
};