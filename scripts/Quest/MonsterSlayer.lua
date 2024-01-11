MonsterSlayer = MonsterSlayer or {}
Monster = Monster or {}

-- ����Ʈ ����
MonsterSlayer.description = "������ ���͵��� ����Ͻÿ�"
MonsterSlayer.rarity = Quest.rarity.Common

-- ����Ʈ ���� ���� ���� �� Ȯ��
MonsterSlayer.checkAcceptQuest = function(player)
	return player:GetGrade() >= 0 and
		player:GetLevel() >= 1
end

-- ����Ʈ �Ϸ� ���� ����
MonsterSlayer.type = Quest.type.Kill
MonsterSlayer.killTarget = {
	[0] = {id = Monster.id.Slime, amount = 1}
}

-- ����Ʈ �Ϸ� ���� Ȯ��
MonsterSlayer.checkClearQuest = function(player, quest)
	return uest:CheckKillTarget()
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