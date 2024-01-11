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
	battleResultHandler.emplace(BATTLE_EVENT::PlayerDead, [this]() { std::cout << "�÷��̾� ���!" << std::endl; });
	battleResultHandler.emplace(BATTLE_EVENT::MonsterRun, [this]() { std::cout << "���� ����!" << std::endl; });
	battleResultHandler.emplace(BATTLE_EVENT::PlayerRun, [this]() { std::cout << "�÷��̾� ����!" << std::endl; });

	battleProcessHandler.emplace(BATTLE_EVENT::PlayerAttack, [this]() { std::cout << "�÷��̾��� ����!" << std::endl; monster_->DecreaseHP(player_->GetAtk() - monster_->GetDef()); });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerSkill, [this]() { std::cout << "�÷��̾��� ��ų!" << std::endl; });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerItem, [this]() { std::cout << "�÷��̾��� ������!" << std::endl; });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerGuard, [this]() { std::cout << "�÷��̾��� ���!" << std::endl; });
	battleProcessHandler.emplace(BATTLE_EVENT::PlayerTryRun, [this]() { std::cout << "�÷��̾��� ����!" << std::endl; });
}

void BattleEvent::HandleBattleProcessEvent()
{
	if (battleProcessHandler.find(event_) != battleProcessHandler.end()) {
		battleProcessHandler[event_]();
	}
	else {
		std::cout << "�߸��� ���� ���� �̺�Ʈ�Դϴ�." << std::endl;
	}
}

void BattleEvent::HandleBattleResultEvent()
{
	if (battleResultHandler.find(event_) != battleResultHandler.end()) {
		battleResultHandler[event_]();
	}
	else {
		std::cout << "�߸��� ���� �Ϸ� �̺�Ʈ�Դϴ�." << std::endl;
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
