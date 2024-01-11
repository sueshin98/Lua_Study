MonsterSlayer = MonsterSlayer or {}
Monster = Monster or {}

-- 퀘스트 설명
MonsterSlayer.description = "지정된 몬스터들을 사냥하시오"
MonsterSlayer.rarity = Quest.rarity.Common

-- 퀘스트 수락 조건 설정 및 확인
MonsterSlayer.checkAcceptQuest = function(player)
	return player:GetGrade() >= 0 and
		player:GetLevel() >= 1
end

-- 퀘스트 완료 조건 설정
MonsterSlayer.type = Quest.type.Kill
MonsterSlayer.killTarget = {
	[0] = {id = Monster.id.Slime, amount = 1}
}

-- 퀘스트 완료 조건 확인
MonsterSlayer.checkClearQuest = function(player, quest)
	return uest:CheckKillTarget()
	-- 조건에 따라 quest:CheckCollectTarget() 등을 한다던가...
end

-- 퀘스트 완료 보상
MonsterSlayer.reward = {
	exp = 101111,
	gold = 10111100,
	item = {
		[0] = {id = item.id.ITEM1, amount = 3}
	}
}