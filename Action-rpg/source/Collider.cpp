#include "..\header\Collider.h"

#include "..\header\World.h"
#include "..\header\Player.h"
#include "..\header\Hero.h"
#include "..\header\Npc.h"
#include "..\header\Warp.h"
#include "..\header\TextBox.h"
#include "..\header\ActionTree.h"
#include "..\core\header\GameApp.h"
#include "..\header\Weapon.h"



Collider::Collider(World &c_world, CommandQueue &c_command_queue, TextSistem &c_text_sistem, Player &c_player, LuaScripting &c_script_system)
: world(c_world)
, command_queue(c_command_queue)
, text_sistem(c_text_sistem)
, player(c_player)
, script_system(c_script_system)
, map(nullptr)
{
	//REGISTER EVENT MAP
	events[CollisionEvent::PlayerNpc] = std::make_pair(Category::Player, Category::Npc);
	events[CollisionEvent::PlayerWarp] = std::make_pair(Category::Player, Category::Warp);
	//events[CollisionEvent::SwordNpc] = std::make_pair(Category::Sword, Category::Npc);
	registerCollisions();

}


Collider::~Collider()
{
}

void Collider::registerCollisions()
{
	//CREATE FUNCTION OBJECTS WITH LAMBDAS THAT ENCAPSULATES THE BEHAVIOURS OF EACH COLLISION DEPENDING ON THE PAIRS
	CommandCollision player_npc;
	CommandCollision player_warp;
	CommandCollision enemy_player;

	/*sword_enemy.action = get_function_collision<Weapon, Npc>([this](Weapon &weapon, Npc &npc)
	{


	});*/

	
	//Register actions
	player_npc.action = get_function_collision<Hero, Npc>([this](Hero &m_player, Npc &npc)
	{
		npc.chase(m_player.getPosition());

		if (m_player.getCollisionRectExt().intersects(npc.getCollisionRect()) == true)
		{
			m_player.setCollision(true);
			//std::cout << "Collision" << std::endl;

			//Depending on the direction of the collision correct the position until the collision finishes
			Direction dir = m_player.getCurrentDirection();
			bool bounce = false;

			while (m_player.getCollisionRect().intersects(npc.getCollisionRect()) == true && dir != Direction::None)
			{
				bounce = true;

				if (dir == Direction::Left) { m_player.move(sf::Vector2f(0.5f, 0.f)); m_player.setCollisionDirection(Direction::Left); }
				else if (dir == Direction::Right) { m_player.move(sf::Vector2f(-0.5f, 0.f));  m_player.setCollisionDirection(Direction::Right); }
				else if (dir == Direction::Down) { m_player.move(sf::Vector2f(0.f, -0.5f));  m_player.setCollisionDirection(Direction::Down); }
				else if (dir == Direction::Up) { m_player.move(sf::Vector2f(0.f, 0.5f));  m_player.setCollisionDirection(Direction::Up); }
			}

			if (bounce)
			{
				m_player.stopAnimation();

				//Lose one life and turn on invicible mode
				if (m_player.isInvincible() == false)
				{
					m_player.recieveDamage(3.f);

					Command lose_life;
					lose_life.category = Category::HeroPanel;
					lose_life.action = get_function<HeroPanel>([this](HeroPanel &panel, sf::Time dt)
					{
						panel.setLifes(-1);
					});

					command_queue.push(lose_life);
				}
			}

			//DISPLAY NPC TEXT
			//We put a timer between the text begin and text exit to avoid the infinite loop (enter-exit-enter-exit....)
			//The infinite loop it's caused because the key to show the text it's the same that the exit.

			if (m_player.getCollisionDirection() == m_player.getOrientation() && npc.isTalking() == false)
			{
				TextBox *text_box(new TextBox());


				if (GameApp::event.type == sf::Event::KeyPressed && GameApp::event.key.code == sf::Keyboard::Z)
				{
					sf::Time wait_time1 = sf::seconds(0.2f);
					sf::Time wait_time2 = sf::seconds(0.2f);
					sf::Time wait_time3 = sf::seconds(0.2f);
					bool removed = false;
					bool change_text = false;
					bool go_next = false;

					Action new_text;
					new_text.thread_id = 1;

					new_text.action = get_action([this, text_box, &npc, wait_time1, wait_time2, wait_time3, removed, go_next](sf::Time dt) mutable
					{
						wait_time1 -= dt;

						if (GameApp::event.type == sf::Event::KeyPressed && GameApp::event.key.code == sf::Keyboard::Z)
						{
							
							if (npc.isTalking() && wait_time1 <= sf::Time::Zero && removed == false && text_box->isNext() == true && text_box->isDisplaying() == false)
							{
								go_next = true;

							}
							else if (npc.isTalking() && wait_time1 <= sf::Time::Zero && removed == false && text_box->isNext() == false)
							{
								removed = true;
							}
						}

						if (go_next)
						{
							wait_time3 -= dt;

							if (wait_time3 <= sf::Time::Zero)
							{
								text_box->next();
								wait_time3 = sf::seconds(0.2f);
								go_next = false;
							}
						}

						if (removed)
						{
							wait_time2 -= dt;

							if (wait_time2 <= sf::Time::Zero)
							{
								text_box->removeFromScene();
								player.enable();
								npc.setTalking(false);
								return false;
							}
						}


						if (npc.isTalking() == false)
						{
							player.disable();
							text_box->setText(npc.getText());
							text_box->setFont("fonts/Joystix.ttf");
							text_box->init(World::camera.getCenter());
							text_box->setDisplay(true);

							World::current_level->addActorWithoutSprite(text_box, 2);
							npc.displayText();
							npc.setTalking(true);
						}

						return true;
					});

					text_sistem.pushTextBox(new_text);
				}
			}
		}

		

		//Weapon collision
		if (m_player.getWeapon()->getGlobalRect().intersects(npc.getCollisionRect()) == true)
		{
			if (npc.isInvincible() == false)
			{
				npc.recieveDamage(1, 3.f);

				Action force;
				force.thread_id = 2;
				float max_displacement = 50;
				Direction direction = m_player.getOrientation();
				force.action = get_action([&npc, max_displacement, direction](sf::Time dt) mutable
				{
					if (direction == Direction::Right)
					{
						npc.applyForce(sf::Vector2f(100.f, 0.f), dt);
						max_displacement -= modulus(100.f * dt.asSeconds(), 0.f);
					}
					else if (direction == Direction::Left)
					{
						npc.applyForce(sf::Vector2f(-100.f, 0.f), dt);
						max_displacement -= modulus(100.f * dt.asSeconds(), 0.f);
					}
					else if (direction == Direction::Up)
					{
						npc.applyForce(sf::Vector2f(0.f, -100.f), dt);
						max_displacement -= modulus(0.f, 100.f * dt.asSeconds());
					}

					else if (direction == Direction::Down)
					{
						npc.applyForce(sf::Vector2f(0.f, 100.f), dt);
						max_displacement -= modulus(0.f, 100.f * dt.asSeconds());
					}

					if (max_displacement > 0) return true;
	
					return false;
				});
				npc.pushAction(force);

				
				if (npc.isDead())
				{
					std::unique_ptr<Image> die_explosion(new Image());
					die_explosion->setTexture(World::current_level->getTG().get(201));
					die_explosion->addAnimationFrames(0, "H", "OneLoop", 10, 0, 30, 30);
					die_explosion->desactivate();
					die_explosion->setPosition(sf::Vector2f(0.f, 0.f));
					npc.setExplosion(die_explosion.get());
					npc.addChild(std::move(die_explosion));
					
					Action smoke;
					smoke.thread_id = 1;
					smoke.action = get_action([&npc](sf::Time dt) mutable
					{
						npc.runExplosion();
						
						if (npc.isExplosionEnd())
						{
							npc.removeFromScene();
							return false;
						}

						return true;
					});

					
					npc.pushAction(smoke);

				}
				
			}
		}
		
	
	});

	player_warp.action = get_function_collision<Hero, Warp>([this](Hero &hero, Warp &warp)
	{
		if (hero.getCollisionRect().intersects(warp.getGlobalRect()) == true)
		{
			hero.setPosition(warp.getDestiny());
			world.setFirstAnimation(warp.getFirstAnimation());
			std::cout << "First animation " << warp.getFirstAnimation() << std::endl;
			World::is_new_level = true;
			World::level_script_name = warp.getLevelScriptName();
		}
	});


	//REGISTER COMMANDS
	interactions[events[CollisionEvent::PlayerNpc]] = player_npc;
	interactions[events[CollisionEvent::PlayerWarp]] = player_warp;
	//interactions[events[CollisionEvent::SwordNpc]] = sword_enemy;
}

//Iterate trough all pairs avoiding repeated pairs
//It's not posible to add Actors in the interactions because the vector loop it's modified in the loop causing a stackoverflow
void Collider::checkSceneCollision(std::vector<SceneNode*> &nodes)
{
	
	//nodes.resize(nodes.size());
	//if (!nodes.empty())
	//{
	//std::cout << "size " << nodes.size() << std::endl;
		std::vector<SceneNode*>::iterator first_itr = nodes.begin();
		std::vector<SceneNode*>::iterator second_itr = first_itr;
		second_itr++;

		while (second_itr != nodes.end())
		{
			for (std::vector<SceneNode*>::iterator itr = second_itr; itr != nodes.end(); ++itr)
			{
				
				if (*(first_itr) != nullptr && *(itr) != nullptr)
				if ((*(first_itr))->getCategory() != Category::Other && (*(itr))->getCategory() != Category::Other)
				checkCollision(**first_itr, **itr);
			}
			second_itr++;
			first_itr++;
		}
	//}
}





