quest2 = quest or {}

-- �� ����Ʈ ���� ������ ���� ���� ����
quest2.checkAvailable = function(player)
	return player:GetQuestLevel() >= 0 and
		player:GetPlayerLevel() >= 10
end