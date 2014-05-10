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




class World
{
	public:
		explicit World(sf::RenderWindow &c_window, Player &c_player);
		

		void update(const sf::Time dt);
		void render();

		void initLevel();
		void updateEntitiesCollision();
		void updateMapCollision();
		void orderEntitiesByY();
		void broadcastCallbacks(sf::Time dt);
		void drawLayers();

		bool isGameOverEnd();
		void deleteActors();

		inline void addNodeToScene(std::unique_ptr<SceneNode> node) {current_level->addNode(node.get());}
		CommandQueue& getCommandQueue(){ return command_queue; }
	
		//Script function
		static int setLevel(lua_State *L);
		static int setViewTarget(lua_State *L);

		//static std::unique_ptr<Level> current_level;
		

	private:
		sf::RenderWindow &window;
		CommandQueue command_queue;
		Collider collider;
		Player &player;
		LuaScripting script_system;

	private:
		
		static Camera camera;
		static Level* current_level;
		
		//Level* current_level;
	
	public:
		static bool is_new_level;

		
	private:
		//Pacman attributes
		bool isGameOver;
		const float speed = 185.f;

};

