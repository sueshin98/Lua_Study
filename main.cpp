
#include <iostream>
#include "Define.hpp"
#include "CLua.hpp"
#include "Player.hpp"

int main()
{
	CLua::Init();
	CLua::RegisterClass();
	CLua::RegisterScripts();

	std::thread t1(CLua::EnalbeFileWatcher);

	Player* player = new Player();
	
	char buf[256];
	while (true)
	{
		fgets(buf, sizeof(buf), stdin);
		if (strcmp(buf, "check\n") == 0)
		{
			player->ReadQuest(QuestID::quest1);
		}

		if (strcmp(buf, "quest\n") == 0)
		{
			player->AcceptQuest(QuestID::quest1);
		}

		if (strcmp(buf, "kill\n") == 0)
		{
			player->UpdateKillQuestProgress(MonsterID::MONSTER1);
		}

		if (strcmp(buf, "clear\n") == 0)
		{
			player->ClearQuest(QuestID::quest1);
		}

		if (strcmp(buf, "gold\n") == 0)
		{
			std::cout << "gold : " << player->GetPlayerGold() << std::endl;
		}
	}

	player->AcceptQuest(QuestID::quest1);

	player->UpdateKillQuestProgress(MonsterID::MONSTER1);
	player->UpdateKillQuestProgress(MonsterID::MONSTER1);
	
	player->ClearQuest(QuestID::quest1);

	std::cout << "gold : " << player->GetPlayerGold() << std::endl;

	player->AcceptQuest(QuestID::quest1);

	player->UpdateKillQuestProgress(MonsterID::MONSTER1);
	player->UpdateKillQuestProgress(MonsterID::MONSTER1);

	player->ClearQuest(QuestID::quest1);

	std::cout << "gold : " << player->GetPlayerGold() << std::endl;

}
