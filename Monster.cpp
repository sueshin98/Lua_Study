#include "Monster.hpp"
#include "Player.hpp"

Monster::Monster(int monsterId, std::string monsterName)
	: monsterId_(monsterId), monsterName_(monsterName)
{
}

bool Monster::CheckMonsterAlive()
{
	return (monsterHP_ > 0);
}

void Monster::Attack(Player* player)
{
	player->DecreaseHP(monsterAtk_ - player->GetDef());
}

void Monster::Guard()
{
}

bool Monster::TryRun(Player* player)
{
	auto basicChance = 30;

	basicChance -= (player->GetLevel() - monsterLevel_);

	srand(monsterId_);
	if (basicChance > rand() % 100) {
		return true;
	}

	return false;
}

/// <summary>
/// 
/// </summary>

int Monster::GetMonsterID()
{
	return monsterId_;
}

std::string Monster::GetName()
{
	return monsterName_;
}

MONSTER_STATE Monster::GetState()
{
	return monsterState_;
}

int Monster::GetLevel()
{
	return monsterLevel_;
}

int Monster::GetSpeed()
{
	return monsterSpeed_;
}

int Monster::GetAttack()
{
	return monsterAtk_;
}

int Monster::GetDefense()
{
	return monsterDef_;
}

int Monster::GetHP()
{
	return monsterHP_;
}

int Monster::GetMP()
{
	return monsterMP_;
}

/// <summary>
/// 
/// </summary>

void Monster::SetMonsterID(int monsterId)
{
	monsterId_ = monsterId;
}

void Monster::SetName(std::string monsterName)
{
	monsterName_ = monsterName;
}

void Monster::SetState(MONSTER_STATE state)
{
	monsterState_ = state;
}

void Monster::SetLevel(int level)
{
	monsterLevel_ = level;
}

void Monster::SetSpeed(int speed)
{
	monsterSpeed_ = speed;
}

void Monster::SetAttack(int attack)
{
	monsterAtk_ = attack;
}

void Monster::SetDefense(int defense)
{
	monsterDef_ = defense;
}

void Monster::SetHP(int hp)
{
	monsterHP_ = hp;
}

void Monster::SetMP(int mp)
{
	monsterMP_ = mp;
}

