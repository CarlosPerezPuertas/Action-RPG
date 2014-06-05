#pragma once

#include "SceneNode.h"
#include "Resources.h"
//#include "ResourceTypes.h"
#include "SoundNode.h"
#include "LuaScripting.h"
#include "HeroPanel.h"

class Map;
class Npc;
class Hero;
class TextBox;



class Level
{
	public:
		Level();
		~Level();

		//Scene elements getters
		std::unique_ptr<Map>& getMap(){ return map; }
		SceneNode& getSceneGraph(){ return scene_graph; }
		std::vector<SceneNode*>& getSceneVector(){ return node_vector; }
		SceneNode* getLayer(unsigned int num_layer){ assert(layers.size() > num_layer); return layers[num_layer]; }
		Hero& getMainPlayer(){ return *hero; }
		
		void createTiledObjects();
		void deleteNonGlobal();
		int getEntitiesNumber(){ return node_vector.size(); }

		
		void addActorWithoutSprite(SceneNode *node, int layer);
		TextureGenerator& getTG(){ return texture_generator; }
		void initCameraSettings();
		inline Hero* getHero(){ return hero; }
		
	
	public:	
		//Scripting functions
		void addActor(Npc *node); 
		void addActor(Hero *node);
		void setMap(Map *c_map);
		void addTexture(int type, std::string filename);
		void deleteNonGlobals();

	private:
		TextureGenerator texture_generator;
		SoundBufferFactory sounds;

		std::unique_ptr<Map> map;
		Hero* hero;
		HeroPanel* hero_panel;
		

		//All entities stored in a tree and in a vector
		std::vector<SceneNode*> node_vector;
		std::vector<SceneNode*> layers;
		SceneNode scene_graph;
};



