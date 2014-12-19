#include "..\header\Hero.h"
#include "..\header\ScreenEffect.h"






Hero::Hero(int c_texture_id)
: MoveableObject()
, is_invincible(false)
, is_attacking(false)
, time_invincible(sf::Time::Zero)
, fade(0.8, 0.1)
, current_weapon(nullptr)
{
	Entity::texture_id = c_texture_id;
	setSpeed(200, 0.75f);
	setVelRatio(1.f);

	//moveRight(100);

	key = "heroe";

	//Allowed directions
	possible_directions.insert(Direction::Right);
	possible_directions.insert(Direction::Left);
	possible_directions.insert(Direction::Up);
	possible_directions.insert(Direction::Down);

	addWeapon(WeaponType::ObjectInHand, sf::Vector2f(12.5f, 25.f), 0.f, 0.5f, 1);
}


void Hero::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isActive())
	{
		target.draw(Entity::sprite, states);
		target.draw(Entity::collision_rect, states);
		/*target.draw(Entity::up_sensor_rect, states);
		target.draw(Entity::down_sensor_rect, states);
		target.draw(Entity::left_sensor_rect, states);
		target.draw(Entity::right_sensor_rect, states);*/
	}
}

void Hero::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{	
	if (isActive())
	{
		animation.update(dt);
		action_tree.update(dt);

		if (is_colliding) collision_rect.setOutlineColor(sf::Color::Red);
		else collision_rect.setOutlineColor(sf::Color::Green);
		setCollision(false);
	}

	if (is_invincible)
	{
		time_invincible -= dt;

		if (time_invincible == sf::Time::Zero)
		{
			is_invincible = false;
		}
	}
}





unsigned int Hero::getCategory() const
{ 
	return Category::Player;
}

void Hero::attack()
{
	current_weapon->hit(getCurrentDirection());
}



void Hero::moveRight(int px)
{
	Action GoRight;
	GoRight.is_blocking = true;
	GoRight.thread_id = 0;

	GoRight.action = get_action([this, px](sf::Time dt)
	{
		return goRightUntil(px, dt);
	});

	action_tree.push(GoRight);
}

void Hero::moveLeft(int px)
{
	Action GoLeft;
	GoLeft.is_blocking = true;
	GoLeft.thread_id = 0;

	GoLeft.action = get_action([this, px](sf::Time dt)
	{
		return this->goLeftUntil(px, dt);
	});

	action_tree.push(GoLeft);
}

void Hero::moveDown(int px)
{
	Action GoDown;
	GoDown.is_blocking = true;
	GoDown.thread_id = 0;

	GoDown.action = get_action([this, px](sf::Time dt)
	{
		return this->goDownUntil(px, dt);
	});

	action_tree.push(GoDown);
}

void Hero::moveUp(int px)
{
	Action GoUp;
	GoUp.is_blocking = true;
	GoUp.thread_id = 0;

	GoUp.action = get_action([this, px](sf::Time dt)
	{
		return this->goUpUntil(px, dt);
	});

	action_tree.push(GoUp);
}





void Hero::recieveDamage(float seconds)
{ 
	is_invincible = true; 
	time_invincible = sf::seconds(seconds); 
	fade.restart(1.0f, 0.1f);
	std::unique_ptr<Effect> effect(new Effect(sprite));
	fade.setNumLoops(8);
	effect->setLifeTime(0.3f);
	effect->spriteOn();
	effect->addAffector(fade);
	this->addChild(std::move(effect));
	
}

void Hero::addWeapon(WeaponType weapon_type, sf::Vector2f rect_size, float attack_delay, float attack_time, int damage)
{
	std::unique_ptr<Weapon> weapon(new Weapon(weapon_type));
	current_weapon = weapon.get();
	current_weapon->setRect(rect_size);
	current_weapon->setAttackDelay(attack_delay);
	current_weapon->setAttackTime(attack_time);
	current_weapon->setDamage(damage);
	this->addChild(std::move(weapon));
	
}




