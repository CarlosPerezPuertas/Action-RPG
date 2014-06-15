#pragma once

#include "SceneNode.h"


enum class Animations
{
	None,
	GoLeft,
	GoRight,
	GoUp,
	GoDown,
	Sword01Left,
	Sword01Right,
	Sword01Up,
	Sword01Down,
	Die,
};

enum SystemImage
{
	TextContinueButton = 101,
	LifeFlower = 102
};

//Forward declaration of texture and Resources
namespace sf
{
	class Texture;
	class Music;
	class SoundBuffer;
}


template <typename Resource, typename EnumType>
class Resources;


typedef Resources<sf::Texture, int> TextureGenerator;
typedef Resources<sf::SoundBuffer, int> SoundBufferFactory;

static std::mt19937 mt;


static float modulus(float x, float y)
{
	float result = 0.f;
	result = sqrt(pow(x, 2) + pow(y, 2));
	return result;
}

static sf::Vector2f normalize(float x, float y)
{
	return sf::Vector2f(x / modulus(x, y), y / modulus(x, y));
}

