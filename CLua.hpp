#pragma once
#include <string>

#include "sol/sol.hpp"
#include "Define.hpp"

namespace CLua
{
	extern sol::state lua;

	void Init();

	void RegisterClass();
	void RunScript(std::string fileName);

	bool CheckAvailable(const char* questName, Player* player);
}