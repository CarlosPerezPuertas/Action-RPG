#include "..\header\ActionTree.h"


ActionTree::ActionTree(unsigned int c_thread_number)
{
	//Create empty queues depending on the number of threads
	for (unsigned int i = 0; i < c_thread_number; ++i)
	{
		action_threads.push_back(std::queue<Action>());
	}

	thread_number = c_thread_number;
}


ActionTree::~ActionTree()
{
	clean();
}

void ActionTree::addChild(Action &action)
{
	assert(action.thread_id <= thread_number);

	if (action.thread_id == 0) single_actions.push_back(action);
	else if (action.thread_id > 0){ action_threads[action.thread_id - 1].push(action); }
}

void ActionTree::push(Action action)
{
	addChild(action);
}


void ActionTree::clean()
{
	while (!single_actions.empty()) single_actions.pop_front();

	for (auto &thread: action_threads)
	{
		while (!thread.empty())
		{
			thread.pop();
		}
	}

	while (!action_threads.empty())
	{
		action_threads.pop_back();
	}
}

//Actions must return states: running, finished, blocked, etc.
void ActionTree::update(sf::Time dt)
{
	if (!single_actions.empty())
	{
		for (auto &itr :single_actions)
		{
			if (itr.action(dt) == false)
			{
				itr.is_removevable = true;
			}
		}

		auto delete_begin = std::remove_if(single_actions.begin(), single_actions.end(), std::mem_fn(&Action::is_removevable));
		single_actions.erase(delete_begin, single_actions.end());	
	}

	std::set<unsigned int> queues_to_pop;
	int num_thread = 0;
	
	for (auto &thread : action_threads)
	{
		if (!thread.empty())
		if (thread.front().action(dt) == false)
		{
			thread.front().is_removevable = true;
			queues_to_pop.insert(num_thread);
		}

		num_thread++;
	}

	if (!queues_to_pop.empty())
	for (auto &itr : queues_to_pop)
	{
		action_threads[itr].pop();
	}
}

void ActionTree::deleteThread(unsigned int id)
{
	assert(action_threads.size() > id && id > 0);

	if (!action_threads[id - 1].empty())
	while (!action_threads[id-1].empty()) action_threads[id-1].pop();
}

unsigned int ActionTree::threadSize(unsigned int id)
{
	assert(action_threads.size() > id && id > 0);
	return action_threads[id-1].size();
}

