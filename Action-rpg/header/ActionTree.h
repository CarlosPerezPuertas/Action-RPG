#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include <queue>
#include <list>
#include <set>

#include "Command.h"

class ActionTree
{
	public:
		explicit ActionTree(unsigned int c_thread_number);
		~ActionTree();

		void push(Action action);
		void update(sf::Time dt);
		void deleteThread(unsigned int id);
		unsigned int threadSize(unsigned int id);

	private:
		void addChild(Action &action);
		void clean();

	private:
		std::vector<std::queue<Action>> action_threads; //Threads
		std::list<Action> single_actions;
		unsigned int thread_number;
};

