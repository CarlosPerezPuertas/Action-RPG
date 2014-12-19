



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
		ghost[1]:setText("Habla con el guardian, te está esperando en la salida del pueblo.")
		ghost1[1]:setText("Te desbloquearé la puerta para que puedas pasar.")
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
					if tiledGetDoor("door01"):isClosed() then
					--	print("tiledGet OK")
						tiledGetDoor("door01"):open()
					end
					ghost[1]:setText("Muchas veces huir es la única escapatoria.")
					ghost1[1]:setText("Ahí fuera merodean alimañas y entes que actúan de forma incomprensible para nosotros. Ve con cuidado.")
					--door01:open()
				return true
			end
		end
	end

	return false
end




events = { ["InitQuest"] = initQuest, ["FirstQuest"] =  firstQuest}

--Update events
--When the events are triggered we delete them
function updateEvents()
	--print(isQuestFinished("InitQuest"))
	for n, trigger in pairs(events) do
		if trigger() then
			currentQuest = trigger
			--print(n, " is nil")
			events[n] = nil
		end
	end
end


--When we change level we destruct the entities and the info of the quests
--so when we return to the level the data is recorded in "currentQuest
function initQuests()


	currentQuest()
end


