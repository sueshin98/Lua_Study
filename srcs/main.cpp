
#include <iostream>
#include <limits>

#include "Quest.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Item.hpp"
#include "BattleEvent.hpp"
#include "CLua.hpp"

void tolower(std::string& str)
{
	std::for_each(str.begin(), str.end(), [](auto& c) {c = tolower(c); });
}

void HandleQuest(int questId, Player* player)
{
	while (true)
	{
		system("cls");

		std::string input;
		
		std::cout << "Quest [" << CLua::GetQuestName(questId) << "]" << std::endl;
		std::cout << "select Command : 1.[READ] / 2.[ACCEPT] / 3.[CLEAR] / 4.[EXIT]" << std::endl;

		std::cout << ">> ";
		std::getline(std::cin, input);
		tolower(input);
		std::cout << std::endl;

		if (input == "read") {
			player->ReadQuest(questId);
		}
		else if (input == "accept") {
			player->AcceptQuest(questId);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else if (input == "clear") {
			player->ClearQuest(questId);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		if (input == "exit") {
			break;
		}
		std::cout << std::endl;
	}
}

void SelectQuest(Player* player)
{	
	while (true)
	{
		system("cls");
		
		std::string input;
		int questId = -1;

		std::cout << "Quest List" << std::endl;
		std::cout << "=============================" << std::endl;
		for (auto questName : CLua::GetQuestList()) {
			std::cout << "[" << questName << "] " << std::endl;
		}
		std::cout << "=============================" << std::endl;
		std::cout << "select(or exit) >> ";

		std::getline(std::cin, input);
		if (input == "exit") {
			return;
		}

		questId = CLua::GetQuestID(input);
		if (questId == -1) {
			std::cout << "Invalid Quest Name" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			continue;
		}

		HandleQuest(questId, player);	}
}

void HandleField(int fieldId, Player* player)
{
	while (true)
	{
		system("cls");

		std::string input;
		int monsterIndex = 0;

		std::cout << "Monster List" << std::endl;
		std::cout << "=============================" << std::endl;
		for (auto monsterName : player->GetFieldMonsterList()) {
			std::cout << monsterIndex++ << " : [" << monsterName << "] " << std::endl;
		}
		std::cout << "=============================" << std::endl;
		std::cout << "select Monster(Number): ";

		std::getline(std::cin, input);
		if (input == "exit") {
			player->ExitField();
			return;
		}

		try {
			auto selectedNumber = std::stoi(input);

			if (selectedNumber >= monsterIndex) {
				std::cout << "Invalid Monster Number" << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				continue;
			}
			player->StartBattle(player->GetFieldMonster(selectedNumber));
		}
		catch (std::exception& e) {
			std::cout << "Invalid Input" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

void SelectField(Player* player)
{
	while (true)
	{
		system("cls");

		std::string input;
		int fieldId = -1;
		
		std::cout << "Field List" << std::endl;
		std::cout << "=============================" << std::endl;
		for (auto fieldName : CLua::GetFieldList()) {
			std::cout << "[" << fieldName << "] " << std::endl;
		}
		std::cout << "=============================" << std::endl;
		std::cout << "select(or exit) >> ";

		std::getline(std::cin, input);
		if (input == "exit") {
			return;
		}

		fieldId = CLua::GetFieldID(input);
		if (fieldId == -1) {
			std::cout << "Invalid Field Name" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			continue;
		}

		if (player->EnterField(fieldId)) {
			HandleField(fieldId, player);
		}
	}
}

int main()
{
	CLua::Init();
	CLua::RegisterClass();
	CLua::RegisterScripts();

	std::thread t1(CLua::EnalbeFileWatcher);
	t1.detach();

	Player* player = new Player();
	
	//char buf[256];
	std::string input;
	while (true)
	{
		system("cls");
		std::cout << std::endl;
		std::cout << "Select Menu" << std::endl;
		std::cout << "=============================" << std::endl;
		std::cout << "1.[QUEST] / 2.[FIELD] / 3.[EXIT]" << std::endl;
		std::cout << "=============================" << std::endl;

		std::cout << ">> ";
		std::getline(std::cin, input);
		tolower(input);
		
		if (input == "quest") {
			SelectQuest(player);
		}
		else if (input == "field") {
			SelectField(player);
		}
		else if (input == "exit") {
			break;
		}
		else {
			std::cout << "Invalid Command" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	delete(player);
}
