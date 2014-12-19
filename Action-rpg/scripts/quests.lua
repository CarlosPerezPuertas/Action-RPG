



function isQuestFinished(quest)

	local finished = true

	for n, trigger in pairs(events) do
		if n == quest then
			finished = false
		end
	end

	return finished

end


function initQuest()
	if not (ghost1[1] == nil) and not (ghost[1] == nil) then
		ghost[1]:setText("Soy Blinky, ahora habla con Clyde. \nCreo que no le caes muy bien porque le robas. Ten mucho cuidado con el")
		ghost1[1]:setText("¿Que haces aquí?")
		return true
	end

	return false

end

currentQuest = initQuest


function firstQuest()
	if not (ghost1[1] == nil) then
		if isQuestFinished("InitQuest") then
			--print(ghost1[1]:isTalking(), " SECOND QUEST")
			if ghost1[1]:isTalking() or firstQuest == currentQuest  then
					--Init second quest
					ghost1[1]:setText("Conmigo ya hablaste")
					ghost[1]:setText("Calla gilipollas")
				return true
			end
		end
	end

	return false
end


function secondQuest()
	if not (ghost1[1] == nil) and not (ghost[1] == nil) then
		if isQuestFinished("FirstQuest") then
			if ghost[1]:isTalking() or secondQuest == currentQuest then
				ghost1[1]:setText("Clyde te odia")
				ghost[1]:setText("No vuelvas a hablarme")
				return true
			end
		end
	end

	return false
end

events = { ["InitQuest"] = initQuest, ["FirstQuest"] =  firstQuest, ["SecondQuest"] =  secondQuest }

--Update events
--When the events are triggered we delete them
function updateEvents()
	--print(isQuestFinished("InitQuest"))
	for n, trigger in pairs(events) do
		if trigger() then
			currentQuest = trigger
			print(n, " is nil")
			events[n] = nil
		end
	end
end


--When we change level we destruct the entities and the info of the quests
--so when we return to the level the data is recorded in "currentQuest
function initQuests()
	currentQuest()
end


