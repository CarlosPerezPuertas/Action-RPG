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

		inline void setTexture(sf::Texture &texture){ sprite.setTexture(texture); }
		void setRealRect(sf::FloatRect c_real_rect);
		inline sf::FloatRect getRealRect(){ return real_rect; }

		inline sf::Vector2f getInitPos(){ return initial_pos; }
		inline void setInitPos(sf::Vector2f pos){ initial_pos = pos; }
		inline void restartPosition(){ setPosition(initial_pos);}
		void scaleEntity(sf::Vector2f factor);

		sf::FloatRect getLocalRect();
		sf::FloatRect getGlobalRect();
		sf::FloatRect getInteriorRect();
		sf::FloatRect getInteriorRectMinus();
		sf::Vector2f getCenter();
		void setOrigin(sf::Vector2f pos);
		void setCollision(bool x) { is_colliding = x; }
		
	protected:
		sf::Sprite  sprite;
		sf::FloatRect real_rect;
		sf::FloatRect real_rect_minus;
		sf::Vector2f  initial_pos;
		sf::RectangleShape collision_rect;
		
		bool is_colliding;
		
};

