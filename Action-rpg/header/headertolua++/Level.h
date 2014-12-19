#pragma once

#include "SceneNode.h"
#include "Entity.h"
#include "Resources.h"
#include "ResourceTypes.h"
#include "Pacman.h"
#include "Ghost.h"
#include "PickupObject.h"
#include "Warp.h"
#include "Text.h"
#include "Image.h"
#include "ImageContainer.h"
#include "SoundNode.h"
#include "Map.h"
#include "LuaScripting.h"




class Level
{
	public:
		Level();
		~Level();

		void loadResources();
		void createScene();
		void loadScripts(LuaScripting &script_system);
		void registerPickups();

		TMX::Map& getMap(){ return labyrinth; }
		SceneNode& getSceneGraph(){ return scene_graph; }
		std::vector<SceneNode*>& getSceneVector(){ return node_vector; }



		//Scripting functions
		inline void addNode(SceneNode *node)
		{
			std::unique_ptr<SceneNode> u(node);
			node_vector.push_back(u.get());
			layers[0]->addChild(std::move(u));
		}

		//Scripting functions
		template<typename EntityType>
		void addActor(EntityType *node);
	

	private:
		TextureGenerator texture_generator;
		SoundBufferFactory sounds;

		//Labyrinth map
		TMX::Map labyrinth;

		//Separate entities
		Pacman* pacman;
		Ghost* blinky;
		ImageContainer* lifes;
		ImageContainer* bonus;
		Text* game_over;

		//All entities stored in a tree and in a vector
		std::vector<SceneNode*> node_vector;
		std::vector<Ghost*> ghosts;
		std::vector<SceneNode*> layers;
		SceneNode scene_graph;

		//Pickup factory
		std::map<int, std::function<std::unique_ptr<PickupObject>()>> pickup_factory;
};

template<typename EntityType>
void Level::addActor(EntityType *node)
{
	node->setTexture(texture_generator.get(node->getTextureType()));
	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[0]->addChild(std::move(u));
}


