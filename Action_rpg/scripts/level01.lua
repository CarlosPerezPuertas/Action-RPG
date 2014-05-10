--tab = {}

--x = {2}
--y = {4}

--table.insert(tab, x)
--table.insert(tab, y)

--tab[#tab] = nil

--for i = 1 , #tab do
	--tab[i][1] = nil
--end

--if x[1] == nil then print("is nil")
--else  print("is not nil") end





--Creation of objects and setup

level01 = Level:new()
level01:addTexture(TextureType.Pacman, 'textures/celes.png')
level01:addTexture(TextureType.Blinky, 'textures/ghost1.png')
level01:addTexture(TextureType.Pinky, 'textures/ghost2.png')
level01:addTexture(TextureType.Inky, 'textures/ghost3.png')
level01:addTexture(TextureType.Clyde, 'textures/ghost4.png')

--Make table to pass by reference
ghost = {Npc:new(TextureType.Clyde)}
ghost[1]:scale(2.5, 2.5)
ghost[1]:setPosition(200, 300)
ghost[1]:moveRight(200)
ghost[1]:moveLeft(200)
ghost[1]:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 3, 20, 20);
ghost[1]:addAnimationFrames(anim_type.go_right, "H", "Loop", 2,4, 20, 20);
ghost[1]:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 1, 20, 20);
ghost[1]:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 2, 20, 20);
ghost[1]:setText("¿Que haces aquí?")
table.insert(entities, ghost)


--tolua.takeownership(ghost)

ghost1 = {Npc:new(TextureType.Blinky)}
ghost1[1]:scale(2.5, 2.5)
ghost1[1]:setPosition(400, 200)
ghost1[1]:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 3, 20, 20);
ghost1[1]:addAnimationFrames(anim_type.go_right, "H", "Loop", 2,4, 20, 20);
ghost1[1]:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 1, 20, 20);
ghost1[1]:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 2, 20, 20);
ghost1[1]:moveRight(100)
ghost1[1]:moveDown(200)
ghost1[1]:moveUp(50)
ghost1[1]:moveLeft(50)
ghost1[1]:moveUp(50)
ghost1[1]:moveLeft(50)
ghost1[1]:moveUp(50)
ghost1[1]:moveLeft(50)
ghost1[1]:setText("Soy Blinky, ahora habla con Clyde")
table.insert(entities, ghost1)


--tolua.takeownership(ghost1)



map01 = Map:new('maps/map1.tmx')
--tolua.takeownership(map01)
setViewTarget(hero, map01)

level01:addActor(hero)
level01:addActor(ghost[1])
level01:addActor(ghost1[1])
level01:setMap(map01)



setLevel(level01)





