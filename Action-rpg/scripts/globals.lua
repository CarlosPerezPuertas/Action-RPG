anim_type =
{
	none = 0,
	go_left = 1,
	go_right = 2,
	go_up = 3,
	go_down = 4
}

TextureType =
{
	None = 0,
	Pacman = 1,
	Blinky = 123,
	Pinky = 4,
	Inky = 5,
	Clyde = 5678,
}

--Entitities list to set entities to nil when deleted
entities = {}

hero = Hero:new(TextureType.Pacman)
hero:scale(1.5, 1.5)
hero:setPosition(360, 587)

hero:addAnimationFrames(anim_type.go_left, "V", "Loop", 4, 3, 48, 64);
hero:addAnimationFrames(anim_type.go_right, "V", "Loop", 4,4, 48, 64);
hero:addAnimationFrames(anim_type.go_up, "V", "Loop", 4, 2, 48, 64);
hero:addAnimationFrames(anim_type.go_down, "V", "Loop", 4, 1, 48, 64);










