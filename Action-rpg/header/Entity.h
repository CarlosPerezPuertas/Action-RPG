#pragma once

#include "SceneNode.h"
#include "Animation.h"

//Drawable entities
class Entity : public SceneNode
{
	public:
		Entity(){}
		Entity(sf::Texture &texture);
		virtual ~Entity();

		sf::FloatRect getLocalRect();
		sf::FloatRect getGlobalRect();
		sf::Vector2f getCenter();
		sf::Vector2f getColisionCenter();
		void setOrigin(sf::Vector2f pos);
		inline void setTexture(sf::Texture &texture){ sprite.setTexture(texture); }
		
		inline sf::Vector2f getInitPos(){ return initial_pos; }
		inline void setInitPos(sf::Vector2f pos){ initial_pos = pos; }
		inline void restartPosition(){ setPosition(initial_pos);}
		
		void setCollisionRect(sf::FloatRect c_col_rect);
		inline sf::FloatRect getCollisionRect(){ return getWorldTransform().transformRect(collision_rect.getGlobalBounds()); }
		sf::FloatRect getCollisionRectExt();
		void setCollision(bool x) { is_colliding = x; }
		sf::FloatRect getLeftSensor();
		sf::FloatRect getRightSensor();
		sf::FloatRect getUpSensor();
		sf::FloatRect getDownSensor();



		
	protected:
		sf::Sprite  sprite;
		sf::Vector2f  initial_pos;
		sf::RectangleShape collision_rect;
		sf::RectangleShape up_sensor_rect;
		sf::RectangleShape down_sensor_rect;
		sf::RectangleShape left_sensor_rect;
		sf::RectangleShape right_sensor_rect;

		bool is_colliding;	
};

