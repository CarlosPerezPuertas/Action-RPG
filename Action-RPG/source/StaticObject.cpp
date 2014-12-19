#include "..\header\StaticObject.h"


StaticObject::StaticObject(sf::Texture &texture)
: Entity(texture)
{
	key = "no";
}


StaticObject::~StaticObject()
{
}
