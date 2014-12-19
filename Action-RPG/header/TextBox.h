#pragma once


#include "Text.h"
#include "Image.h"
#include <iterator> 

class TextBox : public SceneNode
{
	public:
		TextBox(std::string c_text);
		TextBox();

		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

		inline virtual unsigned int getCategory() const { return Category::Text; }
		void init(sf::Vector2f camera_center);

		void insertNewLine(float x_camera, float y_camera);
		void setText(std::string c_text);
		void setFont(std::string filename);

		bool isNext();
		void next();
		void nextLetter();
		inline void setDisplay(bool display){ is_displaying = display; }
		inline bool isDisplaying(){ return is_displaying; }


	private:
		//Box elements
		sf::RectangleShape box;
		Image continue_button;
		
		//Raw text
		std::string font;
		std::string current_text;
		sf::Text sfml_text_no_processed;

		//Text processed
		std::vector<std::string> texts;
		std::vector<std::unique_ptr<Text>> sfml_texts;
		std::vector<std::unique_ptr<Text>>::iterator itr_text;
		unsigned int itr_counter;
		
		//Letter by letter display
		const sf::Time text_velocity;
		sf::Time next_letter_time;
		bool is_displaying;
		unsigned int letter_index;
		
};

