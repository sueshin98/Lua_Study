#pragma once
#include <map>
#include <list>
#include <string>

enum class MonsterID;
enum class ItemID;

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
	std::list<std::tuple<int, int>> itemReward = {};
};

class Quest
{
public:
	
	Quest(int questId, std::string questName);
	~Quest() {}

	bool CheckKillTarget();

	void SetQuestID(int questID);
	void SetType(QuestType questType);
	void SetRarity(QuestRarity questRarity);
	void SetKillTargetList(std::map<int, QuestKillTarget> targetList);
	void SetName(const char* questName);
	void SetDescription(std::string questDescription);
	void SetReward(QuestReward& questReward);

	int GetQuestID();
	QuestType GetType();
	QuestRarity GetRarity();
	std::map<int, QuestKillTarget>& GetKillTargetList();
	std::string GetName();
	std::string GetDescription();
	QuestReward& GetReward();

private:
	int questId_;
	QuestType questType_;
	QuestRarity questRarity_;
	QuestReward questReward_;
	std::map<int, QuestKillTarget> questKillTargetList_;
	
	std::string questName_;
	std::string questDescription_;
};