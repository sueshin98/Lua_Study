MonsterSlayer = MonsterSlayer or {}
monster = monster or {}

-- ����Ʈ ����
MonsterSlayer.description = "������ ���͵��� ����Ͻÿ�"
MonsterSlayer.rarity = quest.rarity.Common

-- ����Ʈ ���� ���� ���� �� Ȯ��
MonsterSlayer.checkAcceptQuest = function(player)
	return player:GetPlayerGrade() >= 0 and
		player:GetPlayerLevel() >= 1
end

-- ����Ʈ �Ϸ� ���� ����
MonsterSlayer.type = quest.type.Kill
MonsterSlayer.killTarget = {
	[0] = {id = monster.id.MONSTER1, amount = 1},
	[1] = {id = monster.id.MONSTER2, amount = 1},
	[2] = {id = monster.id.MONSTER3, amount = 100}
}

-- ����Ʈ �Ϸ� ���� Ȯ��
MonsterSlayer.checkClearQuest = function(player, quest)
	return quest:CheckKillTarget()
	-- ���ǿ� ���� quest:CheckCollectTarget() ���� �Ѵٴ���...
end

-- ����Ʈ �Ϸ� ����
MonsterSlayer.reward = {
	exp = 101111,
	gold = 10111100,
	item = {
		[0] = {id = item.id.ITEM1, amount = 3}
	}
}