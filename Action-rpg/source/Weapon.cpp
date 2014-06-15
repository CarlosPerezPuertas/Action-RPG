#include "..\header\Weapon.h"


Weapon::Weapon(WeaponType c_type)
: type(c_type)
, attack_time(sf::Time::Zero)
, attack_time_elapsed(sf::Time::Zero)
, attack_delay(sf::Time::Zero)
{
	
}


Weapon::~Weapon()
{
}

void Weapon::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(rect_shape, states);
}

void Weapon::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	attack_time_elapsed -= dt;
	if (attack_time_elapsed == sf::Time::Zero) rect_shape.setSize(sf::Vector2f(0.f, 0.f));

	if (hasLifetime == true)
	{
		lifetime_elapsed -= dt;

		if (lifetime_elapsed <= sf::Time::Zero)
		{
			hasLifetime = false;
			removeFromScene();
		}
	}
}

void Weapon::hit(Direction direction)
{
	attack_time_elapsed = attack_time;
	rect_shape.setSize(rect_size);
	
	if (direction == Direction::Right)
	{
		if (type == WeaponType::ObjectInHand)
		rect_shape.setPosition(sf::Vector2f(entity_center.x + 15.f, entity_center.y));
		rect_shape.setRotation(0);
	}
	else if (direction == Direction::Left)
	{
		if (type == WeaponType::ObjectInHand)
		rect_shape.setPosition(sf::Vector2f(entity_center.x - 15.f, entity_center.y));
		rect_shape.setRotation(0);
	}
	else if (direction == Direction::Up)
	{
		if (type == WeaponType::ObjectInHand)
		rect_shape.setPosition(sf::Vector2f(entity_center.x, entity_center.y - 15.f));
		rect_shape.setRotation(90);
	}
	else if (direction == Direction::Down)
	{
		if (type == WeaponType::ObjectInHand)
		rect_shape.setPosition(sf::Vector2f(entity_center.x, entity_center.y + 15.f));
		rect_shape.setRotation(90);
	}

}

sf::FloatRect Weapon::getGlobalRect()
{
	return getWorldTransform().transformRect(rect_shape.getGlobalBounds());
}
