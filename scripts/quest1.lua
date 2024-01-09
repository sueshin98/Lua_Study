quest1 = quest1 or {}
monster = monster or {}

-- ����Ʈ ����
quest1.description = "kill 10 monsters"
quest1.rarity = "Common"

-- ����Ʈ ���� ���� ���� �� Ȯ��
quest1.checkAcceptQuest = function(player)
	return player:GetPlayerGrade() >= 0 and
		player:GetPlayerLevel() >= 1
end

-- ����Ʈ �Ϸ� ���� ����
quest1.type = "Kill"
quest1.killTarget = {
	[0] = {id = monster.id.MONSTER1, amount = 1}
}

-- ����Ʈ �Ϸ� ���� Ȯ��
quest1.checkClearQuest = function(quest)
	return quest:CheckKillTarget()
	-- ���ǿ� ���� quest:CheckCollectTarget() ���� �Ѵٴ���...
end

-- ����Ʈ �Ϸ� ����
quest1.reward = {
	exp = 10000,
	gold = 10111100,
	item = {
		[0] = {id = item.id.ITEM1, amount = 1}
	}
}