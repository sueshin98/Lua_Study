quest2 = quest or {}

-- 각 퀘스트 마다 별개의 수락 조건 설정
quest2.checkAvailable = function(player)
	return player:GetQuestLevel() >= 0 and
		player:GetPlayerLevel() >= 10
end