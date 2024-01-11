#include "Quest.hpp"

Quest::Quest(int questId, std::string questName)
	: questId_(questId), questName_(questName)
{
}

bool Quest::CheckKillTarget()
{
	for (auto& targetPair : questKillTargetList_)
	{
		auto& target = targetPair.second;
		if (target.targetCount < target.targetAmount)
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// 
/// </summary>

void Quest::SetQuestID(int questId)
{
	questId_ = questId;
};

void Quest::SetType(QuestType type)
{
	questType_ = type;
};

void Quest::SetRarity(QuestRarity rarity)
{
	questRarity_ = rarity;
};

void Quest::SetKillTargetList(std::map<int, QuestKillTarget> targetList)
{
	questKillTargetList_ = targetList;
}
void Quest::SetNormalTarget(std::string questNormalTarget)
{
	questNormalTarget_ = questNormalTarget;
}

void Quest::SetName(const char* name)
{
	questName_ = name;
};

void Quest::SetDescription(std::string description)
{
	questDescription_ = description;
};

void Quest::SetReward(QuestReward& reward)
{
	questReward_ = reward;
};

/// <summary>
/// 
/// </summary>

int Quest::GetQuestID()
{
	return questId_;
};

QuestType Quest::GetType()
{
	return questType_;
};

QuestRarity Quest::GetRarity()
{
	return questRarity_;
};

std::map<int, QuestKillTarget>& Quest::GetKillTargetList()
{
	return questKillTargetList_;
}
std::string Quest::GetNormalTarget()
{
	return questNormalTarget_;
}

std::string Quest::GetName()
{
	return questName_;
};

std::string Quest::GetDescription()
{
	return questDescription_;
};

QuestReward& Quest::GetReward()
{
	return questReward_;
};
