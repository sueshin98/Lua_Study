quest1 = quest or {}

-- �� ����Ʈ ���� ������ ���� ���� ����
quest1.checkAvailable = function(player)
	return player:GetQuestLevel() >= 0 and
		player:GetPlayerLevel() >= 1
end

