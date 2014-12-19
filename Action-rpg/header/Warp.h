#pragma once

#include "SceneNode.h"

class Warp : public SceneNode
{
	public:
		explicit Warp(sf::RectangleShape c_rect);
		~Warp() { std::cout << "Warp deleted" << std::endl; }

		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time df);
		virtual unsigned int getCategory() const { return Category::Warp; }
		sf::FloatRect getGlobalRect();
		
		inline void setDestiny(sf::Vector2f des) { warp_destiny = des; }
		inline sf::Vector2f getDestiny() { return warp_destiny; }
		inline void setLevelScriptName(std::string name) { level_script_name = name; }
		inline std::string getLevelScriptName() { return level_script_name; }
		inline int getFirstAnimation(){ return first_animation; }
		inline void setFirstAnimation(int type){ first_animation = type; }

	private:
		sf::RectangleShape warp_rect;
		sf::Vector2f    warp_destiny;
		std::string  level_script_name;
		int first_animation;

};

