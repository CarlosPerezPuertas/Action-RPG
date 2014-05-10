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


namespace CollisionEvent
{
	enum Id
	{
		PlayerNpc,
		PlayerWarp
	};
}


class Collider
{
	public:
		explicit Collider(World &c_world, CommandQueue &c_command_queue, Player &c_player, LuaScripting &c_script_system);
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
	sf::FloatRect rect1 = sf::FloatRect(entity.getPosition().x - 0.5f, entity.getPosition().y - 0.5f, entity.getRealRect().width + 1.f, entity.getRealRect().height + 1.f);
	std::vector<sf::FloatRect> map_rects;


	for (auto &i : map->tmx_info.collision_map)
	{
		//map_rects.push_back(i.rect);

		if (i.type == TileType::Collidable)
		{
			if (entity.getInteriorRectMinus().intersects(i.rect) == true)
			{
				entity.setCollision(true);
				//Depending on the direction of the collision correct the position until the collision finishes
				Direction dir = entity.getCurrentDirection();
				bool bounce = false;

				while (entity.getInteriorRect().intersects(i.rect) == true && dir != Direction::None)
				{
					bounce = true;

					if (dir == Direction::Down) { entity.move(sf::Vector2f(0.f, -1.f)); entity.setCollisionDirection(Direction::Down); }
					else if (dir == Direction::Up) { entity.move(sf::Vector2f(0.f, 1.f)); entity.setCollisionDirection(Direction::Up); }
					else if (dir == Direction::Left) { entity.move(sf::Vector2f(1.f, 0.f)); entity.setCollisionDirection(Direction::Left); }
					else if (dir == Direction::Right) { entity.move(sf::Vector2f(-1.f, 0.f)); entity.setCollisionDirection(Direction::Right); }
					
				}

				if (bounce) { entity.stopAnimation(); }

				//entity.setCurrentDirection(Direction::None);
				//std::cout << "Map collision " << std::endl;
			}
		}
 
	}

	


	

	
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

