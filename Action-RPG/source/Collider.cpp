#include "..\header\Collider.h"

#include "..\header\World.h"
#include "..\header\Player.h"
#include "..\header\Hero.h"
#include "..\header\Npc.h"
#include "..\header\Enemy.h"
#include "..\header\Warp.h"
#include "..\header\Door.h"
#include "..\header\TextBox.h"
#include "..\header\ActionTree.h"
#include "..\core\header\GameApp.h"
#include "..\header\Weapon.h"

template<typename NodeType1, typename NodeType2>
float distance(NodeType1 &node1, NodeType2 &node2)
{
	return modulus(node1.getCenter().x - node2.getCenter().x, node1.getCenter().y - node2.getCenter().y);
}




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
	events[CollisionEvent::PlayerEnemy] = std::make_pair(Category::Player, Category::Enemy);
	events[CollisionEvent::PlayerWarp] = std::make_pair(Category::Player, Category::Warp);
	events[CollisionEvent::PlayerDoor] = std::make_pair(Category::Player, Category::Door);
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
	CommandCollision player_enemy;
	CommandCollision player_door;

	/*sword_enemy.action = get_function_collision<Weapon, Npc>([this](Weapon &weapon, Npc &npc)
	{


	});*/

	
	//Register actions
	player_npc.action = get_function_collision<Hero, Npc>([this](Hero &m_player, Npc &npc)
	{
		
			

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
	});

	//Register actions
	player_enemy.action = get_function_collision<Hero, Enemy>([this](Hero &m_player, Enemy &enemy)
	{
		if (!enemy.isInvincible())
		{

			if (distance(enemy, m_player) < 250.f && distance(enemy, m_player) > 50.f) enemy.chase(m_player.getPosition());
			else if (distance(enemy, m_player) < 50.f) enemy.attack(1.f, 2.f, 1);
			else enemy.patrol();
		}


		if (m_player.getCollisionRectExt().intersects(enemy.getCollisionRect()) == true)
		{
			m_player.setCollision(true);
			//std::cout << "Collision" << std::endl;

			//Depending on the direction of the collision correct the position until the collision finishes
			Direction dir = m_player.getCurrentDirection();
			bool bounce = false;

			while (m_player.getCollisionRect().intersects(enemy.getCollisionRect()) == true && dir != Direction::None)
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
				if (m_player.isInvincible() == false && enemy.isInvincible() == false)
				{
					m_player.recieveDamage(2.f);

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

			if (m_player.getCollisionDirection() == m_player.getOrientation() && enemy.isTalking() == false)
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

					new_text.action = get_action([this, text_box, &enemy, wait_time1, wait_time2, wait_time3, removed, go_next](sf::Time dt) mutable
					{
						wait_time1 -= dt;

						if (GameApp::event.type == sf::Event::KeyPressed && GameApp::event.key.code == sf::Keyboard::Z)
						{

							if (enemy.isTalking() && wait_time1 <= sf::Time::Zero && removed == false && text_box->isNext() == true && text_box->isDisplaying() == false)
							{
								go_next = true;

							}
							else if (enemy.isTalking() && wait_time1 <= sf::Time::Zero && removed == false && text_box->isNext() == false)
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
								enemy.setTalking(false);
								return false;
							}
						}


						if (enemy.isTalking() == false)
						{
							player.disable();
							text_box->setText(enemy.getText());
							text_box->setFont("fonts/Joystix.ttf");
							text_box->init(World::camera.getCenter());
							text_box->setDisplay(true);

							World::current_level->addActorWithoutSprite(text_box, 2);
							enemy.displayText();
							enemy.setTalking(true);
						}

						return true;
					});

					text_sistem.pushTextBox(new_text);
				}
			}
		}



		//Weapon collision
		if (m_player.getWeapon()->getGlobalRect().intersects(enemy.getCollisionRect()) == true)
		{
			if (enemy.isInvincible() == false)
			{
				enemy.recieveDamage(1, 2.f);

				Action force;
				force.thread_id = 2;
				float max_displacement = 50;
				Direction direction = m_player.getOrientation();
				force.action = get_action([&enemy, max_displacement, direction](sf::Time dt) mutable
				{
					if (direction == Direction::Right)
					{
						enemy.applyForce(sf::Vector2f(100.f, 0.f), dt);
						max_displacement -= modulus(100.f * dt.asSeconds(), 0.f);
					}
					else if (direction == Direction::Left)
					{
						enemy.applyForce(sf::Vector2f(-100.f, 0.f), dt);
						max_displacement -= modulus(100.f * dt.asSeconds(), 0.f);
					}
					else if (direction == Direction::Up)
					{
						enemy.applyForce(sf::Vector2f(0.f, -100.f), dt);
						max_displacement -= modulus(0.f, 100.f * dt.asSeconds());
					}

					else if (direction == Direction::Down)
					{
						enemy.applyForce(sf::Vector2f(0.f, 100.f), dt);
						max_displacement -= modulus(0.f, 100.f * dt.asSeconds());
					}

					if (max_displacement > 0) return true;

					return false;
				});
				enemy.pushAction(force);


				if (enemy.isDead())
				{
					std::unique_ptr<Image> die_explosion(new Image());
					die_explosion->setTexture(World::current_level->getTG().get(201));
					die_explosion->addAnimationFrames(0, "H", "OneLoop", 10, 0, 30, 30);
					die_explosion->desactivate();
					die_explosion->setPosition(sf::Vector2f(0.f, 0.f));
					enemy.setExplosion(die_explosion.get());
					enemy.addChild(std::move(die_explosion));

					Action smoke;
					smoke.thread_id = 1;
					smoke.action = get_action([&enemy](sf::Time dt) mutable
					{
						enemy.runExplosion();

						if (enemy.isExplosionEnd())
						{
							enemy.removeFromScene();
							return false;
						}

						return true;
					});


					enemy.pushAction(smoke);

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

	player_door.action = get_function_collision<Hero, Door>([this](Hero &hero, Door &door)
	{
		if (hero.getCollisionRect().intersects(door.getCollisionRect()) == true && door.isClosed())
		{
			hero.setCollision(true);

			//Depending on the direction of the collision correct the position until the collision finishes
			Direction dir = hero.getCurrentDirection();
			bool bounce = false;

			while (hero.getCollisionRect().intersects(door.getCollisionRect()) == true && dir != Direction::None)
			{
				bounce = true;

				if (dir == Direction::Left) { hero.move(sf::Vector2f(0.5f, 0.f)); hero.setCollisionDirection(Direction::Left); }
				else if (dir == Direction::Right) { hero.move(sf::Vector2f(-0.5f, 0.f));  hero.setCollisionDirection(Direction::Right); }
				else if (dir == Direction::Down) { hero.move(sf::Vector2f(0.f, -0.5f));  hero.setCollisionDirection(Direction::Down); }
				else if (dir == Direction::Up) { hero.move(sf::Vector2f(0.f, 0.5f));  hero.setCollisionDirection(Direction::Up); }
			}

			if (bounce) hero.stopAnimation();
		}
	});


	//REGISTER COMMANDS
	interactions[events[CollisionEvent::PlayerNpc]] = player_npc;
	interactions[events[CollisionEvent::PlayerWarp]] = player_warp;
	interactions[events[CollisionEvent::PlayerEnemy]] = player_enemy;
	interactions[events[CollisionEvent::PlayerDoor]] = player_door;
	//interactions[events[CollisionEvent::SwordNpc]] = sword_enemy;
}

//Iterate trough all pairs avoiding repeated pairs
//It's not posible to add Actors in the interactions because the vector loop it's modified in the loop causing a stackoverflow
void Collider::checkSceneCollision(std::vector<SceneNode*> &nodes)
{
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
}





