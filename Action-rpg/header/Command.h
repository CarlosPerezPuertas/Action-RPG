#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <cassert>


class SceneNode;

struct Command
{
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};


struct Action
{
	std::function<bool(sf::Time)> action;
	bool is_removevable;
	bool is_blocking;
	unsigned int thread_id;
};

struct CommandCollision
{
	std::function<void(SceneNode&, SceneNode&)> action;
	unsigned int category;
};


template<typename object, typename callback>
std::function<void(SceneNode&, sf::Time)> get_function(callback c)
{
	return[=](SceneNode& node, sf::Time df)
	{
		c(static_cast<object&>(node), df);	
	};
}

template<typename callback>
std::function<bool( sf::Time)> get_action(callback c)
{
	return[=](sf::Time dt) mutable
	{
		return c(dt);
	};
}


template<typename object1, typename object2, typename callback>
std::function<void(SceneNode&, SceneNode&)> get_function_collision(callback c)
//std::function<void(std::pair<SceneNode&, SceneNode&>&, sf::Time)> get_function_collision(callback c)
{
	return[=](SceneNode& node1, SceneNode& node2)
	{
		//std::pair<object1&, object2&> pair = std::make_pair(static_cast<object1&>(node1), static_cast<object2&>(node2));
	
		c(static_cast<object1&>(node1), static_cast<object2&>(node2));
	};
}

