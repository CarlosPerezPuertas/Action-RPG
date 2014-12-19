#include "..\header\Animation.h"



ga::Animation::Animation(sf::Sprite &c_sprite, const sf::Time dt, const int init_state) :
sprite(c_sprite)     //link with the sprite of the entity
, frame_rate(dt)
, elapsed(frame_rate)
, state(init_state)
, iterator_initialized(false)
, playing(false)
, end_loop(false)
, is_forward(false)
, is_rewind(false)
{
	
}


//If animation is playing then update depending on the frame rate of the animation

void ga::Animation::update(const sf::Time dt)
{
	if (isPlaying())
	{
		elapsed -= dt;
		assert(iterator_initialized == true); //assert if the iterator it's not initialized

		sprite.setOrigin(frame_itr->width / 2.f, frame_itr->height / 2.f); //Origin in the center

		if (elapsed <= sf::Time::Zero && end_loop == false)
		{
			++frame_itr;

			//Restart the animation
			if (frame_itr == frame_map[state].end())
			{
				frame_itr = frame_map[state].begin();
				if (isUniqueLoop()) { stop(); end_loop = true; }
				else if (is_forward) { frame_itr = frame_map[state].end() - 1; stop(); end_loop = true; is_forward = false; }
				else if (is_rewind) { frame_itr = frame_map[state].end() - 1; stop(); end_loop = true; is_rewind = false; }
			}

			elapsed = frame_rate;
			sprite.setTextureRect(*frame_itr);
		}
	}
}

//Find the animation type and check if exists, if it isn't then create
//Create and add the frame to the vector depending on the animation type

void ga::Animation::addFrame(const int id, const sf::IntRect frame_rect)
{
	auto itr = frame_map.find(id);

	if (itr == frame_map.end())
	{
		sprite.setTextureRect(frame_rect);
		std::vector<sf::IntRect> animation_frames(0);
		animation_frames.push_back(frame_rect);
		frame_map.insert(std::make_pair(id, animation_frames));
		itr = frame_map.begin();
	}
	else itr->second.push_back(frame_rect);

	//Put iterator on the initial state
	frame_itr = itr->second.begin();
	iterator_initialized = true;


}

//Change animation type and init the iterator starting in the first frame

void ga::Animation::changeState(const int id)
{
	end_loop = false;

	state = id;
	frame_itr = frame_map[id].begin();
	assert(frame_itr != frame_map[id].end()); //Assert if the id doesn't exist
	sprite.setTextureRect(*frame_itr);
	sprite.setOrigin(getFrameCenter());

}