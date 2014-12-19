#include "..\header\Enemy.h"




#include "..\header\ScreenEffect.h"

Enemy::Enemy(int c_texture_id)
: MoveableObject()
, is_talking(false)
, is_invincible(false)
, is_attacking(false)
, time_invincible(sf::seconds(0.f))
, fade(0.8, 0.1)
, life(2)
, stop_time(sf::Time::Zero)
, die_explosion_effect(nullptr)
, current_weapon(nullptr)
{
	Entity::texture_id = c_texture_id;
	setSpeed(50, 0.75f);
	addWeapon(WeaponType::ObjectInHand, sf::Vector2f(12.5f, 25.f), 0.f, 0.5f, 1);
	key = "Enemy";

}



Enemy::~Enemy()
{
	std::cout << "Npc deleted " << std::endl;
}


void Enemy::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isActive())
	{
		target.draw(Entity::sprite, states);
		target.draw(Entity::collision_rect, states);
	}
}

void Enemy::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (isActive())
	{
		updateAnimation(dt);
		action_tree.update(dt);

		

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

bool Enemy::selectRightDirection()
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

bool Enemy::selectLeftDirection()
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

bool Enemy::selectUpDirection()
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

bool Enemy::selectDownDirection()
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
void Enemy::discardOppositeDirection()
{
	if (getCurrentDirection() == Direction::Up) removeDirection(Direction::Down);
	else if (getCurrentDirection() == Direction::Down) removeDirection(Direction::Up);
	else if (getCurrentDirection() == Direction::Left) removeDirection(Direction::Right);
	else if (getCurrentDirection() == Direction::Right) removeDirection(Direction::Left);
}


unsigned int Enemy::getCategory() const
{
	return Category::Enemy;
}

void Enemy::recieveDamage(int damage, float seconds)
{
	life -= damage;

	is_invincible = true;
	time_invincible = sf::seconds(seconds);
	fade.restart(1.0f, 0.1f);
	std::unique_ptr<Effect> effect(new Effect(sprite));
	fade.setNumLoops(35);
	effect->setLifeTime(0.05f);
	effect->spriteOn();
	effect->addAffector(fade);
	this->addChild(std::move(effect));
}


void Enemy::restart()
{


}

void Enemy::moveRight(int px)
{
	Action GoRight;
	GoRight.is_blocking = true;
	GoRight.thread_id = 1;
	Action AnimReset;
	AnimReset.is_blocking = true;
	AnimReset.thread_id = 1;

	GoRight.action = get_action([this, px](sf::Time dt)
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

void Enemy::moveLeft(int px)
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

void Enemy::moveDown(int px)
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

void Enemy::moveUp(int px)
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

void Enemy::wait(sf::Time w_time)
{
	Action Wait;
	Wait.is_blocking = true;
	Wait.thread_id = 1;
	
	stop_time = w_time;

	Wait.action = get_action([this](sf::Time dt)
	{
		stop_time -= dt;

		if (stop_time >= sf::Time::Zero)
		{
			return true;
			
		}

		return false;
	});

	action_tree.push(Wait);

}

void Enemy::die()
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





bool Enemy::isTalking()
{
	return is_talking;
}

void Enemy::setText(std::string c_text)
{
	text = c_text;
}

std::string Enemy::getText()
{
	return text;
}

void Enemy::displayText()
{
	std::cout << text << std::endl;
}

void Enemy::chase(sf::Vector2f pos)
{
	action_tree.deleteThread(1);

	Action chase;
	chase.thread_id = 1;
	chase.action = get_action([this, pos](sf::Time dt)
	{

		sf::Vector2f normal = normalize(pos.x - getPosition().x, pos.y - getPosition().y);
		float x = normal.x;
		float y = normal.y;

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

	pushAction(chase);
}

void Enemy::patrol()
{

	std::discrete_distribution<int> dir_distribution({ 60, 10, 10, 10, 10 });
	std::uniform_int_distribution<int> distance_distribution(50, 100);
	std::uniform_real_distribution<float> wait_time_distribution(1.f, 3.f);
	Direction dir = static_cast<Direction>(dir_distribution(mt));
	int distance = distance_distribution(mt);
	stop_time = sf::seconds(wait_time_distribution(mt));
	

	//Action selection
	Action patrol;
	patrol.thread_id = 1;
	patrol.action = get_action([this, dir, distance](sf::Time dt)
	{
		if (dir == Direction::Left) { moveLeft(distance); }
		else if (dir == Direction::Right) { moveRight(distance); }
		else if (dir == Direction::Up) { moveUp(distance); }
		else if (dir == Direction::Down) { moveDown(distance); }
		//else if (dir == Direction::None) { std::cout << "Stop time" << stop_time.asSeconds() << std::endl; wait(stop_time); }
		

		return false;
	});
	//When we have 2 actions we stop action addition
	unsigned int max_actions = 2;
	if (action_tree.threadSize(patrol.thread_id) < max_actions)
	{
		pushAction(patrol);
	}


	//Action updating, each frame
	Action patrol_update;
	patrol_update.thread_id = 0;
	patrol_update.action = get_action([this](sf::Time dt)
	{
		if (getCurrentDirection() == Direction::Left) { goLeft(dt); }
		else if (getCurrentDirection() == Direction::Right) { goRight(dt); }
		else if (getCurrentDirection() == Direction::Up) { goUp(dt); }
		else if (getCurrentDirection() == Direction::Down) { goDown(dt); }

		return false;
	});
	pushAction(patrol_update);

	
}

void Enemy::attack(float attack_delay, float attack_time, int damage)
{
	current_weapon->hit(Direction::Left);
}

void Enemy::addWeapon(WeaponType weapon_type, sf::Vector2f rect_size, float attack_delay, float attack_time, int damage)
{
	std::unique_ptr<Weapon> weapon(new Weapon(weapon_type));
	current_weapon = weapon.get();
	current_weapon->setRect(rect_size);
	current_weapon->setAttackDelay(attack_delay);
	current_weapon->setAttackTime(attack_time);
	current_weapon->setDamage(damage);
	this->addChild(std::move(weapon));
}



