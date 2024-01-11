#include <list>
#include <string>
#include <vector>

class Monster;

class Field
{
public:
	Field(int fieldId, std::string fieldName);
	~Field() {}

	void MonsterDead(Monster* monster);

	int GetID();
	std::string GetName();
	std::vector<Monster*> GetMonsterList();

	void SetID(int fieldId);
	void SetName(std::string fieldName);
	void SetMonsterList(std::list<int> monsterList);

private:
	int fieldId_;
	std::string fieldName_;
	
	std::vector<Monster*> monsterList_;

};