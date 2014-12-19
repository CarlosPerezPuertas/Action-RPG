anim_type =
{
	none = 0,
	go_left = 1,
	go_right = 2,
	go_up = 3,
	go_down = 4,
	sword01_left = 5,
	sword01_right = 6,
	sword01_up = 7,
	sword01_down = 8,
	die = 9
}

TextureType =
{
	None = 0,
	Pacman = 1,
	Blinky = 123,
	Pinky = 4,
	Inky = 5,
	Clyde = 5678,
	Alien = 7
}

--Entitities list to set entities to nil when deleted
entities = {}
--currentQuest = 0

hero = Hero:new(TextureType.Pacman)
hero:scale(3.0, 3.0)
hero:setPosition(360, 587)
hero:setCollisionRect(-5, 2, 10, 10)


hero:addAnimationFrames(anim_type.go_left, "H", "Loop", 9, 75, 25, 25);
hero:addAnimationFrames(anim_type.go_right, "H", "Loop", 9,50, 25, 25);
hero:addAnimationFrames(anim_type.go_up, "H", "Loop", 9, 25, 25, 25);
hero:addAnimationFrames(anim_type.go_down, "H", "Loop", 9, 0, 25, 25);
hero:addAnimationFrames(anim_type.sword01_left, "H", "OneLoop", 7, 250, 50, 50);
hero:addAnimationFrames(anim_type.sword01_right, "H", "OneLoop", 7,200, 50, 50);
hero:addAnimationFrames(anim_type.sword01_up, "H", "OneLoop", 6, 150, 50, 50);
hero:addAnimationFrames(anim_type.sword01_down, "H", "OneLoop", 7, 100, 50, 50);


--Functions

function setToNil(object)
	for i = 1 , #entities do
		if entities[i][1] == object then
			entities[i][1] = nil
		end
	end
end





