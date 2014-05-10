#include "..\header\Hero.h"




Hero::Hero(int c_texture_id)
: MoveableObject()
, animation(Entity::sprite, sf::seconds(0.13f), 0)
, action_queue(*this)
, texture_id(c_texture_id)

{
	//makeGlobal();
	//Allowed directions
	possible_directions.insert(Direction::Right);
	possible_directions.insert(Direction::Left);
	possible_directions.insert(Direction::Up);
	possible_directions.insert(Direction::Down);
}


void Hero::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isActive())
	{
		target.draw(Entity::sprite, states);
		target.draw(Entity::collision_rect, states);
	}
		

}

void Hero::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (isActive())
	{
		animation.update(dt);

		if (is_colliding) collision_rect.setOutlineColor(sf::Color::Red);
		else collision_rect.setOutlineColor(sf::Color::Green);
		setCollision(false);
	
		
		//action_queue.update(dt);
	}
}

void Hero::changeAnimation(const int state)
{
	animation.changeState(state);
	animation.play();
}



unsigned int Hero::getCategory() const
{ 
	return Category::Player;
}



void Hero::moveRight(int px)
{
	Action GoRight;


	GoRight.action = get_action<Hero>([this, px](Hero &m_player, sf::Time dt)
	{
		return goRightUntil(px);
	});

	action_queue.push(GoRight);
}

void Hero::moveLeft(int px)
{
	Action GoLeft;

	GoLeft.action = get_action<Hero>([this, px](Hero &m_player, sf::Time dt)
	{
		return this->goLeftUntil(px);

	});

	action_queue.push(GoLeft);
}

void Hero::moveDown(int px)
{
	Action GoDown;

	GoDown.action = get_action<Hero>([this, px](Hero &m_player, sf::Time dt)
	{

		return this->goDownUntil(px);

	});

	action_queue.push(GoDown);
}

void Hero::moveUp(int px)
{
	Action GoUp;

	GoUp.action = get_action<Hero>([this, px](Hero &m_player, sf::Time dt)
	{
		return this->goUpUntil(px);

	});

	action_queue.push(GoUp);
}

void Hero::setPosition(sf::Vector2f pos)
{
	sf::Transformable::setPosition(pos);
}

void Hero::setPosition(float x, float y)
{
	sf::Transformable::setPosition(sf::Vector2f(x, y));
}

void Hero::scale(sf::Vector2f factor)
{
	sf::Transformable::scale(factor);
}

void Hero::scale(float x, float y)
{
	sf::Transformable::scale(sf::Vector2f(x, y));
}

void Hero::addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height)
{
	if (distribution == "H")
	{
		for (int i = 0; i < num_frames; i++)
		{
			animation.addFrame(anim_type, sf::IntRect(i*width, (position-1) * height, width, height));
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






