BeginnerDungeon = BeginnerDungeon or {}
Monster = Monster or {}

-- 필드 입장 조건 설정 및 확인
BeginnerDungeon.checkEnterField = function(player)
	return player:GetGrade() >= 0 and
		player:GetLevel() >= 1
end

BeginnerDungeon.maxMonsterAmount = 10

BeginnerDungeon.monsterList = {
	[0] = {id = Monster.id.Slime, chance = 0.9},
	[1] = {id = Monster.id.Rat, chance = 0.5},
	--[2] = {id = Monster.id.Monster3, chance = 0.3},
	--[3] = {id = Monster.id.Monster4, chance = 0.1}
}

-- 몬스터 가중치에 따라 필드 젠 설정
BeginnerDungeon.generateMonster = function()
	local generatedMonsterList = {}
	local totalChance = 0

	for i = 0, #BeginnerDungeon.monsterList do
		totalChance = totalChance + BeginnerDungeon.monsterList[i].chance
	end

	for i = 1, BeginnerDungeon.maxMonsterAmount do	
		local randomValue = math.random() * totalChance
		local accumulatedChance = 0

		for j = 0, #BeginnerDungeon.monsterList do
			accumulatedChance = accumulatedChance + BeginnerDungeon.monsterList[j].chance
			if randomValue <= accumulatedChance then
				table.insert(generatedMonsterList, BeginnerDungeon.monsterList[j].id)
				break
			end
		end
	end

	return generatedMonsterList
end