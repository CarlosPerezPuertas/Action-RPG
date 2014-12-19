#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "Command.h"
#include "Hero.h"

class ActionQueue;

enum class PlayerAction
{
	GoLeft,
	GoRight,
	GoUp,
	GoDown,
	Attack,
};

class Player
{
	
	public:
		Player();

		void updateInput(ActionTree &action_tree);
		inline void disable() { keyboard_works = false; last_key_pressed = sf::Keyboard::A; }
		inline void enable()  { keyboard_works = true; }
		inline const bool isEnabled() const { return keyboard_works; }
		void initAction(PlayerAction action);
		inline void setPlayer(Hero *c_hero){ hero = c_hero; last_key_pressed = sf::Keyboard::X; hero->stopAnimation(); }
		void releaseKeys();


	private:

		PlayerAction current_action;
		std::map<sf::Keyboard::Key, PlayerAction> key_to_action;
		std::map<PlayerAction, Action> action_to_command;
		Hero *hero;
		
		std::set<sf::Keyboard::Key> keys_pressed;
		sf::Keyboard::Key last_key_pressed;

		bool keyboard_works;
		bool is_attacking;
		bool X_Pressed;
};


