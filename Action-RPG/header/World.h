#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

#include "Player.h"
#include "CommandQueue.h"
#include "SceneNode.h"
#include "Map.h"
#include "Collider.h"
#include "Level.h"
#include "LuaScripting.h"
#include "Camera.h"

#include "ScreenEffect.h"
#include "ScreenAffector.h"
#include "TextSistem.h"


class World
{
	public:
		explicit World(sf::RenderWindow &c_window, Player &c_player);

		void update(const sf::Time dt);
		void render();
		
		void doTransitions(sf::Time dt);
		void initLevel();
		void orderEntitiesByY();
		void updateEntitiesCollision();
		void updateMapCollision();
		void updateCamera(sf::Time dt);
		void broadcastCallbacks(sf::Time dt);
		void luaObjectsToNil();
		void deleteActors();
		bool isGameOverEnd();
		void drawLayers();

		
		CommandQueue& getCommandQueue(){ return command_queue; }
		inline void setFirstAnimation(int type){ first_animation = type; }
		inline int getFirstAnimation(){ return first_animation; }
	
	//Script function
	public:
		static bool levelLoaded(){ return is_level_loaded; }
		static int setLevel(lua_State *L);
		static int setViewTarget(lua_State *L);
		static int tiledGetDoor(lua_State *L);

	private:
		sf::RenderWindow &window;
		CommandQueue command_queue;
		TextSistem text_sistem;
		Collider collider;
		Player &player;
		static LuaScripting script_system;

		//First = exit , Second = enter
		std::pair<FadeAffector*, FadeAffector*> affector;
		std::queue<Effect*> screen_effects;

		int first_animation; //Initial animation taken from warp

	

		
	public:
		static Level* current_level;
		static Camera camera;
		static bool is_level_loaded;
		
	public:
		static bool is_new_level;
		static std::string level_script_name;
		bool is_level_initialized;
		bool is_transition;
		bool is_first_effect_initialized;
	
};

