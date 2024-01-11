Slime = Slime or {}
Monster = Monster or {}

-- ���� �⺻����
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

-- ���� ��ų


-- ������ ������ �����Ѵٰ� ����
-- ���� ���۽�
Slime.initBattle = function(player, monster)
	if player:GetLevel() > monster:GetLevel() then
		monster:SetState(Monster.state.Fear)
		print(monster:GetName() .. "�� �÷��̾ ���� �̿� ���ȴ�!")
	elseif player:GetHP() < 100 then
		monster:SetState(Monster.state.Excitement)
		print(monster:GetName() .. "�� �÷��̾ ���� ����� ���ϴ�.")
	else
		monster:SetState(Monster.state.Normal)
		print(monster:GetName() .. "�� �÷��̾ �ٶ󺸰��ִ�.")
	end
end

-- ���� ����
Slime.checkBattleTurn = function(player, monster)
	if monster:GetState() == monster.state.Fear then
		print(monster:GetName() .. "�� �̿� ���� �����̴�.")
		return true
	end
	return player:GetSpeed() >= monster:GetSpeed()
end

-- ���� �ൿ
Slime.battleMonsterTurn = function(player, monster, event)
	if monster:CheckMonsterAlive() == false or player:CheckPlayerAlive() == false then
		return
	end

	-- ���� ���� ���¿� ���� ���� / ��� / ���� �� ó��
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

-- ��Ʋ ���� �� ���� ����
Slime.provideBattleReward = function(player)
	player:IncreaseExp(Slime.exp)
	player:IncreaseGold(Slime.gold)
	for i = 0, #Slime.dropItem do
		if Slime.dropItem[i].chance > math.random() then
			player:AddItem(Slime.dropItem[i].id, Slime.dropItem[i].amount)
		end
	end
end