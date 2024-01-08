#pragma once
#include "Define.hpp"

class Player
{
public:
	Player()
	{
		playerLevel_ = 5;
		questLevel_ = 1;
	}

	~Player()
	{
		// ...
	}

	bool StartQuest(QuestID questId);


	int GetPlayerLevel();
	void SetPlayerLevel(int level);

	int GetQuestLevel();
	void SetQuestLevel(int level);


private:
	int playerLevel_;
	int questLevel_;

};