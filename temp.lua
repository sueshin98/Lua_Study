quest1.checkAvailable = function(player)
	print (player:GetPlayerLevel())
	return player:GetQuestLevel() >= 0 and
		player:GetPlayerLevel() >= 10
end