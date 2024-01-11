Forest = Forest or {}
Monster = Monster or {}

-- 필드 입장 조건 설정 및 확인
Forest.checkEnterField = function(player)
	return player:GetGrade() >= 0 and
		player:GetLevel() >= 2
end

Forest.maxMonsterAmount = 5

Forest.monsterList = {
	[0] = {id = Monster.id.Slime, chance = 0.9},
	[1] = {id = Monster.id.Rat, chance = 0.5},
	--[2] = {id = Monster.id.Monster3, chance = 0.3},
	--[3] = {id = Monster.id.Monster4, chance = 0.1}
}

-- 몬스터 가중치에 따라 필드 젠 설정
Forest.generateMonster = function()
	local generatedMonsterList = {}
	local totalChance = 0

	for i = 0, #Forest.monsterList do
		totalChance = totalChance + Forest.monsterList[i].chance
	end

	for i = 1, Forest.maxMonsterAmount do	
		local randomValue = math.random() * totalChance
		local accumulatedChance = 0

		for j = 0, #Forest.monsterList do
			accumulatedChance = accumulatedChance + Forest.monsterList[j].chance
			if randomValue <= accumulatedChance then
				table.insert(generatedMonsterList, Forest.monsterList[j].id)
				break
			end
		end
	end

	return generatedMonsterList
end