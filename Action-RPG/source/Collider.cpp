#include "..\header\Collider.h"

#include "..\header\World.h"
#include "..\header\Player.h"
#include "..\header\Hero.h"
#include "..\header\Npc.h"
#include "..\header\Warp.h"




Collider::Collider(World &c_world, CommandQueue &c_command_queue, Player &c_player, LuaScripting &c_script_system)
: world(c_world)
, command_queue(c_command_queue)
, player(c_player)
, script_system(c_script_system)
, map(nullptr)
{
	//REGISTER EVENT MAP
	events[CollisionEvent::PlayerNpc] = std::make_pair(Category::Player, Category::Npc);
	events[CollisionEvent::PlayerWarp] = std::make_pair(Category::Player, Category::Warp);
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
	
	//Register actions
	player_npc.action = get_function_collision<Hero, Npc>([this](Hero &m_player, Npc &npc)
	{
		npc.setTalking(false);
		
		if (m_player.getInteriorRectMinus().intersects(npc.getInteriorRect()) == true )
		{
			m_player.setCollision(true);

			//Depending on the direction of the collision correct the position until the collision finishes
			Direction dir = m_player.getCurrentDirection();
			bool bounce = false;

			while (m_player.getInteriorRect().intersects(npc.getInteriorRect()) == true && dir != Direction::None)
			{
				bounce = true;
				
				if (dir == Direction::Left) { m_player.move(sf::Vector2f(1.f, 0.f)); m_player.setCollisionDirection(Direction::Left); }
				else if (dir == Direction::Right) { m_player.move(sf::Vector2f(-1.f, 0.f));  m_player.setCollisionDirection(Direction::Right); }
				else if (dir == Direction::Down) { m_player.move(sf::Vector2f(0.f, -1.f));  m_player.setCollisionDirection(Direction::Down); }
				else if (dir == Direction::Up) { m_player.move(sf::Vector2f(0.f, 1.f));  m_player.setCollisionDirection(Direction::Up); }
			}

			if (bounce) { m_player.stopAnimation(); }
			//m_player.setCurrentDirection(Direction::None);

			//NPC talks
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && m_player.getCollisionDirection() == m_player.getOrientation())
			{
				npc.setTalking(true);
				npc.displayText();
			}	
		}
	});

	player_warp.action = get_function_collision<Hero, Warp>([this](Hero &hero, Warp &warp)
	{
		if (hero.getInteriorRect().intersects(warp.getGlobalRect()) == true)
		{
			hero.setPosition(warp.getDestiny());
			World::is_new_level = true;
		}
	});


	//REGISTER COMMANDS
	interactions[events[CollisionEvent::PlayerNpc]] = player_npc;
	interactions[events[CollisionEvent::PlayerWarp]] = player_warp;
}

//Iterate trough all pairs avoiding repeated pairs
void Collider::checkSceneCollision(std::vector<SceneNode*> &nodes)
{
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
				checkCollision(**first_itr, **itr);
			}
			second_itr++;
			first_itr++;
		}
	//}
}





