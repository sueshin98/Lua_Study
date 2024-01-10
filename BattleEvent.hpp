enum class BATTLE_EVENT
{
	None,
	MonsterDead,
	PlayerDead,
	MonsterRun,
	PlayerRun
};

class BattleEvent
{
public:
	BattleEvent() {}
	~BattleEvent() {}

	void SetEvent(BATTLE_EVENT event) { event_ = event; }
	BATTLE_EVENT GetEvent() { return event_; }

	void MonsterDead() { event_ = BATTLE_EVENT::MonsterDead; }
	void PlayerDead() { event_ = BATTLE_EVENT::PlayerDead; }
	void MonsterRun() { event_ = BATTLE_EVENT::MonsterRun; }
	void PlayerRun() { event_ = BATTLE_EVENT::PlayerRun; }

private:
	BATTLE_EVENT event_;

};
