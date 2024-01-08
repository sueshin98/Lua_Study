
#include <iostream>
#include "Define.hpp"
#include "CLua.hpp"
#include "Player.hpp"

int main()
{
	CLua::Init();
	CLua::RegisterClass();

	CLua::RunScript("quest1.lua");

	Player* player = new Player();

	player->StartQuest(QuestID::quest1);

}
