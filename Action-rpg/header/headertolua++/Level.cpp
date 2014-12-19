#include "..\header\Level.h"


Level::Level()
: pacman(nullptr)
, game_over(nullptr)
, lifes(nullptr)
, bonus(nullptr)
, labyrinth()
, scene_graph()
{
	loadResources();
	createScene();
	
}


Level::~Level()
{
}

void Level::loadResources()
{
	texture_generator.load(Textures::Pacman, "textures/pacman.png");
	texture_generator.load(Textures::Ghost1, "textures/ghost1.png");
	texture_generator.load(Textures::Ghost2, "textures/ghost2.png");
	texture_generator.load(Textures::Ghost3, "textures/ghost3.png");
	texture_generator.load(Textures::Ghost4, "textures/ghost4.png");
	texture_generator.load(Textures::SmallDot, "textures/small_dot.png");
	texture_generator.load(Textures::BigDot, "textures/big_dot_animated.png");
	texture_generator.load(Textures::Logo, "textures/Logotipo.png");
	texture_generator.load(Textures::Labyrinth, "textures/labyrinth.png");
	texture_generator.load(Textures::ScreenTransition1, "textures/effect02.png");
	texture_generator.load(Textures::Life, "textures/life.png");
	texture_generator.load(Textures::Cherry, "textures/cherry.png");
	texture_generator.load(Textures::Strawerry, "textures/strawerry.png");
	texture_generator.load(Textures::Peach, "textures/peach.png");
	texture_generator.load(Textures::Apple, "textures/apple.png");
	texture_generator.load(Textures::Key, "textures/key.png");
	texture_generator.load(Textures::Galaxian, "textures/galaxian.png");
	texture_generator.load(Textures::Grapes, "textures/grapes.png");
	texture_generator.load(Textures::Bell, "textures/bell.png");

	sounds.load(SoundEffect::EatPickup, "sfx/Pacman Eating Cherry.wav");
	sounds.load(SoundEffect::PacmanDies, "sfx/Pacman Dies.wav");
	sounds.load(SoundEffect::EatGhost, "sfx/Pacman Eating Ghost.wav");
	sounds.load(SoundEffect::Waka1, "sfx/waka1.wav");
	sounds.load(SoundEffect::Waka2, "sfx/waka2.wav");
	sounds.load(SoundEffect::Siren, "sfx/Pacman Siren.wav");
	sounds.load(SoundEffect::OneUp, "sfx/Pacman Extra Live.wav");
	sounds.load(SoundEffect::BigDot, "sfx/large+pellet+loop.wav");
	sounds.load(SoundEffect::Opening, "sfx/Pacman Opening Song.wav");

}

void Level::loadScripts(LuaScripting &script_system)
{

}


void Level::createScene()
{

	labyrinth.load("maps/pacman_board.tmx");

	SceneNode::PtrNode layer1(new SceneNode());
	layers.push_back(layer1.get());
	scene_graph.addChild(std::move(layer1));

	SceneNode::PtrNode layer2(new SceneNode());
	layers.push_back(layer2.get());
	scene_graph.addChild(std::move(layer2));

	 
	pacman = new Pacman();
	pacman->scale(sf::Vector2f(2.5f, 2.5f));
	pacman->setPosition(sf::Vector2f(360.f, 587.f));
	pacman->setSpeed(200, 0.8f);
	pacman->setVelRatio(1.f);
	addActor(pacman);
	
	

	Ghost *blinky = new Ghost(GhostType::Blinky);
	blinky->moveRight(120);
	blinky->scale(sf::Vector2f(2.5f, 2.5f));
	blinky->setPosition(sf::Vector2f(360.f, 299.f));
	blinky->setInitPos(sf::Vector2f(360.f, 299.f));
	blinky->desactivate();
	blinky->setRealRect(sf::FloatRect(0.f, 0.f, 2.f, 2.f)); //Stack overflow when is less square 
	blinky->setCurrentDirection(Direction::Right);
	blinky->setSpeed(100, 0.75f);
	blinky->desactivate(4.8f);
	addActor(blinky);


	std::unique_ptr<Ghost> g2(new Ghost(GhostType::Pinky, Textures::Ghost2, texture_generator));
	g2->setPosition(sf::Vector2f(372.f, 371.f));
	g2->setInitPos(sf::Vector2f(372.f, 371.f));
	g2->scale(sf::Vector2f(2.5f, 2.5f));
	g2->setRealRect(sf::FloatRect(0.f, 0.f, 2.f, 2.f));
	g2->desactivate();
	g2->setCurrentDirection(Direction::Left);
	g2->setSpeed(100, 0.75f);
	g2->desactivate(4.8f);
	ghosts.push_back(g2.get());
	node_vector.push_back(g2.get());
	layers[1]->addChild(std::move(g2));

	std::unique_ptr<Ghost> g3(new Ghost(GhostType::Inky, Textures::Ghost3, texture_generator));
	g3->setPosition(sf::Vector2f(312.f, 371.f));
	g3->setInitPos(sf::Vector2f(312.f, 371.f));
	g3->scale(sf::Vector2f(2.5f, 2.5f));
	g3->setRealRect(sf::FloatRect(0.f, 0.f, 2.f, 2.f));
	g3->desactivate();
	g3->setScatterTarget(988); //Look pacman dossier (Fixed Target Tiles)
	g3->setCaveReturnTarget(375);
	g3->setCurrentDirection(Direction::Right);
	g3->setSpeed(100, 0.75f);
	g3->setVelRatio(0.75f);
	g3->setCaveRatio(0.4f);
	g3->setFrightenedRatio(0.5f);
	g3->setExitCaveTime(6);
	g3->setFrightenedTime(6.f);
	g3->desactivate(4.8f);
	ghosts.push_back(g3.get());
	node_vector.push_back(g3.get());
	layers[1]->addChild(std::move(g3));

	std::unique_ptr<Ghost> g4(new Ghost(GhostType::Clyde, Textures::Ghost4, texture_generator));
	g4->setPosition(sf::Vector2f(408.f, 371.f));
	g4->setInitPos(sf::Vector2f(408.f, 371.f));
	g4->scale(sf::Vector2f(2.5f, 2.5f));
	g4->setRealRect(sf::FloatRect(0.f, 0.f, 2.f, 2.f));
	g4->desactivate();
	g4->setScatterTarget(961); //Look pacman dossier (Fixed Target Tiles)
	g4->setCaveReturnTarget(375);
	g4->setCurrentDirection(Direction::Left);
	g4->setSpeed(100, 0.75f);
	g4->setVelRatio(0.75f);
	g4->setCaveRatio(0.4f);
	g4->setFrightenedRatio(0.5f);
	g4->setExitCaveTime(8);
	g4->setFrightenedTime(6.f);
	g4->desactivate(4.8f);
	ghosts.push_back(g4.get());
	node_vector.push_back(g4.get());
	layers[1]->addChild(std::move(g4));

	std::vector<sf::FloatRect> warp_rect = labyrinth.getObjectGroup().warp_rects;
	std::vector<sf::Vector2f>  warp_dest = labyrinth.getObjectGroup().warp_destinies;

	for (unsigned int i = 0; i < warp_rect.size(); ++i)
	{
		std::unique_ptr<Warp> warp(new Warp(sf::RectangleShape(sf::Vector2f(warp_rect[i].width, warp_rect[i].height))));
		float x_corrected = warp_rect[i].left * 2.f + labyrinth.getPosition().x;
		float y_corrected = warp_rect[i].top  * 2.f + labyrinth.getPosition().y;
		float x_destiny_corrected = warp_dest[i].x * 2.f + labyrinth.getPosition().x;
		float y_destiny_corrected = warp_dest[i].y * 2.f + labyrinth.getPosition().y;
		warp->setPosition(sf::Vector2f(x_corrected, y_corrected));
		warp->setDestiny(sf::Vector2f(x_destiny_corrected, y_destiny_corrected));
		warp->scale(sf::Vector2f(2.f, 2.f));
		node_vector.push_back(warp.get());
		layers[0]->addChild(std::move(warp));
	}

	std::unique_ptr<Text> high_score_text(new Text("HIGH SCORE", "fonts/Press Start Regular.ttf", 15));
	high_score_text->setPosition(sf::Vector2f(380.f, -40.f));
	node_vector.push_back(high_score_text.get());
	layers[0]->addChild(std::move(high_score_text));

	std::unique_ptr<Text> high_score(new Text(std::to_string(pacman->getHighScore()), "fonts/Press Start Regular.ttf", 15, TextType::HighScore));
	high_score->setPosition(sf::Vector2f(410.f, -10.f));
	node_vector.push_back(high_score.get());
	layers[0]->addChild(std::move(high_score));

	std::unique_ptr<Text> one_up(new Text("1UP", "fonts/Press Start Regular.ttf", 15));
	one_up->setPosition(sf::Vector2f(220.f, -40.f));
	node_vector.push_back(one_up.get());
	layers[0]->addChild(std::move(one_up));

	std::unique_ptr<Text> score(new Text("00", "fonts/Press Start Regular.ttf", 15, TextType::Score));
	score->setPosition(sf::Vector2f(220.f, -10.f));
	node_vector.push_back(score.get());
	layers[0]->addChild(std::move(score));

	std::unique_ptr<Text> player_one(new Text("PLAYER ONE", "fonts/Press Start Regular.ttf", 22, TextType::Static, sf::Color(0, 255, 255, 255)));
	player_one->setPosition(sf::Vector2f(250.f, 285.f));
	player_one->setLifeTime(4.8f);
	node_vector.push_back(player_one.get());
	layers[0]->addChild(std::move(player_one));

	std::unique_ptr<Text> ready(new Text("READY!", "fonts/Press Start Regular.ttf", 22, TextType::Static, sf::Color(255, 255, 0, 255)));
	ready->setPosition(sf::Vector2f(295.f, 430.f));
	ready->setLifeTime(4.8f);
	node_vector.push_back(ready.get());
	layers[0]->addChild(std::move(ready));

	std::unique_ptr<ImageContainer> lifes_container(new ImageContainer(ContainerType::Lifes));
	lifes = lifes_container.get();
	lifes_container->setContainerMode(ContainerMode::Horizontal);
	lifes_container->setPosition(sf::Vector2f(80.f, 780.f));
	lifes_container->scale(sf::Vector2f(2.f, 2.f));
	lifes_container->pushBack(Textures::Life, texture_generator);
	lifes_container->pushBack(Textures::Life, texture_generator);
	node_vector.push_back(lifes_container.get());
	layers[0]->addChild(std::move(lifes_container));

	std::unique_ptr<ImageContainer> bonus_container(new ImageContainer(ContainerType::Pickups));
	bonus = bonus_container.get();
	bonus_container->setContainerMode(ContainerMode::Horizontal);
	bonus_container->setPosition(sf::Vector2f(660.f, 780.f));
	bonus_container->scale(sf::Vector2f(2.f, 2.f));
	node_vector.push_back(bonus_container.get());
	layers[0]->addChild(std::move(bonus_container));
	//nextBonus();

	//Insert dots
	//restartDots();

	std::unique_ptr<SoundNode> sound_eat_pickup(new SoundNode(SoundEffect::EatPickup, sounds));
	node_vector.push_back(sound_eat_pickup.get());
	layers[0]->addChild(std::move(sound_eat_pickup));

	std::unique_ptr<SoundNode> sound_pacman_dies(new SoundNode(SoundEffect::PacmanDies, sounds));
	node_vector.push_back(sound_pacman_dies.get());
	layers[0]->addChild(std::move(sound_pacman_dies));

	std::unique_ptr<SoundNode> sound_waka1(new SoundNode(SoundEffect::Waka1, SoundEffect::Waka2, sounds));
	node_vector.push_back(sound_waka1.get());
	layers[0]->addChild(std::move(sound_waka1));

	std::unique_ptr<SoundNode> sound_siren(new SoundNode(SoundEffect::Siren, sounds));
	node_vector.push_back(sound_siren.get());
	sound_siren->playAfter(4.8f);
	sound_siren->setLoop(true);
	layers[0]->addChild(std::move(sound_siren));

	std::unique_ptr<SoundNode> sound_eat_ghost(new SoundNode(SoundEffect::EatGhost, sounds));
	node_vector.push_back(sound_eat_ghost.get());
	layers[0]->addChild(std::move(sound_eat_ghost));

	std::unique_ptr<SoundNode> sound_one_up(new SoundNode(SoundEffect::OneUp, sounds));
	node_vector.push_back(sound_one_up.get());
	layers[0]->addChild(std::move(sound_one_up));

	std::unique_ptr<SoundNode> sound_big_dot(new SoundNode(SoundEffect::BigDot, sounds));
	node_vector.push_back(sound_big_dot.get());
	layers[0]->addChild(std::move(sound_big_dot));

	std::unique_ptr<SoundNode> sound_opening(new SoundNode(SoundEffect::Opening, sounds));
	node_vector.push_back(sound_opening.get());
	sound_opening->play();
	layers[0]->addChild(std::move(sound_opening));

}


//We register the pickup objects that will be displayed depending on the level
//The info (scores and levels) is taken from : http://nrchapman.com/pacman/
void Level::registerPickups()
{
	pickup_factory[1] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Cherry, Textures::Cherry, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(100);
		return pickup;
	};

	pickup_factory[2] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Strawerry, Textures::Strawerry, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(300);
		return pickup;
	};

	pickup_factory[3] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Peach, Textures::Peach, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(500);
		return pickup;
	};

	pickup_factory[4] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Peach, Textures::Peach, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(500);
		return pickup;
	};

	pickup_factory[5] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Apple, Textures::Apple, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(700);
		return pickup;
	};

	pickup_factory[6] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Apple, Textures::Apple, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(700);
		return pickup;
	};

	pickup_factory[7] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Grapes, Textures::Grapes, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(1000);
		return pickup;
	};

	pickup_factory[8] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Grapes, Textures::Grapes, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(1000);
		return pickup;
	};

	pickup_factory[9] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Galaxian, Textures::Galaxian, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(2000);
		return pickup;
	};

	pickup_factory[10] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Galaxian, Textures::Galaxian, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(2000);
		return pickup;
	};

	pickup_factory[11] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Bell, Textures::Bell, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(3000);
		return pickup;
	};

	pickup_factory[12] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Bell, Textures::Bell, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(3000);
		return pickup;
	};

	pickup_factory[13] = [this]()
	{
		std::unique_ptr<PickupObject> pickup(new PickupObject(Pickup::Key, Textures::Key, texture_generator));
		pickup->setLifeTime(6.f);
		pickup->setPosition(sf::Vector2f(350.f, 435.f));
		pickup->scale(sf::Vector2f(2.3f, 2.3f));
		pickup->setScore(5000);
		return pickup;
	};
}

/*void Level::addActor(SceneNode *node)
{

}*/

