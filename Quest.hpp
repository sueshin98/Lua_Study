#pragma once
#include <map>
#include <list>
#include <string>

enum class MonsterID;
enum class ItemID;

enum class QuestID
{
	quest1,
	quest2,
	quest3
};

enum class QuestRarity
{
	Common,
	Rare,
	Unique
};

enum class QuestType
{
	None,
	Kill,
	Collect,
	Multi
};

struct QuestKillTarget
{
	int targetAmount = 0;
	int targetCount = 0;
};

struct QuestReward
{
	int expReward = 0;
	int goldReward = 0;
	std::list<std::tuple<ItemID, int>> itemReward = {};
};

class Quest
{
public:
	
	Quest(QuestID questId, const char* questName);
	~Quest() {}

	bool CheckKillTarget();

	void SetQuestID(QuestID questID);
	void SetType(QuestType questType);
	void SetRarity(QuestRarity questRarity);
	void SetKillTargetList(std::map<MonsterID, QuestKillTarget> targetList);
	void SetName(const char* questName);
	void SetDescription(std::string questDescription);
	void SetReward(QuestReward& questReward);

	QuestID GetQuestID();
	QuestType GetType();
	QuestRarity GetRarity();
	std::map<MonsterID, QuestKillTarget>& GetKillTargetList();
	std::string GetName();
	std::string GetDescription();
	QuestReward& GetReward();

private:
	QuestID questID_;
	QuestType questType_;
	QuestRarity questRarity_;
	QuestReward questReward_;
	std::map<MonsterID, QuestKillTarget> questKillTargetList_;
	
	const char* questName_;
	std::string questDescription_;
};