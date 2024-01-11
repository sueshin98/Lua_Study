#include <map>
#include <functional>

enum class BATTLE_EVENT
{
	None,
	MonsterDead,
	PlayerDead,
	MonsterRun,
	PlayerRun,
	PlayerAttack,
	PlayerSkill,
	PlayerItem,
	PlayerGuard,
	PlayerTryRun
};

class Player;
class Monster;

class BattleEvent
{
public:
	BattleEvent(Player* player, Monster* monster);
	~BattleEvent() {}

	void Init();
	void HandleBattleProcessEvent();
	void HandleBattleResultEvent();

	void SetEvent(BATTLE_EVENT event);
	BATTLE_EVENT GetEvent();

	void MonsterDead();
	void PlayerDead();
	void MonsterRun();
	void PlayerRun();

private:
	std::map<BATTLE_EVENT, std::function<void()>> battleResultHandler;
	std::map<BATTLE_EVENT, std::function<void()>> battleProcessHandler;
	BATTLE_EVENT event_;
	Player* player_;
	Monster* monster_;

};
