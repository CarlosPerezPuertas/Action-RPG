#include "..\header\Level.h"

#include "..\header\Map.h"
#include "..\header\Hero.h"
#include "..\header\Npc.h"
#include "..\header\Warp.h"
#include <tolua++.h>



Level::Level()
: hero(nullptr)
, map(nullptr)
, scene_graph()
{
	SceneNode::PtrNode layer1(new SceneNode());
	layers.push_back(layer1.get());
	scene_graph.addChild(std::move(layer1));

	SceneNode::PtrNode layer2(new SceneNode());
	layers.push_back(layer2.get());
	scene_graph.addChild(std::move(layer2));

	SceneNode::PtrNode layer3(new SceneNode());
	layers.push_back(layer3.get());
	scene_graph.addChild(std::move(layer3));

	std::cout << "Level created" << std::endl;	
}


Level::~Level()
{
	std::cout << "Level deleted" << std::endl;
	
	
}

void Level::addTexture(int type, std::string filename)
{
	texture_generator.load(type, filename);	
}


void Level::addNode(SceneNode *node)
{
	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[0]->addChild(std::move(u));
}




/*template<typename EntityType>
void Level::addActor(EntityType *node)
{
	node->setTexture(texture_generator.get(node->getTextureType()));
	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[0]->addChild(std::move(u));
}*/



void Level::addActor(Hero *node)
{
	hero = node;
	node->setTexture(texture_generator.get(node->getTextureType()));

	//Set the center in order to apply transformations
	sf::FloatRect local_rect = node->getLocalRect();
	sf::FloatRect frame_rect = sf::FloatRect(0.f, 0.f, local_rect.width/1.5f, local_rect.height/4.f);
	node->setOrigin(sf::Vector2f(local_rect.width / 5.f, local_rect.height/1.3f));
	node->setRealRect(frame_rect);

	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[1]->addChild(std::move(u));
}




void Level::addActor(Npc *node)
{
	node->setTexture(texture_generator.get(node->getTextureType()));
	
	//Set the center in order to apply transformations
	sf::FloatRect local_rect = node->getLocalRect();
	sf::FloatRect frame_rect = sf::FloatRect(0.f, 0.f, local_rect.width, local_rect.height/3.f);
	node->setOrigin(sf::Vector2f(0.f, local_rect.height / 1.5f));
	node->setRealRect(frame_rect);

	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[1]->addChild(std::move(u));
}



void Level::createTiledObjects()
{
	//Create Warps
	for (unsigned int i = 0; i < map->object_group.warp_rects.size(); ++i)
	{
	
		std::unique_ptr<Warp> warp(new Warp(sf::RectangleShape(sf::Vector2f(map->object_group.warp_rects[i].width * map->getScale().x, map->object_group.warp_rects[i].height * map->getScale().y))));
		float x_corrected = map->object_group.warp_rects[i].left * map->getScale().x ;
		float y_corrected = map->object_group.warp_rects[i].top * map->getScale().y ;
		float x_destiny_corrected = map->object_group.warp_destinies[i].x  * 2.f ;
		float y_destiny_corrected = map->object_group.warp_destinies[i].y  * 2.f;


		warp->setPosition(sf::Vector2f(x_corrected, y_corrected));
		warp->setDestiny(sf::Vector2f(x_destiny_corrected, y_destiny_corrected));
		//warp->scale(map->getScale());
		node_vector.push_back(warp.get());
		layers[0]->addChild(std::move(warp));
	}
}

void Level::setMap(Map *c_map)
{
	//if (map != nullptr) delete map;
	map.release();
	//std::unique_ptr<Map> new_map(c_map);
	map.reset(c_map);
	createTiledObjects();	
}

void Level::deleteNonGlobals()
{
	scene_graph.deleteNonGlobal();
}



