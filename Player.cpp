#include "Player.hpp"
#include "CLua.hpp"

bool Player::StartQuest(QuestID questId)
{
	auto result = CLua::CheckAvailable(magic_enum::enum_name(questId).data(), this);

	if (result == true) {
		printf("quest start!\n");
	}
	else {
		printf("Cannot start Quest!\n");
	}

	return true;
}


int Player::GetPlayerLevel()
{
	return playerLevel_;
}

void Player::SetPlayerLevel(int level)
{
	playerLevel_ = level;
}

int Player::GetQuestLevel()
{
	return questLevel_;
}

void Player::SetQuestLevel(int level)
{
	questLevel_ = level;
}