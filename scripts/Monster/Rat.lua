Rat = Rat or {}
Monster = Monster or {}

-- 몬스터 기본설정
Rat.speed = 15
Rat.attack = 8
Rat.defense = 0
Rat.hp = 18
Rat.mp = 100
Rat.exp = 100
Rat.gold = 100
Rat.dropItem = {
	[0] = {id = item.id.ITEM1, amount = 2, chance = 0.1},
	[1] = {id = item.id.ITEM2, amount = 1, chance = 0.8},
	[2] = {id = item.id.ITEM3, amount = 1, chance = 0.9},
}

-- 몬스터 스킬


-- 전투는 턴제로 진행한다고 가정
-- 전투 시작시
Rat.initBattle = function(player, monster)
	if player:GetHP() < 100 then
		monster:SetState(Monster.state.Excitement)
		print(monster:GetName() .. "은 플레이어를 보고 흥분한 듯하다.")
	else
		monster:SetState(Monster.state.Normal)
		print(monster:GetName() .. "은 플레이어를 바라보고있다.")
	end
end

-- 선공 결정
Rat.checkBattleTurn = function(player, monster)
	return false;
end

-- 몬스터 행동
Rat.battleMonsterTurn = function(player, monster, event)
	if monster:CheckMonsterAlive() == false or player:CheckPlayerAlive() == false then
		return
	end

	-- 현재 몬스터 상태에 따라 공격 / 방어 / 도망 등 처리
	if monster:GetHP() < Rat.hp * 0.5 then
		print("Monster Guard")
		monster:Guard()
	elseif monster:GetHP() < Rat.hp * 0.2 then
		print("Monster Try to Run")
		local result = monster:TryRun(player)
		if result == true then
			return event:MonsterRun();
		end
	else
		print("Monster Attack!")
		monster:Attack(player)
	end

	if monster:CheckMonsterAlive() == false then
		event:MonsterDead();
	elseif player:CheckPlayerAlive() == false then
		event:PlayerDead();
	end
end

-- 배틀 종료 후 보상 지급
Rat.provideBattleReward = function(player)
	player:IncreaseExp(Rat.exp)
	player:IncreaseGold(Rat.gold)
	for i = 0, #Rat.dropItem do
		if Rat.dropItem[i].chance > math.random() then
			player:AddItem(Rat.dropItem[i].id, Rat.dropItem[i].amount)
		end
	end
end