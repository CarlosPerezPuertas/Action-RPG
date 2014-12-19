#pragma once

#include "ActionTree.h"


class TextSistem 
{
	public:
		TextSistem();
		~TextSistem();

		void update(const sf::Time dt);
		void pushTextBox(Action action);
		//void cleanTextBox();

	private:
		ActionTree action_tree;

};

