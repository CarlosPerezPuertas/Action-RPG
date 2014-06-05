#pragma once

#include "SceneNode.h"

enum TextType
{
	Static,
	Score,
	HighScore
};

class Text : public SceneNode
{
	public:
		Text(std::string c_text);
		Text(){}
		~Text(){ std::cout << "Deleted text" << std::endl; }

		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time df);

		void setColor(sf::Color color);
		void setSize(unsigned int size);
		void setFont(std::string font_type);

		virtual unsigned int getCategory() const;
		inline void setText(std::string data){ current_text = data;  text.setString(data); }
		inline const TextType getType() const { return type; }
		void initForTextBox(float x_camera, float y_camera);
		//inline void setLifeTime(float seconds) { hasTime = true;  lifetime = sf::seconds(seconds); }
		

	private:
		sf::Font font;
		TextType type;

	protected:
		sf::Text text;
		std::string current_text;

};

