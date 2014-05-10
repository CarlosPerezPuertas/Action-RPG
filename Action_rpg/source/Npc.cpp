#include "..\header\Npc.h"



Npc::Npc(int c_texture_id)
: MoveableObject()
, action_queue(*this)
, animation(Entity::sprite, sf::seconds(0.1f), 0)
, is_talking(false)
, texture_id(c_texture_id)
{
	setSpeed(100, 0.75f);
}



Npc::~Npc()
{
	std::cout << "Npc deleted " << std::endl;
}


void Npc::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isActive())
	{
		target.draw(Entity::sprite, states);
		target.draw(Entity::collision_rect, states);
	}
		
}

void Npc::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (isActive())
	{
		updateAnimation(dt);
		action_queue.update(dt);

		if (getCurrentDirection() == Direction::Left) goLeft(dt);
		else if (getCurrentDirection() == Direction::Right) goRight(dt);
		else if (getCurrentDirection() == Direction::Up) goUp(dt);
		else if (getCurrentDirection() == Direction::Down) goDown(dt);
	}
}

bool Npc::selectRightDirection()
{
	bool is_selected = false;

	auto directions = getPossibleDirections();

	auto itr2 = directions.find(Direction::Right);
	if (itr2 != directions.end())
	{
		setCurrentDirection(Direction::Right);
		is_selected = true;
	}

	return is_selected;
}

bool Npc::selectLeftDirection()
{
	bool is_selected = false;

	auto directions = getPossibleDirections();

	auto itr2 = directions.find(Direction::Left);
	if (itr2 != directions.end())
	{
		setCurrentDirection(Direction::Left);
		is_selected = true;
	}

	return is_selected;
}

bool Npc::selectUpDirection()
{
	bool is_selected = false;

	auto directions = getPossibleDirections();

	auto itr2 = directions.find(Direction::Up);
	if (itr2 != directions.end())
	{
		setCurrentDirection(Direction::Up);
		is_selected = true;
	}

	return is_selected;
}

bool Npc::selectDownDirection()
{
	bool is_selected = false;

	auto directions = getPossibleDirections();

	auto itr2 = directions.find(Direction::Down);
	if (itr2 != directions.end())
	{
		setCurrentDirection(Direction::Down);
		is_selected = true;
	}

	return is_selected;
}


//The ghosts cannot go to the opposite site
void Npc::discardOppositeDirection()
{
	if (getCurrentDirection() == Direction::Up) removeDirection(Direction::Down);
	else if (getCurrentDirection() == Direction::Down) removeDirection(Direction::Up);
	else if (getCurrentDirection() == Direction::Left) removeDirection(Direction::Right);
	else if (getCurrentDirection() == Direction::Right) removeDirection(Direction::Left);
}


unsigned int Npc::getCategory() const
{
	return Category::Npc;
}


void Npc::restart()
{


}

void Npc::moveRight(int px)
{
	Action GoRight;
	Action AnimReset;

	GoRight.action = get_action<Npc>([this, px](Npc &npc, sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoRight))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoRight));
			getAnimation().play();
		}
		return goRightUntil(px);
	});

	AnimReset.action = get_action<Npc>([this](Npc &npc, sf::Time dt)
	{
		animation.reset();
		return false;
	});

	action_queue.push(GoRight);
	action_queue.push(AnimReset);
}

void Npc::moveLeft(int px)
{
	Action GoLeft;
	Action AnimReset;

	GoLeft.action = get_action<Npc>([this, px](Npc &npc, sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoLeft))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoLeft));
			getAnimation().play();
		}
		return goLeftUntil(px);
	});

	AnimReset.action = get_action<Npc>([this](Npc &npc, sf::Time dt)
	{
		animation.reset();
		return false;
	});

	action_queue.push(GoLeft);
	action_queue.push(AnimReset);
}

void Npc::moveDown(int px)
{
	Action GoDown;
	Action AnimReset;

	GoDown.action = get_action<Npc>([this, px](Npc &npc, sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoDown))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoDown));
			getAnimation().play();
		}
		return goDownUntil(px);
	});

	AnimReset.action = get_action<Npc>([this](Npc &npc, sf::Time dt)
	{
		animation.reset();
		return false;
	});


	action_queue.push(GoDown);
	action_queue.push(AnimReset);
}

void Npc::moveUp(int px)
{
	Action GoUp;
	Action AnimReset;

	GoUp.action = get_action<Npc>([this, px](Npc &npc, sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoUp))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoUp));
			getAnimation().play();
		}
		return goUpUntil(px);
	});

	AnimReset.action = get_action<Npc>([this](Npc &npc, sf::Time dt)
	{
		animation.reset();
		return false;
	});

	action_queue.push(GoUp);
	action_queue.push(AnimReset);
}

void Npc::setPosition(sf::Vector2f pos)
{
	sf::Transformable::setPosition(pos);
}

void Npc::setPosition(float x, float y)
{
	sf::Transformable::setPosition(sf::Vector2f(x, y));
}

void Npc::scale(sf::Vector2f factor)
{
	sf::Transformable::scale(factor);
}

void Npc::scale(float x, float y)
{
	sf::Transformable::scale(sf::Vector2f(x, y));
}

bool Npc::isTalking()
{
	return is_talking;
}

void Npc::addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height)
{
	if (distribution == "H")
	{
		for (int i = 0; i < num_frames; i++)
		{
			animation.addFrame(anim_type, sf::IntRect(i*width, (position - 1) * height, width, height));
		}
	}
	else if (distribution == "V")
	{
		for (int i = 0; i < num_frames; i++)
		{
			animation.addFrame(anim_type, sf::IntRect((position - 1) * width, i * height, width, height));
		}

	}

	if (loop_type == "OneLoop") animation.setUniqueLoop(anim_type);

	setSpeed(200, 0.75f);
	setVelRatio(1.f);
}

void Npc::setText(std::string c_text)
{
	text = c_text;
}

void Npc::displayText()
{
	std::cout << text << std::endl;
}



