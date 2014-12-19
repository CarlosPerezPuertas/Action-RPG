#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <functional>
//#include "ResourceTypes.h"
//#include "Resources.h"
#include "ScreenAffectors.h"
#include "SceneNode.h"


//ScreeEffect class is used to do simple effects in the screen that are applied in the whole screen.
//For example to make transition between stages we fade the screen making it dark in order to make softs transitions

/*######INSTRUCTIONS######
	
	1 Create Screen effect clas and assign a texture  => ScreenEffect(sf::Texture &texture);
			 or a shape specifying the size and color => ScreenEffect(sf::Vector2i rect, sf::Color color);	
	
	2 Set a lifetime.                                 => screen_effect.setLifeTime(sf::seconds(2.f));

	3 Create an affector.                             => FadeAffector fade(double init_alpha , int end_alpha)

	4 Add the affector to the screen effect system.   => screen_effect.addAffector(fade);
	  Because it's a template it's compatible with 
	  differents affectors.

	Options:

	a If you want to have a soft clear screen         => screen_effect.addClearRectangle(window_size);

																			+

														     screen_effect.addAffector(fade);

	At this moment there is only one affector.
*/


class Effect : public SceneNode
{
	public:
		typedef std::vector<std::function<void(Effect&, sf::Time)>> Affectors;

	public:
		explicit Effect(sf::Sprite &c_sprite);
		~Effect(){ std::cout << "ScreenEffect deleted " << std::endl; }

		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		void updateScreen(const sf::Time dt);
		virtual unsigned int getCategory() const{ if (is_on_screen)return Category::ScreenEffect; 
																   return Category::EntityEffect; }
		 
		template<typename T>
		void addAffector(T aff);
		void addClearRectangle();
		void screenOn(){ is_on_screen = true; }
		void spriteOn(){ is_for_sprite = true; }


		//void setTexture(sf::Texture &texture);
		//void setTexture(sf::Vector2i rect, sf::Color color);
		inline void restart(){ elapsed = sf::Time::Zero; is_clearing = true; affectors.clear(); }
		inline void setLifeTime(float lifetime){ this->lifetime = sf::seconds(lifetime); }
		inline void setAlpha(sf::Uint8 alpha){ sprite.setColor(sf::Color(255, 255, 255, alpha)); clear_rectangle.setFillColor(sf::Color(color.r, color.g, color.b, alpha)); }
		bool isRunning();
	
	public:   
		sf::Color color;     //Attributes used in affectors
		sf::Time elapsed;	
		sf::Time lifetime;
		sf::Sprite &sprite;
		sf::Sprite sprite_restart;
		
	private:
		
		
		bool is_on_screen;
		bool is_clearing;				    // The difference between window.clear() it's that this have alpha chanel
		bool is_for_sprite;
		sf::RectangleShape clear_rectangle; // Used to make soft transitions
		
		Affectors affectors;	
};

template<typename T>
void Effect::addAffector(T aff)
{
	aff.init(*this);
	affectors.push_back(aff.get());
}




