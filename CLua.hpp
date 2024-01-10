#pragma once
#include <string>
#include <tuple>

#include "sol/sol.hpp"
#include "watcher.hpp"

class Player;
class Monster;
class Quest;
class BattleEvent;

namespace CLua
{
	extern sol::state lua;

	void Init();

	void RegisterClass();
	void RegisterScripts();
	void RunScript(std::string fileName);
	void EnalbeFileWatcher();

	Quest GetQuest(int questId);
	bool CheckAcceptQuest(int questId, Player* player);
	bool CheckClearQuest(int questId, Player* player, Quest* quest);

	Monster GetMonster(int monsterId);
	void InitBattle(Player* player, Monster* monster);
	bool CheckBattleTurn(Player* player, Monster* monster);
	void BattleMonsterTurn(Player* player, Monster* monster, BattleEvent& event);
	void ProvideBattleReward(Player* player, Monster* monster);

	int GetQuestID(std::string questName);
	int GetMonsterID(std::string monsterName);
	std::string GetQuestName(int questId);
	std::string GetMonsterName(int monsterId);
	std::string GetItemName(int itemId);
}