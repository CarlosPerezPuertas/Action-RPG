
--Creation of objects and setup


level01 = Level:new()
level01:addTexture(TextureType.Pacman, 'textures/link.png')
level01:addTexture(TextureType.Blinky, 'textures/ghost1.png')
level01:addTexture(TextureType.Pinky, 'textures/ghost2.png')
level01:addTexture(TextureType.Inky, 'textures/ghost3.png')
level01:addTexture(TextureType.Clyde, 'textures/ghost4.png')
level01:addTexture(201, 'textures/smoke_puffup.png')

--Make table to pass by reference
ghost = {Npc:new(TextureType.Clyde)}
ghost[1]:scale(2.5, 2.5)
ghost[1]:setPosition(500, 400)
ghost[1]:setCollisionRect(-5, 2, 10, 6)
--ghost[1]:moveRight(200)
--ghost[1]:moveLeft(200)
ghost[1]:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 40, 20, 20);
ghost[1]:addAnimationFrames(anim_type.go_right, "H", "Loop", 2, 60, 20, 20);
ghost[1]:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 0, 20, 20);
ghost[1]:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 20, 20, 20);
table.insert(entities, ghost)


--tolua.takeownership(ghost)

ghost1 = {Npc:new(TextureType.Blinky)}
ghost1[1]:scale(2.5, 2.5)
ghost1[1]:setPosition(800, 150)
ghost1[1]:setCollisionRect(-5, 2, 10, 6)
ghost1[1]:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 40, 20, 20);
ghost1[1]:addAnimationFrames(anim_type.go_right, "H", "Loop", 2,60, 20, 20);
ghost1[1]:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 0, 20, 20);
ghost1[1]:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 20, 20, 20);
--ghost1[1]:moveUp(50)
--ghost1[1]:moveLeft(50)
--ghost1[1]:moveLeft(50)
--ghost1[1]:moveUp(50)
--ghost1[1]:moveLeft(50)
table.insert(entities, ghost1)


--tolua.takeownership(ghost1)



map01 = Map:new('maps/map01.tmx')
--tolua.takeownership(map01)
setViewTarget(hero, map01)

level01:addActor(hero)
level01:addActor(ghost[1])
level01:addActor(ghost1[1])
level01:setMap(map01)


setLevel(level01)





