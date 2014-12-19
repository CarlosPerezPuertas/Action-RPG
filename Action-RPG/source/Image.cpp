#include "..\header\Image.h"

Image::Image()
: has_movement(false)
, movement_time(sf::Time::Zero)
, animation(sprite, sf::seconds(0.1f), 0)
{
	key = "no";
}

Image::Image(const int type, const TextureGenerator &tg )
: sprite(tg.get(type))
, has_movement(false)
, movement_time(sf::Time::Zero)
, animation(sprite, sf::seconds(0.1f), 0)
{
	key = "no";
}



void Image::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (isActive())
	{
		if (has_movement == true)
		{
			setPosition(sf::Vector2f(getPosition().x + displacement.x, getPosition().y + displacement.y));
			movement_time -= dt;

			if (movement_time <= sf::Time::Zero)
			{
				has_movement = false;
			}
		}

		if (is_animated) animation.update(dt);

	}
	
}

void Image::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isActive())
	target.draw(sprite, states);
}

void Image::moveDuring(sf::Vector2f c_displacement, float seconds)
{
	has_movement = true;
	displacement = c_displacement;
	movement_time = sf::seconds(seconds);
}

void Image::addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height)
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
	
	animation.play();
	is_animated = true;

}
