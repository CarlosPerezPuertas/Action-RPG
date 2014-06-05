#pragma once

#include "Entity.h"
#include "Map.h"



class MoveableObject : public Entity
{
	public:
		MoveableObject(){}
		MoveableObject(sf::Texture &texture);
		virtual ~MoveableObject();


		void move(const sf::Vector2f displacement);
		void moveByMap(Direction dir, sf::Time dt);
		void goLeft(sf::Time dt);
		void goRight(sf::Time dt);
		void goDown(sf::Time dt);
		void goUp(sf::Time dt);

		//Scripting functions
		bool goLeftUntil(int px, sf::Time dt);
		bool goRightUntil(int px, sf::Time dt);
		bool goUpUntil(int px, sf::Time dt);
		bool goDownUntil(int px, sf::Time dt);
		void applyForce(sf::Vector2f force, sf::Time dt);


		inline const float getSpeed() const { return speed; }
		inline const float getSpeedRatio() const { return speed * vel_ratio; }
		void setSpeed(float c_speed, float c_ratio);
		inline void setVelRatio(float c_vel_ratio){ vel_ratio = c_vel_ratio; }
		inline float getVelRatio(){ return vel_ratio; }
		

		inline void addDirection(Direction direction){ possible_directions.insert(direction); }
		inline void removeDirection(Direction direction){ possible_directions.erase(direction); }
		inline bool isPossibleDirection(Direction direction){ return (possible_directions.find(direction) != possible_directions.end()) && direction != Direction::None; }
		inline void setCurrentDirection(Direction direction){ current_direction = direction; parcial_displacement = 0; }
		inline void setPreviousDirection(Direction direction){ previous_direction = direction; }
		inline Direction getCurrentDirection(){ return current_direction; }
		inline std::set<Direction> getPossibleDirections(){ return possible_directions; }
		inline Direction getOrientation(){ return orientation; }
		inline void setOrientation(Direction dir){ orientation = dir; }
		inline Direction getCollisionDirection(){ return collision_direction; }
		inline void setCollisionDirection(Direction dir){ collision_direction = dir; }


		inline bool isDifferentTileMap(int num_tile)
		{ 
			//Init the tile map id
			if (tile_map_id == -1) tile_map_id = num_tile;
			return tile_map_id != num_tile;
		}

		inline void setIdTileMap(int num_tile) { tile_map_id = num_tile; }
		inline int getTileMap(){ return tile_map_id; }

		inline void setPreviousTileType(TileType previous){ previous_tile_type = previous; }
		inline TileType getPreviousTileType(){ return previous_tile_type; }
		inline sf::Vector2f getLastMovement(){ return last_movement; }

		

	protected:
		float speed;
		float vel_ratio;
		int  tile_map_id;

		sf::Vector2f last_movement;
		float parcial_displacement;

		std::set<Direction> possible_directions;
		Direction current_direction;
		Direction previous_direction;
		Direction orientation;
		Direction collision_direction;
		std::map<Direction, sf::Vector2f> movement_map;

		TileType previous_tile_type;
};

