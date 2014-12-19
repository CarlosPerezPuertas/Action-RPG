#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <fstream>

#include "CommandQueue.h"
#include "SceneNode.h"
#include "Map.h"

class World;
class Player;
class LuaScripting;
struct TMX_Tile;
class TextSistem;




namespace CollisionEvent
{
	enum Id
	{
		PlayerNpc,
		PlayerWarp,
		SwordNpc 
	};
}


class Collider
{
	public:
		explicit Collider(World &c_world, CommandQueue &c_command_queue, TextSistem &c_text_sistem, Player &c_player, LuaScripting &c_script_system);
		virtual ~Collider();

		void checkSceneCollision(std::vector<SceneNode*> &nodes);
		template<typename T1, typename T2>
		void checkCollision(T1 &entity1, T2 &entity2);
		template<typename T1>
		void checkMapCollision(T1 &entity1);
		template<typename T1>
		int getMapPosition(T1 &entity);
		void registerCollisions();

		inline sf::Vector2f getMapPosition() { return map->getPosition(); }
		inline void setMap(Map *m){ map = m; }


	public:
		CommandQueue &command_queue;
		TextSistem &text_sistem;
		World &world;
		Player &player;
		LuaScripting &script_system;
		

	private:
		std::map<CollisionEvent::Id, std::pair<Category::Type, Category::Type>> events;
		std::map<std::pair<Category::Type, Category::Type>, CommandCollision> interactions;
		Map *map;
};

template<typename T1, typename T2>
void Collider::checkCollision(T1 &entity1, T2 &entity2)
{
	//if (&entity1 == nullptr || &entity2 == nullptr) std::cout << "nullptr" << std::endl;
	Category::Type category1 = static_cast<Category::Type>(entity1.getCategory());
	Category::Type category2 = static_cast<Category::Type>(entity2.getCategory());
	std::pair<Category::Type, Category::Type> pairs = std::make_pair(category1, category2);

	auto itr = interactions.find(pairs);
	if (itr != interactions.end()) itr->second.action(entity1, entity2);
	else
	{
		std::swap(pairs.first, pairs.second);
		itr = interactions.find(pairs);
		if (itr != interactions.end()) itr->second.action(entity2, entity1);
	}
	
	
}

template<typename T1>
void Collider::checkMapCollision(T1 &entity)
{
	bool col_left = false;
	bool col_right = false;
	bool col_up = false;
	bool col_down = false;

	for (auto &i : map->tmx_info.collision_map)
	{
		if (i.type == TileType::Collidable)
		{
			//Depending on the direction of the collision correct the position until the collision finishes
			if (entity.getCollisionRectExt().intersects(i.rect) == true)
			{
				entity.setCollision(true);
				Direction dir = entity.getCurrentDirection();
				bool bounce = false;

				while (entity.getCollisionRect().intersects(i.rect) == true && ((dir != Direction::None && entity.getCategory() == Category::Player) || entity.getCategory() == Category::Npc))
				{
					bounce = true;

					if (dir == Direction::Down) { entity.setCollisionDirection(Direction::Down);}
					else if (dir == Direction::Up) {  entity.setCollisionDirection(Direction::Up); }
					else if (dir == Direction::Left) {  entity.setCollisionDirection(Direction::Left); }
					else if (dir == Direction::Right) {  entity.setCollisionDirection(Direction::Right); }		
					
					//To avoid that NPC and enemies trembles when collides
					if (entity.getCategory() == Category::Npc)
					{
						float x = 0.f;
						float y = 0.f;

						if (entity.getLastMovement().x > 0) x = 0.1f;
						else if (entity.getLastMovement().x < 0) x = -0.1f;
						if (entity.getLastMovement().y > 0) y = 0.1f;
						else if (entity.getLastMovement().y < 0) y = -0.1f;

						entity.move(sf::Vector2f(-(entity.getLastMovement().x + x), -(entity.getLastMovement().y + y)));
					}
					else entity.move(sf::Vector2f(-(entity.getLastMovement().x), -(entity.getLastMovement().y)));
				}

				if (bounce) entity.stopAnimation(); 	
				if (entity.getDownSensor().intersects(i.rect)) col_down = true;
				if (entity.getUpSensor().intersects(i.rect)) col_up = true;
				if (entity.getLeftSensor().intersects(i.rect)) col_left = true;
				if (entity.getRightSensor().intersects(i.rect)) col_right = true;
			}		
		}
	}

	if (col_down) { entity.addCollisionDirection(Direction::Down);   } //std::cout << "Remove down direction" << std::endl; }
	else { entity.removeCollisionDirection(Direction::Down); }//std::cout << "Add down direction" << std::endl; }
	if (col_up) { entity.addCollisionDirection(Direction::Up); }//std::cout << "Remove up direction" << std::endl; }
	else { entity.removeCollisionDirection(Direction::Up); } //std::cout << "Add up direction" << std::endl; }
	if (col_left) { entity.addCollisionDirection(Direction::Left); } //std::cout << "Remove left direction" << std::endl; }
	else { entity.removeCollisionDirection(Direction::Left); } //std::cout << "Add left direction" << std::endl; }
	if (col_right) { entity.addCollisionDirection(Direction::Right); } //std::cout << "Remove right direction" << std::endl; }
	else { entity.removeCollisionDirection(Direction::Right); } //std::cout << "Add right direction" << std::endl; }

	//std::cout << entity.isCollisionDirection(Direction::Down) << std::endl;;
}

//Calcule the map position using the center of the entity as a reference
template<typename T1>
int Collider::getMapPosition(T1 &entity)
{
	int id = 0;
	int map_width = map->tmx_info.map_size.x;
	int map_height = map->tmx_info.map_size.y;
	float tile_width = map->tmx_info.collision_map[0].rect.width;
	float tile_height = map->tmx_info.collision_map[0].rect.height;

	sf::Vector2f rect;
	rect.x = entity.getGlobalRect().left;
	rect.y = entity.getGlobalRect().top;

	//The center of the entity
	rect.x += entity.getGlobalRect().width / 2.f;
	rect.y += entity.getGlobalRect().height / 2.f;
	
	//Perfect precision when it's scaled by integers +- 0.001 pixels
	id = static_cast<int>((rect.x - map->getPosition().x) / tile_width) +
		static_cast<int>(static_cast<int>((rect.y - map->getPosition().y) / tile_height) * map_width);

	return id;
}

