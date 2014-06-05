#include "..\header\World.h"
#include "..\header\Hero.h"
#include "..\header\HeroPanel.h"
#include "..\header\Npc.h"



 //std::unique_ptr<Level> World::current_level(nullptr);

 Level* World::current_level = nullptr;
 Camera World::camera;
 bool World::is_new_level = false;
 std::string World::level_script_name = "Empty";

 bool compareY(SceneNode* i, SceneNode* j) { return (i->getPosition().y + i->getOrigin().y < j->getPosition().y + j->getOrigin().y); }

World::World(sf::RenderWindow &c_window, Player &c_player)
: window(c_window)
, player(c_player)
, command_queue()
, collider(*this, command_queue, text_sistem, c_player, script_system)
, is_transition(true)
//, exit_enter_effect(std::make_pair(new ScreenEffect(sf::Sprite()), new ScreenEffect(sf::Sprite())))
, affector(std::make_pair(new FadeAffector(0.5, 1.0), new FadeAffector(1.0, 0.0)))
, is_level_initialized(false)
, is_first_effect_initialized(false)
, first_animation(0)
{
	//Map is loaded in the level script then is assigned to collider as a reference
	script_system.loadScript("scripts/globals.lua");
	script_system.loadScript("scripts/level01.lua");
	script_system.loadScript("scripts/quests.lua");
	script_system.loadScript("scripts/quest_data_init.lua");
	
	window.setView(camera);
	collider.setMap(current_level->getMap().get());	
	current_level->initCameraSettings();
	player.setPlayer(current_level->getHero());
}




void World::update(const sf::Time dt)
{
	if (World::is_new_level) doTransitions(dt);	
	if (World::is_new_level == false)
	{
		orderEntitiesByY();
		broadcastCallbacks(dt);
		updateEntitiesCollision();
		updateMapCollision();
	}

	updateCamera(dt);
	deleteActors();
}

void World::render()
{
	drawLayers();	
}


void World::orderEntitiesByY()
{
	if (World::current_level->getSceneVector().size() > 2)
	std::sort(World::current_level->getSceneVector().begin(), World::current_level->getSceneVector().end(), compareY);
}

void World::initLevel()
{
	is_level_initialized = true;
	deleteActors();
	script_system.loadScript(World::level_script_name);
	script_system.loadScript("scripts/quest_data_init.lua");
	collider.setMap(current_level->getMap().get());
	current_level->initCameraSettings();	
	player.setPlayer(current_level->getHero());
	current_level->getHero()->changeAnimation(getFirstAnimation());	
}

void World::doTransitions(sf::Time dt)
{
	if (is_first_effect_initialized == false)
	{
		Effect* out_effect(new Effect(sf::Sprite()));
		out_effect->setLifeTime(1.f);
		out_effect->addClearRectangle();
		out_effect->screenOn();
		affector.first->restart(0.5, 1.0);
		out_effect->addAffector(*affector.first);
		screen_effects.push(out_effect);
		World::current_level->addActorWithoutSprite(out_effect, 4);

		player.disable();
		is_first_effect_initialized = true;
	}

	//std::cout << screen_effects.front()->isRunning() << " " << screen_effects.size()  << std::endl;

	screen_effects.front()->updateScreen(dt);

	if (!screen_effects.front()->isRunning())
	{
		if (is_level_initialized == false) //out screen
		{
			screen_effects.front()->removeFromScene();
			screen_effects.pop();
			
			broadcastCallbacks(dt);
			initLevel();
			
			Effect *black_screen(new Effect(sf::Sprite()));
			black_screen->setLifeTime(1.f);
			black_screen->addClearRectangle();
			black_screen->screenOn();
			screen_effects.push(black_screen);
			World::current_level->addActorWithoutSprite(black_screen, 4);

			Effect* in_effect(new Effect(sf::Sprite()));
			in_effect->setLifeTime(1.f);
			in_effect->addClearRectangle();
			in_effect->screenOn();
			affector.second->restart(1.0, 0.0);
			in_effect->addAffector(*affector.second);
			screen_effects.push(in_effect);
			World::current_level->addActorWithoutSprite(in_effect, 4);

		}
		else if (screen_effects.size() == 2) //Black screen
		{
			screen_effects.front()->removeFromScene();
			screen_effects.pop();
		}
		else if (screen_effects.size() == 1) //In screeen
		{
			screen_effects.front()->removeFromScene();
			screen_effects.pop();
			World::is_new_level = false;
			is_level_initialized = false;
			is_first_effect_initialized = false;
			player.enable();
			
		}
	}
}


void World::updateEntitiesCollision()
{
	collider.checkSceneCollision(World::current_level->getSceneVector());
	script_system.loadScript("scripts/QuestUpdating.lua");
}


void World::updateMapCollision()
{
	Command player_map_collision;
	player_map_collision.category = Category::Player;
	player_map_collision.action = get_function<Hero>([this](Hero &m_player, sf::Time dt)
	{
		collider.checkMapCollision(m_player);
	});
	command_queue.push(player_map_collision);

	Command npc_map_collision;
	npc_map_collision.category = Category::Npc;
	npc_map_collision.action = get_function<Npc>([this](Npc &npc, sf::Time dt)
	{
		collider.checkMapCollision(npc);
	});
	command_queue.push(npc_map_collision);
}

void  World::updateCamera(sf::Time dt)
{
	camera.update(command_queue, dt, *current_level, window);
	window.setView(World::camera);
}

void World::broadcastCallbacks(sf::Time dt)
{
	while (command_queue.isEmpty() == false)
	{
		World::current_level->getSceneGraph().recieveCommand(command_queue.pop(), dt);
	}
	World::current_level->getSceneGraph().update(command_queue, dt);
	text_sistem.update(dt);
}



void World::drawLayers()
{
	if (World::current_level != nullptr)
	for (int i = 0; i < 5; i++)
	{
		World::current_level->getMap()->draw_layer(window, i);

		if (i == 1)
		{
			for (auto j : World::current_level->getSceneVector())if (j->getCategory() != Category::ScreenEffect) window.draw(*j);
		}
		else if (i == 0 || i > 1) window.draw(*World::current_level->getLayer(i));
	}

	if (World::is_new_level)
	{
		for (auto j : World::current_level->getSceneVector())
		{
			if (j->getCategory() == Category::ScreenEffect)
			{
				window.draw(*j);
			}
		}	
	}	
}


bool World::isGameOverEnd()
{
	
	//if (isGameOver == true && game_over == nullptr) { std::cout << "Game over end" << std::endl; return true; }
	return false;
}

void  World::luaObjectsToNil()
{
	//Set to nil lua objects
	for (auto *i : World::current_level->getSceneVector())
	{
		if (i->isRemovable() == true || is_new_level)
		if (i->getCategory() == Category::Npc)
		{
			lua_getglobal(script_system.getLuaState(), "setToNil");
			tolua_pushusertype(script_system.getLuaState(), (void*)i, "Npc");
			lua_call(script_system.getLuaState(), 1, 1); //1 argumento 1 resultado
		}
	}

}

// Check for the objects marked as removable and remove it from the scene
void World::deleteActors()
{
	luaObjectsToNil();
	World::current_level->getSceneGraph().deleteRemovable(World::current_level->getSceneVector());
	lua_settop(script_system.getLuaState(), 1);
}

//Script function
int World::setLevel(lua_State *L)
{
	if (World::current_level != nullptr)
	{
		for (auto &i : World::current_level->getSceneVector())
		{
			if (i != nullptr)
			if (i->getCategory() != Category::Player)
			{
				Mtolua_delete(i);
				i = nullptr;
			}
		}
		Mtolua_delete(World::current_level->getMap().get());
	}
	current_level = (static_cast<Level*>(tolua_touserdata(L, 1, NULL)));
	//std::cout << "size " << current_level->getEntitiesNumber() << std::endl;
	
	return 0;
}

int World::setViewTarget(lua_State *L)
{
	SceneNode *m_player = static_cast<SceneNode*>(tolua_touserdata(L, 1, NULL));
	Map *map = static_cast<Map*>(tolua_touserdata(L, 2, NULL));
	
	World::camera.setTarget(*m_player, *map);

	return 0;
}
