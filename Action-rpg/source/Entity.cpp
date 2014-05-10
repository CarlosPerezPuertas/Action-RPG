#include "..\header\Entity.h"


Entity::Entity(sf::Texture &texture)
: SceneNode()
, sprite(texture)
, is_colliding(false)
{
	
}


Entity::~Entity()
{
}

void Entity::setRealRect(sf::FloatRect c_real_rect)
{ 
	//real_rect = sf::FloatRect(c_real_rect.left, c_real_rect.top, c_real_rect.width / getScale().x, c_real_rect.height / getScale().y);
	real_rect = c_real_rect;
	real_rect_minus = sf::FloatRect(c_real_rect.left - 0.5f, c_real_rect.top - 0.5f, c_real_rect.width + 1.f, c_real_rect.height + 1.f);
	collision_rect.setSize(sf::Vector2f(real_rect.width , real_rect.height ));
	collision_rect.setFillColor(sf::Color::Transparent); 
	collision_rect.setOutlineColor(sf::Color::Green); 
	collision_rect.setOutlineThickness(1);
}


void Entity::scaleEntity(sf::Vector2f factor)
{
	scale(factor);

	real_rect.left *= factor.x;
	real_rect.top *= factor.y;
	real_rect.width *= factor.x;
	real_rect.height *= factor.y;
}

sf::FloatRect Entity::getLocalRect()
{
	return sprite.getLocalBounds();
}

//The rectangle with corrected axis to make easy the collision detection
sf::FloatRect Entity::getGlobalRect()
{
	return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

sf::FloatRect Entity::getInteriorRect()
{
	return getWorldTransform().transformRect(getRealRect());
}

sf::FloatRect Entity::getInteriorRectMinus()
{
	return getWorldTransform().transformRect(real_rect_minus);
}

sf::Vector2f Entity::getCenter()
{
	sf::FloatRect rect = getGlobalRect();
	return sf::Vector2f(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}

void Entity::setOrigin(sf::Vector2f pos)
{
	sprite.setOrigin(pos);
}








