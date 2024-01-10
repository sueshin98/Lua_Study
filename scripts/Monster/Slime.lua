-- ������ ������ �����Ѵٰ� ����
Slime = Slime or {}


-- ���� �⺻����
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

-- ���� ��ų

-- ���� ���۽�
Slime.initBattle = function(player, monster)
	if player.GetLevel() > monster.GetLevel() then
		monster:SetState(monster.state.Fear)
		print(monster.GetName() .. "�� �÷��̾ ���� �̿� ���ȴ�!")
	elseif player.GetHP() < 100 then
		monster:SetState(monster.state.Excitement)
		print(monster.GetName() .. "�� �÷��̾ ���� ����� ���ϴ�.")
	else
		monster:SetState(monster.state.Normal)
		print(monster.GetName() .. "�� �÷��̾ �ٶ󺸰��ִ�.")
	end
end

-- ���� ����
Slime.checkBattleTurn = function(player, monster)
	if monster:GetState() == monster.state.Fear then
		return true
	end
	return player:GetSpeed() > monster:GetSpeed()
end

-- ���� �ൿ
Slime.battleMonsterTurn = function(player, monster, event)
	-- ���� ���� ���¿� ���� ���� / ��� / ���� �� ó��
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

-- ��Ʋ ���� �� ���� ����
Slime.provideBattleReward = function(player)
	player:AddExp(Slime.exp)
	player:AddGold(Slime.gold)
	for i = 0, Slime.dropItem.length do
		if Slime.dropItem[i].chance > math.random() then
			player:AddItem(Slime.dropItem[i].id, Slime.dropItem[i].amount)
		end
	end
end