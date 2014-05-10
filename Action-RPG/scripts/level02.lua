


--ghost = nil
--ghost1 = nil
--Creation of objects and setup
--if ghost1 == nil then print("Ghost is nil") end


if ghost1[1] == nil then print("Ghost is nil") end

level02 = Level:new()
level02:addTexture(TextureType.Pacman, 'textures/celes.png')
level02:addTexture(TextureType.Blinky, 'textures/ghost1.png')
level02:addTexture(TextureType.Pinky, 'textures/ghost2.png')
level02:addTexture(TextureType.Inky, 'textures/ghost3.png')
level02:addTexture(TextureType.Clyde, 'textures/ghost4.png')


ghost3 = Npc:new(TextureType.Pinky)
ghost3:scale(2.5, 2.5)
ghost3:setPosition(600, 300)
ghost3:moveRight(200)
ghost3:moveLeft(200)
ghost3:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 3, 20, 20);
ghost3:addAnimationFrames(anim_type.go_right, "H", "Loop", 2,4, 20, 20);
ghost3:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 1, 20, 20);
ghost3:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 2, 20, 20);
ghost3:setText("¿Que haces aquí?")

ghost4 = Npc:new(TextureType.Inky)
ghost4:scale(2.5, 2.5)
ghost4:setPosition(800, 200)
ghost4:addAnimationFrames(anim_type.go_left, "H", "Loop", 2, 3, 20, 20);
ghost4:addAnimationFrames(anim_type.go_right, "H", "Loop", 2,4, 20, 20);
ghost4:addAnimationFrames(anim_type.go_up, "H", "Loop", 2, 1, 20, 20);
ghost4:addAnimationFrames(anim_type.go_down, "H", "Loop", 2, 2, 20, 20);
ghost4:moveRight(100)
ghost4:moveDown(200)
ghost4:moveUp(50)
ghost4:moveLeft(50)
ghost4:moveUp(50)
ghost4:moveLeft(50)
ghost4:moveUp(50)
ghost4:moveLeft(50)
ghost4:setText("Soy Blinky, ahora habla con Clyde")


map02 = Map:new('maps/map1.tmx')
setViewTarget(hero, map02)

level02:addActor(hero)
level02:addActor(ghost3)
level02:addActor(ghost4)
level02:setMap(map02)

setLevel(level02)





