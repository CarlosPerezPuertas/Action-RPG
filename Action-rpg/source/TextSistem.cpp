#include "..\header\TextSistem.h"


TextSistem::TextSistem()
: action_tree(3)
{
}


TextSistem::~TextSistem()
{
	std::cout << "Text sistem deleted" << std::endl;
}

void TextSistem::update(const sf::Time dt)
{
	action_tree.update(dt);
}

void TextSistem::pushTextBox(Action action)
{
	action_tree.push(action);
}

/*bool TextSistem::isEmptyTextBox()
{
	return action_tree.isEmpty();
}*/

/*void TextSistem::cleanTextBox()
{
	action_tree.clean();
}*/





