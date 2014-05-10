#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <queue>

#include "Command.h"

template<typename EntityType>
class ActionQueue
{
	public:
		explicit ActionQueue(EntityType &entity);

		void push(Action &command);
		Action pop();
		bool isEmpty();

		void update(sf::Time dt);

	private:
		std::queue<Action> action_queue;
		EntityType &owner;
};

template<typename EntityType>
ActionQueue<typename EntityType>::ActionQueue(EntityType &entity) : owner(entity)
{

}


template<typename EntityType>
void ActionQueue<typename EntityType>::push(Action &command)
{
	action_queue.push(command);
}

template<typename EntityType>
Action ActionQueue<typename EntityType>::pop()
{
	Action command = action_queue.front();
	action_queue.pop();
	return command;
}

template<typename EntityType>
bool ActionQueue<typename EntityType>::isEmpty()
{
	return action_queue.empty();
}

//Actions must return states: running, finished, blocked, etc.
template<typename EntityType>
void ActionQueue<typename EntityType>::update(sf::Time dt)
{
	if (!isEmpty())
	{
		if (!action_queue.front().action(owner, dt))
		{
			action_queue.pop();
		}
			
	}
}



