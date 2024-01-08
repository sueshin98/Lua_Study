#include "CLua.hpp"

namespace CLua
{
	sol::state lua;

	void CLua::Init()
	{
		lua.open_libraries();
	}

	void CLua::RegisterClass()
	{
		lua.new_usertype<Player>("Player",
			"GetPlayerLevel", &Player::GetPlayerLevel,
			"SetPlayerLevel", &Player::SetPlayerLevel,
			"GetQuestLevel", &Player::GetQuestLevel,
			"SetQuestLevel", &Player::SetQuestLevel
		);

		lua.new_usertype<Quest>("Quest");
	}

	void CLua::RunScript(std::string fileName)
	{
		lua.script_file(fileName);
	}

	bool CLua::CheckAvailable(const char* questName, Player* player)
	{
		sol::function checkAvailable;

		checkAvailable = lua[questName]["checkAvailable"];

		auto result = checkAvailable(player);

		return result;
	}
}