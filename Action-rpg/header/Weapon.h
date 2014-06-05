#pragma once

#include "SceneNode.h"

class Weapon : public SceneNode
{
	public:
		Weapon();
		~Weapon();

		void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		virtual unsigned int getCategory() const { return Category::Sword; }

		void hit(Direction direction);
		sf::FloatRect getGlobalRect();


	private:
		sf::RectangleShape rect_shape;
		sf::Time attack_time;

};

