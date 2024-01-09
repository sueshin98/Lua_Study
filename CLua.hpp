#pragma once
#include <string>
#include <tuple>


#include "sol/sol.hpp"
#include "watcher.hpp"
#include "Define.hpp"


namespace CLua
{
	extern sol::state lua;

	void Init();

	void RegisterClass();
	void RegisterScripts();
	void RunScript(std::string fileName);
	void EnalbeFileWatcher();

	Quest* GetQuest(QuestID questId);
	bool CheckAcceptQuest(const char* questName, Player* player);
	bool CheckClearQuest(const char* questName, Quest* quest);
}

