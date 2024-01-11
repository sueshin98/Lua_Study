Slime = Slime or {}
Monster = Monster or {}

-- 몬스터 기본설정
Slime.speed = 10
Slime.attack = 10
Slime.defense = 0
Slime.hp = 10
Slime.mp = 100
Slime.exp = 100
Slime.gold = 100
Slime.dropItem = {
	[0] = {id = item.id.ITEM1, amount = 1, chance = 1.0},
	[1] = {id = item.id.ITEM2, amount = 1, chance = 0.2},
	[2] = {id = item.id.ITEM3, amount = 1, chance = 0.1},
}

-- 몬스터 스킬


-- 전투는 턴제로 진행한다고 가정
-- 전투 시작시
Slime.initBattle = function(player, monster)
	if player:GetLevel() > monster:GetLevel() then
		monster:SetState(Monster.state.Fear)
		print(monster:GetName() .. "은 플레이어를 보고 겁에 질렸다!")
	elseif player:GetHP() < 100 then
		monster:SetState(Monster.state.Excitement)
		print(monster:GetName() .. "은 플레이어를 보고 흥분한 듯하다.")
	else
		monster:SetState(Monster.state.Normal)
		print(monster:GetName() .. "은 플레이어를 바라보고있다.")
	end
end

-- 선공 결정
Slime.checkBattleTurn = function(player, monster)
	if monster:GetState() == monster.state.Fear then
		print(monster:GetName() .. "은 겁에 질린 상태이다.")
		return true
	end
	return player:GetSpeed() >= monster:GetSpeed()
end

-- 몬스터 행동
Slime.battleMonsterTurn = function(player, monster, event)
	if monster:CheckMonsterAlive() == false or player:CheckPlayerAlive() == false then
		return
	end

	-- 현재 몬스터 상태에 따라 공격 / 방어 / 도망 등 처리
	if monster:GetHP() < Slime.hp * 0.5 then
		print("Monster Guard")
		monster:Guard()
	elseif monster:GetHP() < Slime.hp * 0.2 then
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
Slime.provideBattleReward = function(player)
	player:IncreaseExp(Slime.exp)
	player:IncreaseGold(Slime.gold)
	for i = 0, #Slime.dropItem do
		if Slime.dropItem[i].chance > math.random() then
			player:AddItem(Slime.dropItem[i].id, Slime.dropItem[i].amount)
		end
	end
end