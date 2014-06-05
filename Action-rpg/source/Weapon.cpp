#include "..\header\Weapon.h"


Weapon::Weapon()
: rect_shape(sf::Vector2f(0.f,0.f))
{
	rect_shape.setOutlineColor(sf::Color::Blue);
	rect_shape.setOutlineThickness(0.2f);
	rect_shape.setFillColor(sf::Color::Transparent);
	rect_shape.setOrigin(0.f, 0.f);
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
	attack_time -= dt;
	
	if (attack_time == sf::Time::Zero) rect_shape.setSize(sf::Vector2f(0.f, 0.f));


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
	attack_time = sf::seconds(0.5f);

	if (direction == Direction::Right)
	{
		setPosition(sf::Vector2f(10.f, -10.f));
		rect_shape.setSize(sf::Vector2f(10.f, 25.f));
	}
	else if (direction == Direction::Left)
	{
		setPosition(sf::Vector2f(-10.f, -10.f));
		rect_shape.setSize(sf::Vector2f(-10.f, 25.f));

	}
	else if (direction == Direction::Up)
	{
		setPosition(sf::Vector2f(-15.f, -5.f));
		rect_shape.setSize(sf::Vector2f(22.f, -16.f));
	}
	else if (direction == Direction::Down)
	{
		setPosition(sf::Vector2f(-8.f, 5.f));
		rect_shape.setSize(sf::Vector2f(22.f, 14.f));
	}

}

sf::FloatRect Weapon::getGlobalRect()
{
	return getWorldTransform().transformRect(rect_shape.getGlobalBounds());
}
