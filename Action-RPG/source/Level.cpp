#include "..\header\Level.h"

#include "..\header\Map.h"
#include "..\header\Hero.h"
#include "..\header\Npc.h"
#include "..\header\Door.h"
#include "..\header\Enemy.h"
#include "..\header\Warp.h"
#include "..\header\TextBox.h"

#include <tolua++.h>



Level::Level()
: hero(nullptr)
, hero_panel(nullptr)
, map(nullptr)
, scene_graph(nullptr)
{
	scene_graph = new SceneNode();

	SceneNode::PtrNode layer1(new SceneNode());
	layers.push_back(layer1.get());
	scene_graph->addChild(std::move(layer1));

	SceneNode::PtrNode layer2(new SceneNode());
	layers.push_back(layer2.get());
	scene_graph->addChild(std::move(layer2));

	SceneNode::PtrNode layer3(new SceneNode());
	layers.push_back(layer3.get());
	scene_graph->addChild(std::move(layer3));

	SceneNode::PtrNode layer4(new SceneNode());
	layers.push_back(layer4.get());
	scene_graph->addChild(std::move(layer4));

	SceneNode::PtrNode layer5(new SceneNode());
	layers.push_back(layer5.get());
	scene_graph->addChild(std::move(layer5));

	texture_generator.load(SystemImage::TextContinueButton, "textures/text_continue_button.png");
	texture_generator.load(SystemImage::LifeFlower, "textures/life_flower.png");
	texture_generator.load(TiledTextures::Door01, "textures/door01.png");
	


	std::unique_ptr<HeroPanel> h_panel(new HeroPanel(texture_generator));
	hero_panel = h_panel.get();
	h_panel->initPosition();
	node_vector.push_back(hero_panel);
	layers[3]->addChild(std::move(h_panel));


	
	

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

void  Level::initCameraSettings()
{
	hero_panel->setLifes(10);
	hero_panel->setLifes(-2);
	hero_panel->initPosition();

}




void Level::addActorWithoutSprite(SceneNode *node, int layer)
{
	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[layer]->addChild(std::move(u));
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
	hero->changeAnimation(static_cast<int>(Animations::GoDown));
	hero->stopAnimation();
	node->setTexture(texture_generator.get(node->getTextureType()));

	//Set the center in order to apply transformations
	node->setOrigin(node->getFrameCenter());

	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[1]->addChild(std::move(u));



	
}




void Level::addActor(Npc *node)
{
	node->setTexture(texture_generator.get(node->getTextureType()));
	
	//Set the center in order to apply transformations
	node->setOrigin(node->getFrameCenter());

	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[1]->addChild(std::move(u));
}

void Level::addActor(Enemy *node)
{
	node->setTexture(texture_generator.get(node->getTextureType()));

	//Set the center in order to apply transformations
	node->setOrigin(node->getFrameCenter());

	std::unique_ptr<SceneNode> u(node);
	node_vector.push_back(u.get());
	layers[1]->addChild(std::move(u));
}





void Level::createTiledObjects()
{
	//Create Warps
	//Read tiled info: lua level script, warp destiny, etc.
	//The collider checks when there is a interaction with the warp and triggers the teleportation

	for (auto itr : map->tmx_warp)
	{
		std::unique_ptr<Warp> warp(new Warp(sf::RectangleShape(sf::Vector2f(itr.rect.width * map->getScale().x, itr.rect.height * map->getScale().y))));
		float x_corrected = itr.rect.left  * map->getScale().x;
		float y_corrected = itr.rect.top * map->getScale().y;
		float x_destiny_corrected = itr.destiny.x  * 2.f;
		float y_destiny_corrected = itr.destiny.y  * 2.f;
		std::string level_script_name = itr.level_script;
		int first_animation = itr.orientation;

		warp->setPosition(sf::Vector2f(x_corrected, y_corrected));
		warp->setDestiny(sf::Vector2f(x_destiny_corrected, y_destiny_corrected));
		warp->setLevelScriptName(level_script_name);
		warp->setFirstAnimation(first_animation);
		node_vector.push_back(warp.get());
		layers[0]->addChild(std::move(warp));
	}

	//Create Doors

	for (auto itr : map->tmx_door)
	{
		
		std::unique_ptr<Door> door(new Door(itr, 10, 11));
		door->setTexture(texture_generator.get(itr.texture_id));
		
		float tiled_width = itr.rect.width * map->getScale().x;
		float tiled_height = itr.rect.height * map->getScale().y;
		
		door->setPosition(sf::Vector2f(itr.rect.left * map->getScale().x + tiled_width / 2, itr.rect.top * map->getScale().y - tiled_height / 2.f));
		
		float tiled_x = itr.rect.left * map->getScale().x;
		float tiled_y = itr.rect.top * map->getScale().y;
		float width = door->getLocalRect().width;
		float height = door->getLocalRect().height;
		float col_rect_x = ((tiled_x - door->getCenter().x)) / map->getScale().x;
		float col_rect_y = ((tiled_y + tiled_height/2.f) - door->getCenter().y) / map->getScale().y;
		
		door->setCollisionRect(col_rect_x, col_rect_y, tiled_width / map->getScale().x, tiled_height / map->getScale().y);
		
		float scale_factor = tiled_width / width;
		door->setScale(scale_factor, scale_factor);

		door->addAnimationFrames(static_cast<int>(Animations::DoorOpen), "V", "Forward", itr.frame_number, 0, itr.frame_width, itr.frame_height);
		door->addAnimationFrames(static_cast<int>(Animations::DoorClose), "V", "Rewind", itr.frame_number, 0, itr.frame_width, itr.frame_height);
		door->loadState();
		
		node_vector.push_back(door.get());
		layers[1]->addChild(std::move(door));
		
	}
}

void Level::setMap(Map *c_map)
{
	map.reset(c_map);
	createTiledObjects();	
}

void Level::deleteNonGlobals()
{
	scene_graph->deleteNonGlobal();
}




