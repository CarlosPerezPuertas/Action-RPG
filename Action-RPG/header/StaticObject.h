#pragma once

#include "Entity.h"

class StaticObject : public Entity
{
	public:
		StaticObject(){}
		StaticObject(sf::Texture &texture);
		virtual ~StaticObject();
};



