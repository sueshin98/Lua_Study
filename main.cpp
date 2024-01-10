
#include <iostream>
#include "Define.hpp"
#include "CLua.hpp"

void tolower(std::string& str)
{
	std::for_each(str.begin(), str.end(), [](auto& c) {c = tolower(c); });
}


void HandleQuest(Player* player)
{
	std::string input;
	int questId = -1;

	while (questId == -1)
	{
		std::cout << "Quest List" << std::endl;
		std::cout << "=============================" << std::endl;
		std::cout << "[MonsterSlayer] [quest2] [quest3]" << std::endl;
		std::cout << "=============================" << std::endl;
		std::cout << "select Quest: ";

		std::getline(std::cin, input);
		questId = CLua::GetQuestID(input);
		if (questId == -1) {
			std::cout << "Invalid Quest Name" << std::endl;
		}

		std::cout << std::endl;
	}

	while (true)
	{
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
			break;
		}
		else if (input == "clear") {
			player->ClearQuest(questId);
		}
		if (input == "exit") {
			break;
		}
		std::cout << std::endl;
	}
}

void HandleField(Player* player)
{
	std::string input;

	std::cout << "Monster List" << std::endl;
	std::cout << "=============================" << std::endl;
	std::cout << "[Monster1] [Monster2] [Monster3]" << std::endl;
	std::cout << "=============================" << std::endl;
	std::cout << "select Monster: ";

	std::getline(std::cin, input);
	auto monsterId = CLua::GetMonsterID(input);
	std::cout << std::endl;

	while (true)
	{
		std::cout << "Battle Start!" << std::endl;

		player->StartBattle(monsterId);
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
		std::cout << std::endl;
		std::cout << "Select Menu" << std::endl;
		std::cout << "=============================" << std::endl;
		std::cout << "1.[QUEST] / 2.[...] / N.[EXIT]" << std::endl;
		std::cout << "=============================" << std::endl;

		std::cout << ">> ";
		std::getline(std::cin, input);
		tolower(input);
		std::cout << std::endl;
		
		if (input == "quest") {
			HandleQuest(player);
		}
		else if (input == "field") {
			HandleField(player);
		}
		else if (input == "exit") {
			break;
		}
	}

	delete(player);
}
