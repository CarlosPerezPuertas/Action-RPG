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
		void setOrigin(sf::Vector2f pos);
		inline void setTexture(sf::Texture &texture){ sprite.setTexture(texture); }
		
		inline sf::Vector2f getInitPos(){ return initial_pos; }
		inline void setInitPos(sf::Vector2f pos){ initial_pos = pos; }
		inline void restartPosition(){ setPosition(initial_pos);}
		
		void setCollisionRect(sf::FloatRect c_col_rect);
		inline sf::FloatRect getCollisionRect(){ return getWorldTransform().transformRect(collision_rect.getGlobalBounds()); }
		sf::FloatRect getCollisionRectExt();
		void setCollision(bool x) { is_colliding = x; }

		
	protected:
		sf::Sprite  sprite;
		sf::Vector2f  initial_pos;
		sf::RectangleShape collision_rect;
		bool is_colliding;	
};

