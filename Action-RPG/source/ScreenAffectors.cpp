#include "..\header\ScreenAffectors.h"

#include "..\header\ScreenEffect.h"


FadeAffector::FadeAffector(double i_alpha, double e_alpha) 
: init_alpha(i_alpha)
, end_alpha(e_alpha)
, initialized(false)
, num_loops(1)
{  
	affector = createAffector();
}


std::function<void(Effect&, sf::Time)>
FadeAffector::createAffector()
{
	return[this](Effect& effect, sf::Time df) mutable
	{

		
		if (effect.elapsed < effect.lifetime)
		{
			//effect.elapsed += df;
			double ratio = static_cast<double>(effect.elapsed.asMilliseconds()) / static_cast<double>(effect.lifetime.asMilliseconds());
			double adapted_ratio = getInit() + ratio * (getEnd() - getInit());

			if (effect.getCategory() == Category::ScreenEffect)
			{
				if (adapted_ratio > 0.0 && adapted_ratio < 1.0)
					effect.color.a = static_cast<sf::Uint8>(255 * adapted_ratio);
				else if (adapted_ratio <= 0.0) adapted_ratio = static_cast<sf::Uint8>(0.0);
				else if (adapted_ratio >= 1.0) adapted_ratio = static_cast<sf::Uint8>(1.0);
			}
			else
			{
				//std::cout << static_cast<int>(effect.sprite.getColor().r) << " " << static_cast<int>(effect.sprite.getColor().g) << " " << static_cast<int>(effect.sprite.getColor().b) << std::endl;
				//std::cout << getEnd() * 255 << " " << static_cast<int>(effect.sprite.getColor().a) << " " << adapted_ratio << std::endl;
				if (adapted_ratio >= 0.0 && adapted_ratio <= 1.0)
					effect.sprite.setColor(sf::Color(255, 255, 255, 255 * adapted_ratio));
				//else if (adapted_ratio <= 0.0) adapted_ratio = static_cast<sf::Uint8>(0.0);
				//else if (adapted_ratio >= 1.0) adapted_ratio = static_cast<sf::Uint8>(1.0);
				
			}
		}
		else
		{
			if (effect.getCategory() != Category::ScreenEffect)
			{
				num_loops--;
				effect.elapsed = sf::seconds(0.f);
				std::swap(init_alpha, end_alpha);
			}	
		}

		if (effect.getCategory() != Category::ScreenEffect && num_loops == 0)
		{
			effect.sprite.setColor(effect.sprite_restart.getColor());
			effect.removeFromScene();
		}
		
	};
}

void FadeAffector::init(Effect &effect)
{ 
	effect.setAlpha(static_cast<sf::Uint8>(255*init_alpha)); 
}


ColorAffector::ColorAffector(double i_alpha, double e_alpha)
: init_alpha(i_alpha)
, end_alpha(e_alpha)
, initialized(false)
, num_loops(1)
{
	affector = createAffector();
}


std::function<void(Effect&, sf::Time)>
ColorAffector::createAffector()
{
	return[this](Effect& effect, sf::Time df) mutable
	{


		if (effect.elapsed < effect.lifetime)
		{
			//effect.elapsed += df;
			double ratio = static_cast<double>(effect.elapsed.asMilliseconds()) / static_cast<double>(effect.lifetime.asMilliseconds());
			double adapted_ratio = getInit() + ratio * (getEnd() - getInit());

			if (effect.getCategory() == Category::ScreenEffect)
			{
				if (adapted_ratio > 0.0 && adapted_ratio < 1.0)
					effect.color.a = static_cast<sf::Uint8>(255 * adapted_ratio);
				else if (adapted_ratio <= 0.0) adapted_ratio = static_cast<sf::Uint8>(0.0);
				else if (adapted_ratio >= 1.0) adapted_ratio = static_cast<sf::Uint8>(1.0);
			}
			else
			{
				//std::cout << static_cast<int>(effect.sprite.getColor().r) << " " << static_cast<int>(effect.sprite.getColor().g) << " " << static_cast<int>(effect.sprite.getColor().b) << std::endl;
				//std::cout << getEnd() * 255 << " " << static_cast<int>(effect.sprite.getColor().a) << " " << adapted_ratio << std::endl;
				if (adapted_ratio >= 0.0 && adapted_ratio <= 1.0)
					effect.sprite.setColor(sf::Color(255, 255, 255, 255 * adapted_ratio));
				//else if (adapted_ratio <= 0.0) adapted_ratio = static_cast<sf::Uint8>(0.0);
				//else if (adapted_ratio >= 1.0) adapted_ratio = static_cast<sf::Uint8>(1.0);

			}
		}
		else
		{
			num_loops--;
			effect.elapsed = sf::seconds(0.f);
			std::swap(init_alpha, end_alpha);
		}

		if (effect.getCategory() != Category::ScreenEffect && num_loops == 0)
		{
			effect.sprite.setColor(effect.sprite_restart.getColor());
			effect.removeFromScene();
		}

	};
}

void ColorAffector::init(Effect &effect)
{
	effect.setAlpha(static_cast<sf::Uint8>(255 * init_alpha));
}

