#include "..\header\Entity.h"


Entity::Entity(sf::Texture &texture)
: SceneNode()
, sprite(texture)
, is_colliding(false)
, animation(sprite, sf::seconds(0.08f), 0)
, action_tree(4)
{
	key = "no";

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

	//0.5f and 0.25f is to avoid to get stuck in the corners
	float depht_sensor = 1.2f;
	float c = 0.4f;
	up_sensor_rect.setSize(sf::Vector2f(c_col_rect.width + c, -depht_sensor));
	up_sensor_rect.setPosition(sf::Vector2f(c_col_rect.left - c / 2.f, c_col_rect.top));
	down_sensor_rect.setSize(sf::Vector2f(c_col_rect.width + c, depht_sensor));
	down_sensor_rect.setPosition(sf::Vector2f(c_col_rect.left - c / 2.f, c_col_rect.top + c_col_rect.height));
	left_sensor_rect.setSize(sf::Vector2f(-depht_sensor, c_col_rect.height + c));
	left_sensor_rect.setPosition(sf::Vector2f(c_col_rect.left, c_col_rect.top - c / 2.f));
	right_sensor_rect.setSize(sf::Vector2f(depht_sensor, c_col_rect.height + c));
	right_sensor_rect.setPosition(sf::Vector2f(c_col_rect.left + c_col_rect.width, c_col_rect.top - c / 2.f));
	
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

sf::Vector2f Entity::getCenter()
{
	return sf::Vector2f(getPosition().x + collision_rect.getPosition().x + collision_rect.getSize().x / 2.f,
						getPosition().y + collision_rect.getPosition().y + collision_rect.getSize().y / 2.f);
}

sf::Vector2f Entity::getColisionCenter()
{
	return sf::Vector2f( collision_rect.getPosition().x + collision_rect.getSize().x / 2.f,
		                 collision_rect.getPosition().y + collision_rect.getSize().y / 2.f);
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

sf::FloatRect Entity::getLeftSensor()
{
	return getWorldTransform().transformRect(left_sensor_rect.getGlobalBounds());
}

sf::FloatRect Entity::getRightSensor()
{
	return getWorldTransform().transformRect(right_sensor_rect.getGlobalBounds());
}

sf::FloatRect Entity::getUpSensor()
{
	return getWorldTransform().transformRect(up_sensor_rect.getGlobalBounds());
}

sf::FloatRect Entity::getDownSensor()
{
	return getWorldTransform().transformRect(down_sensor_rect.getGlobalBounds());
}


void Entity::setPosition(sf::Vector2f pos)
{
	sf::Transformable::setPosition(pos);
}

void Entity::setPosition(float x, float y)
{
	sf::Transformable::setPosition(sf::Vector2f(x, y));
}



void Entity::scale(sf::Vector2f factor)
{
	sf::Transformable::scale(factor);
}

void Entity::scale(float x, float y)
{
	sf::Transformable::scale(sf::Vector2f(x, y));
}

void Entity::addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height)
{
	if (distribution == "H")
	{
		if (loop_type == "Rewind")
		{
			for (int i = num_frames - 1; i >= 0; i--)
			{
				animation.addFrame(anim_type, sf::IntRect(i*width, position, width, height));
			}

		}
		else
		for (int i = 0; i < num_frames; i++)
		{
			animation.addFrame(anim_type, sf::IntRect(i*width, position, width, height));
		}
	}
	else if (distribution == "V")
	{
		if (loop_type == "Rewind")
		{
			for (int i = num_frames - 1 ; i >= 0; i--)
			{
				animation.addFrame(anim_type, sf::IntRect(position, i * height, width, height));
			}
		}
		else
		for (int i = 0; i < num_frames; i++)
		{
			animation.addFrame(anim_type, sf::IntRect(position, i * height, width, height));
		}

	}

	if (loop_type == "OneLoop") animation.setUniqueLoop(anim_type);
	else if (loop_type == "Forward") animation.forward();
	else if (loop_type == "Rewind") animation.rewind();

}

void Entity::initAnimation(const int state)
{
	animation.changeState(state);
}


void Entity::setCollisionRect(float x, float y, float w, float h)
{
	setCollisionRect(sf::FloatRect(x, y, w, h));
}









