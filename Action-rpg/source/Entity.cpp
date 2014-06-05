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

void Entity::setCollisionRect(sf::FloatRect c_col_rect)
{ 
	collision_rect.setSize(sf::Vector2f(c_col_rect.width, c_col_rect.height));
	collision_rect.setPosition(sf::Vector2f(c_col_rect.left, c_col_rect.top));
	collision_rect.setFillColor(sf::Color::Transparent); 
	collision_rect.setOutlineColor(sf::Color::Green); 
	collision_rect.setOutlineThickness(0.2f);	
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



sf::FloatRect Entity::getCollisionRectExt()
{
	sf::FloatRect rect = sf::FloatRect(getCollisionRect().left - 0.5f, getCollisionRect().top - 0.5f, getCollisionRect().width + 1.f, getCollisionRect().height + 1.f);
	return rect;
}


void Entity::setOrigin(sf::Vector2f pos)
{
	sprite.setOrigin(pos);
}








