#include "..\header\TextBox.h"
#include "..\header\World.h"

TextBox::TextBox()
: itr_counter(0)
, text_velocity(sf::seconds(0.05f))
, next_letter_time(text_velocity)
{
	
	
	key = "no";
}

TextBox::TextBox(std::string c_text)
: current_text(c_text)
, itr_counter(0)
{
	

}

void TextBox::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (hasLifetime == true)
	{
		lifetime_elapsed -= dt;

		if (lifetime_elapsed <= sf::Time::Zero)
		{
			hasLifetime = false;
			removeFromScene();
		}
	}

	if (isDisplaying())
	{
		next_letter_time -= dt;
		if (next_letter_time <= sf::Time::Zero)
		{
			next_letter_time = text_velocity;
			nextLetter();
		}
	}
	else continue_button.updateAnimation(dt);
}

void TextBox::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(box, states);
	target.draw(*itr_text->get(), states);
	if(is_displaying == false) target.draw(continue_button, states);
}

void TextBox::setText(std::string c_text)
{
	current_text = c_text;
	sfml_text_no_processed.setString(current_text);

}

void TextBox::setFont(std::string filename)
{
	font = filename;

}


void TextBox::init(sf::Vector2f camera_center)
{
	continue_button.setTexture(World::current_level->getTG().get(SystemImage::TextContinueButton));
	continue_button.addAnimationFrames(0, "H", "Loop", 4, 1, 23, 23);

	box.setFillColor(sf::Color(0, 0, 210, 150));

	float x = camera_center.x;
	float y = camera_center.y;

	box.setSize(sf::Vector2f(1000.f, 350.f));
	box.setPosition(sf::Vector2f(x - 500, y ));

	sf::Font fo;
	fo.loadFromFile(font);
	sfml_text_no_processed.setFont(fo);
	sfml_text_no_processed.setPosition(sf::Vector2f(x - 500 + 50,y + 50));
	sfml_text_no_processed.setCharacterSize(25);
	sfml_text_no_processed.setColor(sf::Color::White);

	continue_button.setPosition(sf::Vector2f(box.getPosition().x + box.getSize().x - 50, box.getPosition().y + box.getSize().y - 50));

	
	insertNewLine(x, y);
	nextLetter();
}

void TextBox::insertNewLine(float x_camera, float y_camera)
{

	char x = 'f';
	unsigned int jump_index_correction = 0;

	//Put new lines
	for (unsigned int i = 0; i < current_text.size() ; ++i)
	{
		if (sfml_text_no_processed.findCharacterPos(i).x - sfml_text_no_processed.getGlobalBounds().left > 850.f)
		{
			x = current_text[i - 1];

			while (x != ' ' && i - jump_index_correction >= 0)
			{
				jump_index_correction++;
				if (i - jump_index_correction > 0) x = current_text[i - jump_index_correction - 1];
			}

			current_text.insert(i - jump_index_correction, "\n");
			jump_index_correction = 0;
			sfml_text_no_processed.setString(current_text);
		}
	}

	int index_substract = -1;
	bool y_found = false;
	bool continue_subs = true;

	//Substract parts of the text to make the necesarry text boxes.
	std::string text_copy = current_text;
	while (continue_subs)
	{
		for (unsigned int i = 0; i < text_copy.size() && y_found == false; ++i)
		{
			if (sfml_text_no_processed.findCharacterPos(i).y - sfml_text_no_processed.getGlobalBounds().top > 50.f)
			{
				index_substract = i;
				y_found = true;
			}
		}

		if (y_found)
		{
			y_found = false;
			std::string text_part = text_copy.substr(0, index_substract);
			texts.push_back(text_part);
			std::unique_ptr<Text> new_text(new Text(text_part));
			new_text->initForTextBox(x_camera, y_camera);
			new_text->setFont(font);
			sfml_texts.push_back(std::move(new_text));
			text_copy.erase(0, index_substract);
			
		}
		else
		{
			continue_subs = false;
			texts.push_back(text_copy);
			std::unique_ptr<Text> new_text(new Text(text_copy));
			new_text->initForTextBox(x_camera, y_camera);
			new_text->setFont(font);
			sfml_texts.push_back(std::move(new_text));
		}		
	}

	
	itr_text = sfml_texts.begin();	
}

bool TextBox::isNext()
{
	if (itr_counter >= sfml_texts.size() - 1) return false;
	return true;
}

void TextBox::next()
{
	if (isNext())
	{
		letter_index = 0;
		itr_text++;
		itr_counter++;
		nextLetter();
		is_displaying = true;
	}
}

//Show letters
//When all letters are displayed we can press the button to continue
void TextBox::nextLetter()
{
	std::string text_copy = texts[itr_counter];
	std::string s_text_to_show = text_copy.substr(0, letter_index);
	itr_text->get()->setText(s_text_to_show);

	if (letter_index == texts[itr_counter].size() ) is_displaying = false;
	
	letter_index++;	
}
