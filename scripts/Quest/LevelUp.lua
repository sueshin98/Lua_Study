LevelUp = LevelUp or {}
Monster = Monster or {}

-- ����Ʈ ����
LevelUp.description = "������ �ø��ÿ�"
LevelUp.rarity = Quest.rarity.Common

-- ����Ʈ ���� ���� ���� �� Ȯ��
LevelUp.checkAcceptQuest = function(player)
	return player:GetGrade() >= 0 and
		player:GetLevel() >= 1
end

-- ����Ʈ �Ϸ� ���� ����
LevelUp.type = Quest.type.None
LevelUp.normalTarget = "1���� ���"

-- ����Ʈ �Ϸ� ���� Ȯ��
LevelUp.checkClearQuest = function(player, quest)
	return player:GetLevel() > 1
end

-- ����Ʈ �Ϸ� ����
LevelUp.reward = {
	exp = 101111,
	gold = 10111100,
	item = {
		[0] = {id = item.id.ITEM1, amount = 3}
	}
}