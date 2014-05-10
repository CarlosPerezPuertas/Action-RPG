#include "..\header\World.h"
#include "..\header\Hero.h"


 //std::unique_ptr<Level> World::current_level(nullptr);

 Level* World::current_level = nullptr;
 Camera World::camera;
 bool World::is_new_level = false;

 bool compareY(SceneNode* i, SceneNode* j) { return (i->getPosition().y + i->getOrigin().y < j->getPosition().y + j->getOrigin().y); }

World::World(sf::RenderWindow &c_window, Player &c_player)
: window(c_window)
, player(c_player)
, command_queue()
, collider(*this, command_queue, player, script_system)
, isGameOver(false)
{
	//Map is loaded in the level script then is assigned to collider as a reference
	script_system.loadScript("scripts/globals.lua");
	script_system.loadScript("scripts/level01.lua");
	
	script_system.loadScript("scripts/quests.lua");
	window.setView(camera);

	collider.setMap(current_level->getMap().get());

	
	
	
	


	//scale_factor = (840.f / desktop.height) + 0.12f;
	//camera.setCenter(720.f / 2.f, 840.f / 2.f - 30.f);
	//camera.setSize(sf::Vector2f(desktop.width * scale_factor, desktop.height * scale_factor));
	
}





void World::update(const sf::Time dt)
{
	//std::cout << "Uno" <<  std::endl;
	
	initLevel();
	
	//std::cout << "Dos" << std::endl;
    window.setView(World::camera);
	//std::cout << "Tres" << std::endl;
	orderEntitiesByY();
	//std::cout << "Cuatro" << std::endl;
	script_system.loadScript("scripts/QuestUpdating.lua");
	
	
	updateMapCollision();
	//std::cout << "Cinco" << std::endl;
	
	updateEntitiesCollision();
	//std::cout << "Siete" << std::endl;
	broadcastCallbacks(dt);
	
	//std::cout << "Seis" << std::endl;
	
	
	
	

	//std::cout << "Lua stack " << lua_gettop(script_system.getLuaState()) << std::endl;
	lua_settop(script_system.getLuaState(), 1);
	//std::cout << "Ocho" << std::endl;
	camera.update(command_queue, dt, *current_level, window);
	//std::cout << "Nueve" << std::endl;
	
	//deleteActors();
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
	if (World::is_new_level)
	{
		for (auto &i : World::current_level->getSceneVector())
		{
			if (i->getCategory() == Category::Npc)
			{
				lua_getglobal(script_system.getLuaState(), "setToNil");
				tolua_pushusertype(script_system.getLuaState(), (void*)i, "Npc");
				lua_call(script_system.getLuaState(), 1, 1); //1 argumento 1 resultado
			}
			
		}
		


		script_system.loadScript("scripts/level02.lua");
		
		World::is_new_level = false;
		collider.setMap(current_level->getMap().get());
	}
}


void World::updateEntitiesCollision()
{
	//std::cout << "size " << World::current_level->getSceneVector().size() << std::endl;
	//if (World::current_level->getSceneVector().size() > 3)
	collider.checkSceneCollision(World::current_level->getSceneVector());
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

	//for (auto &itr : ghosts) collider.checkMapCollision(*itr); 

}

void World::broadcastCallbacks(sf::Time dt)
{
	while (command_queue.isEmpty() == false)
	{
		World::current_level->getSceneGraph().recieveCommand(command_queue.pop(), dt);
	}
	World::current_level->getSceneGraph().update(command_queue, dt);
}

void World::drawLayers()
{
	if (World::current_level != nullptr)
	for (int i = 0; i < 3; i++)
	{
		World::current_level->getMap()->draw_layer(window, i);

		if (i == 1)
		{
			for (auto j : World::current_level->getSceneVector()) window.draw(*j);
		}
		else if (i == 0 || i > 1) window.draw(*World::current_level->getLayer(i));
		
		//window.draw(*World::current_level->getMap());
		//window.draw(World::current_level->getSceneGraph());
	}
}



bool World::isGameOverEnd()
{
	//if (isGameOver == true && game_over == nullptr) { std::cout << "Game over end" << std::endl; return true; }
	return false;
}

// Check for the objects marked as removable and remove it from the scene
void World::deleteActors()
{
	//World::current_level->getSceneGraph().deleteRemovable(World::current_level->getSceneVector());
}

//Script function
int World::setLevel(lua_State *L)
{
	if (World::current_level != nullptr)
	{
		//World::is_new_level = true;
		//current_level.release();
		World::is_new_level = true;
		//delete current_level;
		for (auto &i : World::current_level->getSceneVector())
		{
			if (i->getCategory() != Category::Player)
			Mtolua_delete(i);
		}

		Mtolua_delete(World::current_level->getMap().get());
		
		//Mtolua_delete(current_level);
		std::cout << "TOLUA DELETE" << std::endl;
	}

	
	
   //Level* result = current_level.release();
	
   //current_level.reset(static_cast<Level*>(tolua_touserdata(L, -1, NULL)));
	//current_level = std::move(std::unique_ptr<Level>(static_cast<Level*>(tolua_touserdata(L, 1, NULL))));
	current_level = (static_cast<Level*>(tolua_touserdata(L, 1, NULL)));
	

	
	std::cout << "size " << current_level->getEntitiesNumber() << std::endl;
	

	return 0;
}

int World::setViewTarget(lua_State *L)
{
	SceneNode *m_player = static_cast<SceneNode*>(tolua_touserdata(L, 1, NULL));
	Map *map = static_cast<Map*>(tolua_touserdata(L, 2, NULL));
	
	World::camera.setTarget(*m_player, *map);

	return 0;
}
