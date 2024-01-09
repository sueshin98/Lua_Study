quest1 = quest1 or {}
monster = monster or {}

-- 퀘스트 설명
quest1.description = "kill 10 monsters"
quest1.rarity = "Common"

-- 퀘스트 수락 조건 설정 및 확인
quest1.checkAcceptQuest = function(player)
	return player:GetPlayerGrade() >= 0 and
		player:GetPlayerLevel() >= 1
end

-- 퀘스트 완료 조건 설정
quest1.type = "Kill"
quest1.killTarget = {
	[0] = {id = monster.id.MONSTER1, amount = 1}
}

-- 퀘스트 완료 조건 확인
quest1.checkClearQuest = function(quest)
	return quest:CheckKillTarget()
	-- 조건에 따라 quest:CheckCollectTarget() 등을 한다던가...
end

-- 퀘스트 완료 보상
quest1.reward = {
	exp = 10000,
	gold = 10111100,
	item = {
		[0] = {id = item.id.ITEM1, amount = 1}
	}
}