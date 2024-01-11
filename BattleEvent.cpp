#include "BattleEvent.hpp"
#include "CLua.hpp"
#include "Player.hpp"
#include "Monster.hpp"

BattleEvent::BattleEvent(Player* player, Monster* monster)
{
	player_ = player;
	monster_ = monster;
	event_ = BATTLE_EVENT::None;

	Init();
}

void BattleEvent::Init()
{
	battleResultHandler.emplace(BATTLE_EVENT::MonsterDead, [this]() { CLua::ProvideBattleReward(player_, monster_); player_->UpdateKillQuestProgress(monster_->GetMonsterID()); });
	battleResultHandler.emplace(BATTLE_EVENT::PlayerDead, [this]() { std::cout << "플레이어 사망!" << std::endl; });
	battleResultHandler.emplace(BATTLE_EVENT::MonsterRun, [this]() { std::cout << "몬스터 도망!" << std::endl; });
	battleResultHandler.emplace(BATTLE_EVENT::PlayerRun, [this]() { std::cout << "플레이어 도망!" << std::endl; });

	battleProcessHandler.emplace(BATTLE_EVENT::PlayerAttack, [this]() { std::cout << "플레이어의 공격!" << std::endl; monster_->DecreaseHP(player_->GetAtk() - monster_->GetDef()); });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerSkill, [this]() { std::cout << "플레이어의 스킬!" << std::endl; });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerItem, [this]() { std::cout << "플레이어의 아이템!" << std::endl; });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerGuard, [this]() { std::cout << "플레이어의 방어!" << std::endl; });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerTryRun, [this]() { std::cout << "플레이어의 도망!" << std::endl; });
}

void BattleEvent::HandleBattleProcessEvent()
{
	if (battleProcessHandler.find(event_) != battleProcessHandler.end()) {
		battleProcessHandler[event_]();
	}
	else {
		std::cout << "잘못된 전투 진행 이벤트입니다." << std::endl;
	}
}

void BattleEvent::HandleBattleResultEvent()
{
	if (battleResultHandler.find(event_) != battleResultHandler.end()) {
		battleResultHandler[event_]();
	}
	else {
		std::cout << "잘못된 전투 완료 이벤트입니다." << std::endl;
	}
}

void BattleEvent::MonsterDead()
{
	event_ = BATTLE_EVENT::MonsterDead;
}

void BattleEvent::PlayerDead()
{
	event_ = BATTLE_EVENT::PlayerDead;
}

void BattleEvent::MonsterRun()
{
	event_ = BATTLE_EVENT::MonsterRun;
}

void BattleEvent::PlayerRun()
{
	event_ = BATTLE_EVENT::PlayerRun;
}

BATTLE_EVENT BattleEvent::GetEvent()
{
	return event_;
}

void BattleEvent::SetEvent(BATTLE_EVENT event)
{
	event_ = event;
}
