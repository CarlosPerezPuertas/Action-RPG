function isQuestFinished(quest)

	local finished = true

	for n, trigger in pairs(events) do
		if n == quest then
			finished = false
		end
	end

	return finished

end


function firstQuest()

	if not (ghost1[1] == nil) then
		if ghost1[1]:isTalking() then
				--Init second quest
				ghost1[1]:setText("Conmigo ya hablaste")
				ghost[1]:setText("Calla gilipollas")
			return true
		end
	end

	return false
end


function secondQuest()

	if not (ghost1[1] == nil) and not (ghost[1] == nil) then
		if isQuestFinished("FirstQuest") then
			if ghost[1]:isTalking() then
				ghost1[1]:setText("Clyde te odia")
				ghost[1]:setText("No vuelvas a hablarme")
				return true
			end
		end
	end

	return false
end

events = { ["FirstQuest"] =  firstQuest, ["SecondQuest"] =  secondQuest }


function setToNil(object)

	--entities[#entities][1] = nil
	--for a in values(entities) do
	for i = 1 , #entities do
		if entities[i][1] == object then
			print("Hola")
			entities[i][1] = nil
		end
	end

	--if ghost1[1] == nil then print("Ghost is nil") end
end


--Update events
--When the events are triggered we delete them
function updateEvents()
	for n, trigger in pairs(events) do
		if trigger() then
			events[n] = nil
		end
	end

	--print(isQuestFinished("FirstQuest"))
end


