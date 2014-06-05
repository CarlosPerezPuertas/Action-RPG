#include "..\header\Player.h"

#include "..\header\Hero.h"
#include "..\header\CommandQueue.h"
#include "..\header\ActionTree.h"
#include "..\core\header\GameApp.h"


Player::Player() 
: current_action(PlayerAction::GoDown)
, keyboard_works(true)
, hero(nullptr)
, X_Pressed(true)
{
	key_to_action[sf::Keyboard::Left] = PlayerAction::GoLeft;
	key_to_action[sf::Keyboard::Right] = PlayerAction::GoRight;
	key_to_action[sf::Keyboard::Up] = PlayerAction::GoUp;
	key_to_action[sf::Keyboard::Down] = PlayerAction::GoDown;
	key_to_action[sf::Keyboard::X] = PlayerAction::Attack;

	Action go_left; Action go_right; Action go_up; Action go_down; Action attack;
	go_left.thread_id = 0; go_right.thread_id = 0; go_up.thread_id = 0; go_down.thread_id = 0; attack.thread_id = 0;

	go_left.action = get_action([&](sf::Time dt)
	{
		if (hero->isActive() && !hero->isAttack())
		{
			if (hero->isPossibleDirection(Direction::Left))
			{
				hero->playAnimation();
				hero->setCurrentDirection(Direction::Left);
				hero->setOrientation(Direction::Left);
				hero->move(sf::Vector2f(-hero->getSpeedRatio() * dt.asSeconds(), 0));
				if (hero->isOtherAnimation(static_cast<int>(Animations::GoLeft))) hero->changeAnimation(static_cast<int>(Animations::GoLeft));
			}
			else if (hero->isPossibleDirection(hero->getCurrentDirection()))
			{
				hero->moveByMap(hero->getCurrentDirection(), dt);
			}
			else
			{
				hero->stopAnimation();
				hero->setCurrentDirection(Direction::None);
			}
		}
		return false;
	});

	go_right.action = get_action([&](sf::Time dt)
	{
		if (hero->isActive() && !hero->isAttack())
		{
			if (hero->isPossibleDirection(Direction::Right))
			{
				hero->playAnimation();
				hero->setCurrentDirection(Direction::Right);
				hero->setOrientation(Direction::Right);
				hero->move(sf::Vector2f(hero->getSpeedRatio() * dt.asSeconds(), 0));
				if (hero->isOtherAnimation(static_cast<int>(Animations::GoRight))) hero->changeAnimation(static_cast<int>(Animations::GoRight));
			}
			else if (hero->isPossibleDirection(hero->getCurrentDirection()))
			{
				hero->moveByMap(hero->getCurrentDirection(), dt);
			}
			else
			{
				hero->stopAnimation();
				hero->setCurrentDirection(Direction::None);
			}
		}
		return false;
	});
	
	go_up.action = get_action([&](sf::Time dt)
	{ 
		if (hero->isActive() && !hero->isAttack())
		{
			if (hero->isPossibleDirection(Direction::Up))
			{
				hero->playAnimation();
				hero->setCurrentDirection(Direction::Up);
				hero->setOrientation(Direction::Up);
				hero->move(sf::Vector2f(0, -hero->getSpeedRatio() * dt.asSeconds()));
				if (hero->isOtherAnimation(static_cast<int>(Animations::GoUp))) hero->changeAnimation(static_cast<int>(Animations::GoUp));
			}
			else if (hero->isPossibleDirection(hero->getCurrentDirection()))
			{
				hero->moveByMap(hero->getCurrentDirection(), dt);
			}
			else
			{
				hero->stopAnimation();
				hero->setCurrentDirection(Direction::None);
			}
		}

		return false;
	});
	
	go_down.action = get_action([&](sf::Time dt)
	{ 
		if (hero->isActive() && !hero->isAttack())
		{
			if (hero->isPossibleDirection(Direction::Down))
			{
				hero->playAnimation();
				hero->setCurrentDirection(Direction::Down);
				hero->setOrientation(Direction::Down);
				hero->move(sf::Vector2f(0, hero->getSpeedRatio() * dt.asSeconds()));
				if (hero->isOtherAnimation(static_cast<int>(Animations::GoDown))) hero->changeAnimation(static_cast<int>(Animations::GoDown));
			}

			else if (hero->isPossibleDirection(hero->getCurrentDirection()))
			{
				hero->moveByMap(hero->getCurrentDirection(), dt);
			}
			else
			{
				hero->stopAnimation();
				hero->setCurrentDirection(Direction::None);
			}
		}

		return false;
	});

	attack.action = get_action([&](sf::Time dt)
	{
		if (!hero->isAttack() && !X_Pressed)
		{
			hero->attack();
			hero->playAnimation();
			hero->setAttack(true);
			X_Pressed = true;

			if (hero->getOrientation() == Direction::Down)
			{
				if (hero->isOtherAnimation(static_cast<int>(Animations::Sword01Down))) hero->changeAnimation(static_cast<int>(Animations::Sword01Down));
			}
			else if (hero->getOrientation() == Direction::Up)
			{
				if (hero->isOtherAnimation(static_cast<int>(Animations::Sword01Up))) hero->changeAnimation(static_cast<int>(Animations::Sword01Up));
			}
			else if (hero->getOrientation() == Direction::Left)
			{
				if (hero->isOtherAnimation(static_cast<int>(Animations::Sword01Left))) hero->changeAnimation(static_cast<int>(Animations::Sword01Left));
			}
			else if (hero->getOrientation() == Direction::Right)
			{
				if (hero->isOtherAnimation(static_cast<int>(Animations::Sword01Right))) hero->changeAnimation(static_cast<int>(Animations::Sword01Right));
			}
		}

		if (hero->isAttack() && hero->isAnimating() == false)
		{
			std::cout << "End down" << std::endl;

			if (hero->getOrientation() == Direction::Down) hero->changeAnimation(static_cast<int>(Animations::GoDown));
			else if (hero->getOrientation() == Direction::Up) hero->changeAnimation(static_cast<int>(Animations::GoUp));
			else if (hero->getOrientation() == Direction::Left) hero->changeAnimation(static_cast<int>(Animations::GoLeft));
			else if (hero->getOrientation() == Direction::Right) hero->changeAnimation(static_cast<int>(Animations::GoRight));

			hero->setAttack(false);
			hero->stopAnimation();

			is_attacking = false;

			return false;
		}

		if (hero->isAttack()) return true;
		
		
		return false;
		
	});


	action_to_command[PlayerAction::GoLeft] = go_left;
	action_to_command[PlayerAction::GoRight] = go_right;
	action_to_command[PlayerAction::GoUp] = go_up;
	action_to_command[PlayerAction::GoDown] = go_down;
	action_to_command[PlayerAction::Attack] = attack;
}

void Player::initAction(PlayerAction action)
{ 
	//current_action = action;
	last_key_pressed = sf::Keyboard::X;
	//hero->pushAction(action_to_command[current_action]);
	hero->stopAnimation();
}

void Player::releaseKeys()
{
	//if (GameApp::event.type == sf::Event::KeyReleased && GameApp::event.key.code == sf::Keyboard::X)
	
	//if (keys_pressed.find(sf::Keyboard::X) == keys_pressed.end())
	if (GameApp::event.type == sf::Event::KeyPressed && GameApp::event.key.code == sf::Keyboard::X)
	{
		//std::cout << "Released" << std::endl;
		X_Pressed = false;
	}
	if (hero != nullptr)
	if (GameApp::event.type == sf::Event::KeyReleased && !hero->isAttack())
	{
		if (keys_pressed.find(sf::Keyboard::Left) == keys_pressed.end() && keys_pressed.find(sf::Keyboard::Right) == keys_pressed.end() &&
			keys_pressed.find(sf::Keyboard::Down) == keys_pressed.end() && keys_pressed.find(sf::Keyboard::Up) == keys_pressed.end())
		{
			if (hero->isAnimating()) hero->stopAnimation();
		}
	}
	
}


void Player::updateInput(ActionTree &action_tree)
{
	bool direction_pressed = false;
	bool attack_pressed = false;

	if (keyboard_works == true)
	{
		releaseKeys();

		for (auto &itr : key_to_action)
		{
			if (keys_pressed.find(sf::Keyboard::X) != keys_pressed.end())
			{
				attack_pressed = true;
			}

			if (keys_pressed.find(sf::Keyboard::Left) != keys_pressed.end() || keys_pressed.find(sf::Keyboard::Right) != keys_pressed.end() ||
				keys_pressed.find(sf::Keyboard::Up) != keys_pressed.end() || keys_pressed.find(sf::Keyboard::Down) != keys_pressed.end())
			{
				direction_pressed = true;
			}

			//If the key is pressed add to the set. If not then delete from the set.
			//If it's a new key then refresh the last_key_pressed and current_action
			if (sf::Keyboard::isKeyPressed(itr.first))
			{
				
				auto key = keys_pressed.find(itr.first);
				if (key == keys_pressed.end() ) //&& (direction_pressed || attack_pressed)
				{
					last_key_pressed = itr.first;
					keys_pressed.insert(last_key_pressed);
				}
			}
			else
			{
				auto key = keys_pressed.find(itr.first);
				if (key != keys_pressed.end())
				{
					keys_pressed.erase(itr.first);				
				}		
			}
		}

		//Only one direction 
		if (attack_pressed)
		{
			if (hero != nullptr)
			if (hero->isAttack() == false )
			{
				//std::cout << "Attack" << std::endl;
				is_attacking = true;
				current_action = key_to_action[last_key_pressed];
				hero->pushAction(action_to_command[current_action]);
			}
		}
		else if (direction_pressed && last_key_pressed != sf::Keyboard::X)
		{
			//if (last_key_pressed == sf::Keyboard::X) std::cout << "Error" << std::endl;
			
			current_action = key_to_action[last_key_pressed];
			hero->pushAction(action_to_command[current_action]);
		}	
	}
}

