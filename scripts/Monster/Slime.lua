-- 전투는 턴제로 진행한다고 가정
Slime = Slime or {}


-- 몬스터 기본설정
Slime.speed = 10
Slime.attack = 10
Slime.defense = 10
Slime.hp = 100
Slime.mp = 100
Slime.exp = 100
Slime.gold = 100
Slime.dropItem = {
	[0] = {id = item.id.ITEM1, amount = 1, chance = 0.5},
	[1] = {id = item.id.ITEM2, amount = 1, chance = 0.2},
	[2] = {id = item.id.ITEM3, amount = 1, chance = 0.1},
}

-- 몬스터 스킬

-- 전투 시작시
Slime.initBattle = function(player, monster)
	if player.GetLevel() > monster.GetLevel() then
		monster:SetState(monster.state.Fear)
		print(monster.GetName() .. "은 플레이어를 보고 겁에 질렸다!")
	elseif player.GetHP() < 100 then
		monster:SetState(monster.state.Excitement)
		print(monster.GetName() .. "은 플레이어를 보고 흥분한 듯하다.")
	else
		monster:SetState(monster.state.Normal)
		print(monster.GetName() .. "은 플레이어를 바라보고있다.")
	end
end

-- 선공 결정
Slime.checkBattleTurn = function(player, monster)
	if monster:GetState() == monster.state.Fear then
		return true
	end
	return player:GetSpeed() > monster:GetSpeed()
end

-- 몬스터 행동
Slime.battleMonsterTurn = function(player, monster, event)
	-- 현재 몬스터 상태에 따라 공격 / 방어 / 도망 등 처리
	if monster:GetHP() < self.hp * 0.5 then
		monster:Guard()
	elseif monster:GetHP() < self.hp * 0.2 then
		local result = monster:TryRun(player)
		if result == true then
			return event:MonsterRun();
		end
	else
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
	player:AddExp(Slime.exp)
	player:AddGold(Slime.gold)
	for i = 0, Slime.dropItem.length do
		if Slime.dropItem[i].chance > math.random() then
			player:AddItem(Slime.dropItem[i].id, Slime.dropItem[i].amount)
		end
	end
end