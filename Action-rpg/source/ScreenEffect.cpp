#include "..\header\ScreenEffect.h"

#include "..\header\World.h"




Effect::Effect(sf::Sprite &c_sprite)
: sprite(c_sprite)
, sprite_restart(c_sprite)
, elapsed(sf::Time::Zero)
, lifetime(sf::Time::Zero)
, is_clearing(false)
, is_for_sprite(false)
{
	
}


void Effect::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	//states.transform *= getTransform();
	
	if (is_clearing == true)
	{
		//target.draw(sprite, states);
		target.draw(clear_rectangle, states);
	}

	if (is_for_sprite == true)
	{
		target.draw(sprite, states);
	}
}

void Effect::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (getCategory() != Category::ScreenEffect)
	{
		elapsed += dt;
			
		for (auto &itr : affectors) { itr(*this, dt); }
	}
}

void Effect::updateScreen(const sf::Time dt)
{
	if (getCategory() == Category::ScreenEffect)
	{
		elapsed += dt;
		for (auto &itr : affectors) itr(*this, dt);
		
		if (is_clearing == true) clear_rectangle.setFillColor(color);
	}
}


/*void ScreenEffect::setTexture(sf::Texture &texture)
{
	sprite.setTexture(texture);
}*/

/*void ScreenEffect::setTexture(sf::Vector2i rect, sf::Color color)
{
	sf::Image image;
	image.create(rect.x, rect.y, color);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	this->color = color;
}*/

bool Effect::isRunning()
{
	//std::cout << lifetime.asSeconds() << " " << elapsed.asSeconds() << std::endl;
	return lifetime.asSeconds() > elapsed.asSeconds();
}

void Effect::addClearRectangle()
{
	float x = 0.0f;
	float y = 0.0f;

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();


	x = World::camera.getCenter().x - static_cast<float>(desktop.width/2.f);
	y = World::camera.getCenter().y - static_cast<float>(desktop.height / 2.f);

	clear_rectangle.setFillColor(sf::Color::Black);


	clear_rectangle.setSize(sf::Vector2f(desktop.width, desktop.height));
	clear_rectangle.setPosition(sf::Vector2f(x, y));
	is_clearing = true;
}





