#pragma once

#include "State.h"
#include "World.h"


class GameState : public State
{
	public:
		GameState(StateStack &c_state_stack, sf::RenderWindow &c_window, Player &c_player, TextureGenerator &c_texture_factory);
		virtual ~GameState();

		virtual void readInput();
		virtual void update(sf::Time df);
		virtual void draw();

		virtual void enterUpdate(sf::Time df);
		virtual void exitUpdate(sf::Time df);
		virtual void enterDraw();
		virtual void exitDraw();

		//Script init
		//void addLevel(Level level);


	private:
		World world;
		sf::Time enter_time;
		sf::Time exit_time;

		sf::Time wait_to_load_time;
		bool isLoaded;
		bool isLoadBegin;
};

