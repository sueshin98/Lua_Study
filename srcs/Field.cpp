#include "Field.hpp"
#include "Monster.hpp"
#include "CLua.hpp"

Field::Field(int fieldId, std::string fieldName)
	: fieldId_(fieldId), fieldName_(fieldName)
{
}

void Field::MonsterDead(Monster* monster)
{
	for (auto iter = monsterList_.begin(); iter != monsterList_.end(); iter++) {
		if ((*iter) == monster) {
			monsterList_.erase(iter);
			break;
		}
	}

	delete(monster);
}

/// <summary>
/// 
/// </summary>

std::vector<Monster*> Field::GetMonsterList()
{
	return monsterList_;
}

int Field::GetID()
{
	return fieldId_;
}

std::string Field::GetName()
{
	return fieldName_;
}

void Field::SetMonsterList(std::list<int> monsterList)
{
	for (auto monsterId : monsterList) {
		monsterList_.push_back(new Monster(CLua::GetMonster(monsterId)));
	}
}

void Field::SetID(int fieldId)
{
	fieldId_ = fieldId;
}

void Field::SetName(std::string fieldName)
{
	fieldName_ = fieldName;
}
