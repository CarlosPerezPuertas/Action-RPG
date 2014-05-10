#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "Command.h"

class CommandQueue;

enum class PlayerAction
{
	GoLeft,
	GoRight,
	GoUp,
	GoDown
};

class Player
{
	
	public:
		Player();

		void updateInput(CommandQueue &command_queue);
		inline void disable() { keyboard_works = false; last_key_pressed = sf::Keyboard::A; }
		inline void enable()  { keyboard_works = true; }
		inline const bool isEnabled() const { return keyboard_works; }
		void initAction(PlayerAction action);


	private:

		PlayerAction current_action;
		std::map<sf::Keyboard::Key, PlayerAction> key_to_action;
		std::map<PlayerAction, Command> action_to_command;
		
		std::set<sf::Keyboard::Key> keys_pressed;
		sf::Keyboard::Key last_key_pressed;

		bool keyboard_works;
};


