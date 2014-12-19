#include "..\header\Text.h"


Text::Text(std::string c_text)
{ 
	key = "no";
	text.setString(c_text);
	text.setCharacterSize(20);
	text.setColor(sf::Color::White);
}


void Text::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void Text::updateCurrent(CommandQueue &command_queue, const sf::Time df)
{
	if (hasLifetime == true)
	{
		lifetime_elapsed -= df;

		if(lifetime_elapsed <= sf::Time::Zero)
		{
			hasLifetime = false;
			removeFromScene();
		}
	}
}

unsigned int Text::getCategory() const
{ 
	return Category::Text; 
}

void Text::setColor(sf::Color color)
{
	text.setColor(color);
}

void Text::setSize(unsigned int size)
{
	text.setCharacterSize(size);
}

void Text::setFont(std::string font_type)
{
	font.loadFromFile(font_type);
	text.setFont(font);
}

void Text::initForTextBox(float x_camera, float y_camera)
{
	text.setPosition(sf::Vector2f(x_camera - 500 + 50, y_camera + 50));
	text.setCharacterSize(25);
	text.setColor(sf::Color::White);
}

