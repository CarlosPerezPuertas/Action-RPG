#pragma once

#include <SFML/Graphics.hpp>


class Hero;
class CommandQueue;
class SceneNode;
class Level;
class Map;


class Camera : public sf::View
{
	public:
		Camera();
		~Camera();

		void update(CommandQueue &command_queue, sf::Time dt, Level &level, sf::RenderWindow &window);
		void setTarget(const SceneNode &target, Map &map);
		

};

