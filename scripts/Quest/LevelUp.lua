LevelUp = LevelUp or {}
Monster = Monster or {}

-- 퀘스트 설명
LevelUp.description = "레벨을 올리시오"
LevelUp.rarity = Quest.rarity.Common

-- 퀘스트 수락 조건 설정 및 확인
LevelUp.checkAcceptQuest = function(player)
	return player:GetGrade() >= 0 and
		player:GetLevel() >= 1
end

-- 퀘스트 완료 조건 설정
LevelUp.type = Quest.type.None
LevelUp.normalTarget = "1레벨 상승"

-- 퀘스트 완료 조건 확인
LevelUp.checkClearQuest = function(player, quest)
	return player:GetLevel() > 1
end

-- 퀘스트 완료 보상
LevelUp.reward = {
	exp = 101111,
	gold = 10111100,
	item = {
		[0] = {id = item.id.ITEM1, amount = 3}
	}
}