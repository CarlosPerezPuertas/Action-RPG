#include "..\header\Npc.h"

#include "..\header\ScreenEffect.h"

Npc::Npc(int c_texture_id)
: MoveableObject()
, action_tree(3)
, animation(Entity::sprite, sf::seconds(0.1f), 0)
, is_talking(false)
, texture_id(c_texture_id)
, is_invincible(false)
, is_attacking(false)
, time_invincible(sf::seconds(0.f))
, fade(0.8, 0.1)
, life(2)
, die_explosion_effect(nullptr)
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
		//if (die_explosion_effect != nullptr)
		//if (die_explosion_effect->isActive()) target.draw(*die_explosion_effect, states);
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

		if (is_invincible)
		{
			time_invincible -= dt;

			if (time_invincible == sf::Time::Zero)
			{
				is_invincible = false;
			}
		}
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

void Npc::recieveDamage(int damage, float seconds)
{
	life -= damage;

	is_invincible = true;
	time_invincible = sf::seconds(seconds);
	fade.restart(1.0f, 0.1f);
	std::unique_ptr<Effect> effect(new Effect(sprite));
	fade.setNumLoops(25);
	effect->setLifeTime(0.1f);
	effect->spriteOn();
	effect->addAffector(fade);
	this->addChild(std::move(effect));
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

void Npc::die()
{
	Action die;
	die.thread_id = 0;

	die.action = get_action([this](sf::Time dt)
	{
		if (getAnimationState() != static_cast<int>(Animations::Die))
		{
			changeAnimation(static_cast<int>(Animations::Die));
			animation.play();
		}

		return animation.isEndLoop();
	});

	action_tree.push(die);

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
			animation.addFrame(anim_type, sf::IntRect(i*width, position, width, height));
		}
	}
	else if (distribution == "V")
	{
		for (int i = 0; i < num_frames; i++)
		{
			animation.addFrame(anim_type, sf::IntRect(position, i * height, width, height));
		}
	}

	if (loop_type == "OneLoop") animation.setUniqueLoop(anim_type);

	setSpeed(200, 0.75f);
	setVelRatio(1.f);
}

void Npc::setCollisionRect(float x, float y, float w, float h)
{ 
	Entity::setCollisionRect(sf::FloatRect(x, y, w, h)); 
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

void Npc::chase(sf::Vector2f pos)
{
	Action chase;
	chase.thread_id = 1;
	chase.action = get_action([this, pos](sf::Time dt)
	{
		sf::Vector2f normal = normalize(pos.x - getPosition().x, pos.y - getPosition().y);
		//std::cout << normal.x << "" << normal.y << std::endl;
		move(sf::Vector2f(normal.x * 100.f * dt.asSeconds(), normal.y * 100.f * dt.asSeconds()));
		return false;
	});

	pushAction(chase);

}



