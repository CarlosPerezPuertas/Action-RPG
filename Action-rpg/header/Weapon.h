#pragma once

#include "SceneNode.h"


enum WeaponType
{
	ObjectInHand,
	StaticMagic,
	Boomerang,
	Bow
};


class Weapon : public SceneNode
{
	public:
		Weapon(WeaponType c_type);
		~Weapon();

		void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		virtual unsigned int getCategory() const { return Category::Sword; }

		void hit(Direction direction);
		sf::FloatRect getGlobalRect();

		inline void setRect(sf::Vector2f c_rect_size)
		{
			rect_size = c_rect_size;
			rect_shape.setOutlineColor(sf::Color::Blue);
			rect_shape.setOutlineThickness(0.2f);
			rect_shape.setFillColor(sf::Color::Transparent);
			rect_shape.setOrigin(6.f, 12.5f);
		}
		inline void setCenter(sf::Vector2f pos){ entity_center = pos; }
		inline void setDamage(int num){ damage = num; }
		inline int  getDamage(){ return damage; }
		inline void setAttackTime(float time){ attack_time = sf::seconds(time); }
		inline sf::Time getAttackTime(){ return attack_time; }
		inline void setAttackDelay(float time){ attack_delay = sf::seconds(time); }
		inline sf::Time getAttackDelay(){ return attack_delay; }

	private:
		WeaponType type;
		sf::RectangleShape rect_shape;
		sf::Vector2f rect_size;
		sf::Vector2f entity_center;
		sf::Time attack_time;
		sf::Time attack_time_elapsed;
		sf::Time attack_delay;
		int damage;

};

