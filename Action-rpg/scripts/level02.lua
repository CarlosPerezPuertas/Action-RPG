
--ghost1[1] = nil
--ghost[1] = nil



level02 = Level:new()
level02:addTexture(TextureType.Pacman, 'textures/link.png')
level02:addTexture(TextureType.Blinky, 'textures/ghost1.png')
level02:addTexture(TextureType.Pinky, 'textures/ghost2.png')
level02:addTexture(TextureType.Inky, 'textures/ghost3.png')
level02:addTexture(TextureType.Clyde, 'textures/ghost4.png')
level02:addTexture(201, 'textures/smoke_puffup.png')


ghost3 = {Npc:new(TextureType.Pinky)}
ghost3[1]:scale(2.5, 2.5)
ghost3[1]:setPosition(600, 300)
ghost3[1]:setCollisionRect(-5, 2, 10, 6)
ghost3[1]:moveRight(200)
ghost3[1]:moveLeft(200)
ghost3[1]:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 3, 20, 20);
ghost3[1]:addAnimationFrames(anim_type.go_right, "H", "Loop", 2,4, 20, 20);
ghost3[1]:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 1, 20, 20);
ghost3[1]:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 2, 20, 20);
ghost3[1]:setText("Largo de aqui!")
table.insert(entities, ghost3)

ghost4 = {Npc:new(TextureType.Inky)}
ghost4[1]:scale(2.5, 2.5)
ghost4[1]:setPosition(800, 200)
ghost4[1]:setCollisionRect(-5, 2, 10, 6)
ghost4[1]:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 3, 20, 20);
ghost4[1]:addAnimationFrames(anim_type.go_right, "H", "Loop", 2,4, 20, 20);
ghost4[1]:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 1, 20, 20);
ghost4[1]:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 2, 20, 20);
ghost4[1]:moveRight(100)
ghost4[1]:moveDown(200)
ghost4[1]:moveUp(50)
ghost4[1]:moveLeft(50)
ghost4[1]:moveUp(50)
ghost4[1]:moveLeft(50)
ghost4[1]:moveUp(50)
ghost4[1]:moveLeft(50)
ghost4[1]:setText("Segunda pantalla")
table.insert(entities, ghost4)


map02 = Map:new('maps/map02.tmx')
setViewTarget(hero, map02)

level02:addActor(hero)
level02:addActor(ghost3[1])
level02:addActor(ghost4[1])
level02:setMap(map02)

setLevel(level02)





