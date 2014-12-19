#include "..\header\Door.h"


std::set<std::pair<std::string, bool>> Door::states;

Door::Door(const TMX_Door &tiled_data,const  unsigned int c_open_animation_id,const unsigned int c_close_animation_id)
: StaticObject()
, open_animation_id(c_open_animation_id)
, close_animation_id(c_close_animation_id)
{
	
	Door::states.insert(std::pair<std::string, bool>(tiled_data.name, tiled_data.state));
	key = tiled_data.name;
	texture_id = tiled_data.texture_id;
	std::cout << key << " created " << std::endl;
}


Door::~Door()
{
	std::cout << key << " deleted " << std::endl;
}

void Door::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isActive())
	{
		target.draw(Entity::sprite, states);
		target.draw(Entity::collision_rect, states);
	}
}

void Door::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (isActive())
	{
		updateAnimation(dt);
		action_tree.update(dt);
	}
}

unsigned int Door::getCategory() const
{
	return Category::Door;
}

void Door::open()
{
	//Refresh the state of the door to load it when we change levels.
	states.erase(std::pair<std::string, bool>(key, false));
	states.insert(std::pair<std::string, bool>(key, true));
	
	is_colliding = false;
	changeAnimation(open_animation_id);
	playAnimation();
}

void Door::close()
{
	//Refresh the state of the door to load it when we change levels.
	states.erase(std::pair<std::string, bool>(key, true));
	states.insert(std::pair<std::string, bool>(key, false));
	
	is_colliding = true;
	changeAnimation(close_animation_id);
	playAnimation();
}

bool Door::isClosed()
{
	return is_colliding;
}

bool Door::isState()
{
	for (auto &itr : states)
	{
		if (itr.first == key) return true;	
	}

	return false;
}

void Door::loadState()
{
	for (auto &itr : states)
	{
		if (itr.first == key)
		{
			if (itr.second == true) initOpened();
			else initClosed();
		}
	}
}


