#include "..\header\Player.h"

#include "..\header\Hero.h"
#include "..\header\CommandQueue.h"


Player::Player() 
: current_action(PlayerAction::GoLeft)
, keyboard_works(true)
{
	key_to_action[sf::Keyboard::Left] = PlayerAction::GoLeft;
	key_to_action[sf::Keyboard::Right] = PlayerAction::GoRight;
	key_to_action[sf::Keyboard::Up] = PlayerAction::GoUp;
	key_to_action[sf::Keyboard::Down] = PlayerAction::GoDown;

	Command go_left; Command go_right; Command go_up; Command go_down;

	go_left.category = Category::Player;
	go_right.category = Category::Player;
	go_up.category = Category::Player;
	go_down.category = Category::Player;

	
	go_left.action = get_function<Hero>([](Hero &m_player, sf::Time dt)
	{
		if (m_player.isActive())
		{
			if (m_player.isPossibleDirection(Direction::Left))
			{
				m_player.playAnimation();
				m_player.setCurrentDirection(Direction::Left);
				m_player.setOrientation(Direction::Left);
				m_player.move(sf::Vector2f(-m_player.getSpeedRatio() * dt.asSeconds(), 0));
				if (m_player.isOtherAnimation(static_cast<int>(Animations::GoLeft))) m_player.changeAnimation(static_cast<int>(Animations::GoLeft));
			}
			else if (m_player.isPossibleDirection(m_player.getCurrentDirection()))
			{
				m_player.moveByMap(m_player.getCurrentDirection(), dt);
			}
			else
			{
				m_player.stopAnimation();
				m_player.setCurrentDirection(Direction::None);
			}
		}
	});

	go_right.action = get_function<Hero>([](Hero &m_player, sf::Time dt)
	{
		if (m_player.isActive())
		{
			if (m_player.isPossibleDirection(Direction::Right))
			{
				m_player.playAnimation();
				m_player.setCurrentDirection(Direction::Right);
				m_player.setOrientation(Direction::Right);
				m_player.move(sf::Vector2f(+m_player.getSpeedRatio() * dt.asSeconds(), 0));
				if (m_player.isOtherAnimation(static_cast<int>(Animations::GoRight))) m_player.changeAnimation(static_cast<int>(Animations::GoRight));
			}
			else if (m_player.isPossibleDirection(m_player.getCurrentDirection()))
			{
				m_player.moveByMap(m_player.getCurrentDirection(), dt);
			}
			else
			{
				m_player.stopAnimation();
				m_player.setCurrentDirection(Direction::None);
			}
		}
	});
	
	go_up.action = get_function<Hero>([](Hero &m_player, sf::Time dt)
	{ 
		if (m_player.isActive())
		{
			if (m_player.isPossibleDirection(Direction::Up))
			{
				m_player.playAnimation();
				m_player.setCurrentDirection(Direction::Up);
				m_player.setOrientation(Direction::Up);
				m_player.move(sf::Vector2f(0, -m_player.getSpeedRatio() * dt.asSeconds()));
				if (m_player.isOtherAnimation(static_cast<int>(Animations::GoUp))) m_player.changeAnimation(static_cast<int>(Animations::GoUp));
			}
			else if (m_player.isPossibleDirection(m_player.getCurrentDirection()))
			{
				m_player.moveByMap(m_player.getCurrentDirection(), dt);
			}
			else
			{
				m_player.stopAnimation();
				m_player.setCurrentDirection(Direction::None);
			}
		}	
	});
	
	go_down.action = get_function<Hero>([](Hero &m_player, sf::Time dt)
	{ 
		if (m_player.isActive())
		{
			if (m_player.isPossibleDirection(Direction::Down))
			{
				m_player.playAnimation();
				m_player.setCurrentDirection(Direction::Down);
				m_player.setOrientation(Direction::Down);
				m_player.move(sf::Vector2f(0, m_player.getSpeedRatio() * dt.asSeconds()));
				if (m_player.isOtherAnimation(static_cast<int>(Animations::GoDown))) m_player.changeAnimation(static_cast<int>(Animations::GoDown));
			}

			else if (m_player.isPossibleDirection(m_player.getCurrentDirection()))
			{
				m_player.moveByMap(m_player.getCurrentDirection(), dt);
			}
			else
			{
				m_player.stopAnimation();
				m_player.setCurrentDirection(Direction::None);
			}
		}
	});

	action_to_command[PlayerAction::GoLeft] = go_left;
	action_to_command[PlayerAction::GoRight] = go_right;
	action_to_command[PlayerAction::GoUp] = go_up;
	action_to_command[PlayerAction::GoDown] = go_down;
}

void Player::initAction(PlayerAction action)
{ 
	current_action = action;
	last_key_pressed = sf::Keyboard::Left;
}


void Player::updateInput(CommandQueue &command_queue)
{
	bool direction_pressed = false;


	if (keyboard_works == true)
	{
		for (auto &itr : key_to_action)
		{
			//If the key is pressed add to the set. If not then delete from the set.
			//If it's a new key then refresh the last_key_pressed and current_action
			if (sf::Keyboard::isKeyPressed(itr.first))
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					direction_pressed = true;
				}

				auto key = keys_pressed.find(itr.first);
				if (key == keys_pressed.end() && direction_pressed)
				{
					last_key_pressed = itr.first;
					keys_pressed.insert(last_key_pressed);
				}
			}
			else
			{
				auto key = keys_pressed.find(itr.first);
				if (key != keys_pressed.end()) keys_pressed.erase(itr.first);
			}
		}

		//Only one direction 
		if (direction_pressed)
		{
			current_action = key_to_action[last_key_pressed];
			command_queue.push(action_to_command[current_action]);
		}

		if (!direction_pressed)
		{
			Command no_direction;
			no_direction.category = Category::Player;
			no_direction.action = get_function<Hero>([](Hero &m_player, sf::Time dt)
			{
				if (m_player.isAnimating()) m_player.stopAnimation();
			});

			command_queue.push(no_direction);
		}
	}

	


	/*if (last_key_pressed != 0 && keyboard_works == true)
	{
		command_queue.push(action_to_command[current_action]);
		std::cout << "Hei" << std::endl;
	}*/
	
		

	//command_queue.push(action_to_command[key_to_action[last_key_pressed]]);
}

