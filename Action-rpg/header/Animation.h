#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>


namespace ga
{
	//Template to associate different types of animations in each entity

	class Animation
	{
	public:
		//Associate a sprite_sheet, the duration of each frame and the animation template-type
		explicit Animation(sf::Sprite &c_sprite, const sf::Time dt, const int init_state);

		void update(const sf::Time dt);

		void addFrame(const int id, const sf::IntRect frame_rect);

		void changeState(const int id);
		int getState(){ return state; }

		inline void play(){ playing = true; }
		inline void stop(){ playing = false; }
		inline void reset(){ if (playing == true) { playing = false; frame_itr = frame_map[state].begin(); sprite.setTextureRect(*frame_itr); } }
		inline void setFrameIterator(const int advance){ if (playing == true){ stop(); frame_itr = frame_map[state].begin(); std::advance(frame_itr, 1); sprite.setTextureRect(*frame_itr); } }
		inline bool isPlaying(){ return playing; }
		inline bool isUniqueLoop() { return loop_map.find(state) != loop_map.end(); }
		inline void setUniqueLoop(int id){ loop_map.insert(id); }
		inline bool isEndLoop(){ return end_loop; }

	private:
		sf::Sprite &sprite;
		std::vector<sf::IntRect>::iterator frame_itr;
		std::map<int, std::vector<sf::IntRect>> frame_map;
		std::set<int> loop_map;

		sf::Time frame_rate;
		sf::Time elapsed;
		int   state;
		bool     playing;
		bool     iterator_initialized;
		bool     end_loop;
	};

}