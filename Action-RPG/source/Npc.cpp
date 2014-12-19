#include "..\header\Npc.h"

#include "..\header\ScreenEffect.h"

Npc::Npc(int c_texture_id)
: MoveableObject()
, is_talking(false)
, fade(0.8, 0.1)
, stop_time(sf::Time::Zero)
{
	Entity::texture_id = c_texture_id;
	setSpeed(100, 0.75f);
	setVelRatio(1.f);
	key = "Npc";

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
		action_tree.update(dt);
		
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
	GoRight.is_blocking = true;
	GoRight.thread_id = 1;
	Action AnimReset;
	AnimReset.is_blocking = true;
	AnimReset.thread_id = 1;

	GoRight.action = get_action([this, px]( sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoRight))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoRight));
			getAnimation().play();
		}
		return goRightUntil(px, dt);
	});

	AnimReset.action = get_action([this](sf::Time dt)
	{
		animation.reset();
		return false;
	});

	action_tree.push(GoRight);
	action_tree.push(AnimReset);
}

void Npc::moveLeft(int px)
{
	Action GoLeft;
	GoLeft.is_blocking = true;
	GoLeft.thread_id = 1;
	Action AnimReset;
	AnimReset.is_blocking = true;
	AnimReset.thread_id = 1;

	GoLeft.action = get_action([this, px](sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoLeft))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoLeft));
			getAnimation().play();
		}
		return goLeftUntil(px, dt);
	});

	AnimReset.action = get_action([this](sf::Time dt)
	{
		animation.reset();
		return false;
	});

	action_tree.push(GoLeft);
	action_tree.push(AnimReset);
}

void Npc::moveDown(int px)
{
	Action GoDown;
	GoDown.is_blocking = true;
	GoDown.thread_id = 1;
	Action AnimReset;
	AnimReset.is_blocking = true;
	AnimReset.thread_id = 1;

	GoDown.action = get_action([this, px](sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoDown))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoDown));
			getAnimation().play();
		}
		return goDownUntil(px, dt);
	});

	AnimReset.action = get_action([this](sf::Time dt)
	{
		animation.reset();
		return false;
	});


	action_tree.push(GoDown);
	action_tree.push(AnimReset);
}

void Npc::moveUp(int px)
{
	Action GoUp;
	GoUp.is_blocking = true;
	GoUp.thread_id = 1;
	Action AnimReset;
	AnimReset.is_blocking = true;
	AnimReset.thread_id = 1;

	GoUp.action = get_action([this, px](sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::GoUp))
		{
			animation.play();
			changeAnimation(static_cast<int>(Animations::GoUp));
			getAnimation().play();
		}
		return goUpUntil(px, dt);
	});

	AnimReset.action = get_action([this](sf::Time dt)
	{
		animation.reset();
		return false;
	});

	action_tree.push(GoUp);
	action_tree.push(AnimReset);
}



bool Npc::isTalking()
{
	return is_talking;
}



void Npc::setText(std::string c_text)
{
	text = c_text;
}

std::string Npc::getText()
{
	return text;
}

void Npc::displayText()
{
	std::cout << text << std::endl;
}

void Npc::follow(sf::Vector2f pos)
{
	/*action_tree.deleteThread(3);

	Action chase;
	chase.thread_id = 2;
	chase.action = get_action([this, pos](sf::Time dt)
	{
		
		sf::Vector2f normal = normalize(pos.x - getPosition().x, pos.y - getPosition().y);
		float x = normal.x ;
		float y = normal.y ;

		if ((isCollisionDirection(Direction::Left) && x < 0.f) || (isCollisionDirection(Direction::Right) && x > 0.f)) { x = 0.f; if (y > 0.f) y = 1.f; else if (y < 0.f)  y = -1.f; }
		if ((isCollisionDirection(Direction::Up) && y < 0.f) || (isCollisionDirection(Direction::Down) && y > 0.f))   { y = 0.f;  if (x > 0.f)x = 1.f;  else if (x < 0.f) x = -1.f; }

		x = x * 100.f * dt.asSeconds();
		y = y * 100.f * dt.asSeconds();

		playAnimation();
		if (x > 0 && abs(x) > abs(y)) { if (getCurrentDirection() != Direction::Right) { setCurrentDirection(Direction::Right); changeAnimation(static_cast<int>(Animations::GoRight)); } }
		if (x < 0 && abs(x) > abs(y)) { if (getCurrentDirection() != Direction::Left) { setCurrentDirection(Direction::Left); changeAnimation(static_cast<int>(Animations::GoLeft)); } }
		if (y > 0 && abs(x) < abs(y)) { if (getCurrentDirection() != Direction::Down) { setCurrentDirection(Direction::Down); changeAnimation(static_cast<int>(Animations::GoDown)); } }
		if (y < 0 && abs(x) < abs(y)) { if (getCurrentDirection() != Direction::Up) { setCurrentDirection(Direction::Up); changeAnimation(static_cast<int>(Animations::GoUp)); } }
		
		//std::cout <<x << " " << y << std::endl;
		//std::cout << this->isCollisionDirection(Direction::Left) << " " << this->isCollisionDirection(Direction::Right) << " " << isCollisionDirection(Direction::Down) << " " << isCollisionDirection(Direction::Up) << std::endl;
		
		move(sf::Vector2f(x, y));
		return false;
	});

	pushAction(chase);*/
}

void Npc::walk()
{
	/*std::discrete_distribution<int> dir_distribution({60, 10, 10, 10, 10});
	std::uniform_int_distribution<int> distance_distribution(50, 100);
	std::uniform_real_distribution<float> wait_time_distribution(1.f, 3.f);
	Direction dir = static_cast<Direction>(dir_distribution(mt));
	int distance = distance_distribution(mt);
	if (stop_time == sf::Time::Zero) stop_time = sf::seconds(wait_time_distribution(mt));

	
	Action patrol;
	patrol.thread_id = 2;
	patrol.action = get_action([this, dir, distance](sf::Time dt)
	{
		if (getCurrentDirection() == Direction::Left) { goLeft(dt); }
		else if (getCurrentDirection() == Direction::Right) {goRight(dt); }
		else if (getCurrentDirection() == Direction::Up) { goUp(dt); }
		else if (getCurrentDirection() == Direction::Down) { goDown(dt); }

		if (dir == Direction::Left) { moveLeft(distance); }
		else if (dir == Direction::Right) { moveRight(distance);  }
		else if (dir == Direction::Up) { moveUp(distance); }
		else if (dir == Direction::Down) { moveDown(distance); }
		/*else if (dir == Direction::None) 
		{
			stopAnimation();
			std::cout << "Stop " << stop_time.asSeconds() <<  std::endl;
			stop_time -= dt;
			if (stop_time > sf::Time::Zero) return true;
			stop_time = sf::Time::Zero;
			return false;
		}*/
		/*stop_time = sf::Time::Zero;
		return false;
	});

	//When we have 2 actions we stop action addition
	unsigned int max_actions = 2;
	if (action_tree.threadSize(patrol.thread_id) < max_actions)
	{
		pushAction(patrol);
	}*/
}






