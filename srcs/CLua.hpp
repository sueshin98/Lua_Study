#pragma once
#include <string>
#include <tuple>

#include "../include/sol.hpp"
#include "../include/watcher.hpp"

class Player;
class Monster;
class Field;
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

	std::list<std::string> GetQuestList();
	Quest GetQuest(int questId);
	bool CheckAcceptQuest(int questId, Player* player);
	bool CheckClearQuest(int questId, Player* player, Quest* quest);

	std::list<std::string> GetFieldList();
	Field GetField(int fieldId);
	bool CheckEnterField(int fieldId, Player* player);

	Monster GetMonster(int monsterId);
	void InitBattle(Player* player, Monster* monster);
	bool CheckBattleTurn(Player* player, Monster* monster);
	void BattleMonsterTurn(Player* player, Monster* monster, BattleEvent& event);
	void ProvideBattleReward(Player* player, Monster* monster);

	int GetQuestID(std::string questName);
	int GetMonsterID(std::string monsterName);
	int GetFieldID(std::string fieldName);
	std::string GetQuestName(int questId);
	std::string GetMonsterName(int monsterId);
	std::string GetItemName(int itemId);
	std::string GetFieldName(int fieldId);
}