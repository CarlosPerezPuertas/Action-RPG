#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <math.h>

#include "..\..\header\Player.h"
#include "..\..\header\StateStack.h"


const float MAX_FPS = 100.f;

class GameApp
{
	public:
		GameApp();

		void run();
		void readInput();
		void update(sf::Time df);
		void render();

		void update_fps(sf::Time df);

	private:
		sf::RenderWindow window;
		Player player;
		TextureGenerator texture_generator;
		StateStack state_stack;

		sf::Time TimePerFrame;
		sf::Time OneSecondCounter;
		float frame_counter;

	public:
		static sf::Event event;	
};

