#pragma once

enum class Animations
{
	None,
	GoLeft,
	GoRight,
	GoUp,
	GoDown,
	Die,
	EyeLeft,
	EyeRight,
	EyeUp,
	EyeDown,
	Escape,
	EscapeFlashing
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

