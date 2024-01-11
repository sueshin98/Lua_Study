Rat = Rat or {}
Monster = Monster or {}

-- ���� �⺻����
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

-- ���� ��ų


-- ������ ������ �����Ѵٰ� ����
-- ���� ���۽�
Rat.initBattle = function(player, monster)
	if player:GetHP() < 100 then
		monster:SetState(Monster.state.Excitement)
		print(monster:GetName() .. "�� �÷��̾ ���� ����� ���ϴ�.")
	else
		monster:SetState(Monster.state.Normal)
		print(monster:GetName() .. "�� �÷��̾ �ٶ󺸰��ִ�.")
	end
end

-- ���� ����
Rat.checkBattleTurn = function(player, monster)
	return false;
end

-- ���� �ൿ
Rat.battleMonsterTurn = function(player, monster, event)
	if monster:CheckMonsterAlive() == false or player:CheckPlayerAlive() == false then
		return
	end

	-- ���� ���� ���¿� ���� ���� / ��� / ���� �� ó��
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

-- ��Ʋ ���� �� ���� ����
Rat.provideBattleReward = function(player)
	player:IncreaseExp(Rat.exp)
	player:IncreaseGold(Rat.gold)
	for i = 0, #Rat.dropItem do
		if Rat.dropItem[i].chance > math.random() then
			player:AddItem(Rat.dropItem[i].id, Rat.dropItem[i].amount)
		end
	end
end