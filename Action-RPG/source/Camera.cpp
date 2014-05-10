#include "..\header\Camera.h"

#include "..\header\CommandQueue.h"
#include "..\header\Level.h"
#include "..\header\SceneNode.h"
#include "..\header\Hero.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update(CommandQueue &command_queue, sf::Time dt, Level &level, sf::RenderWindow &window)
{

	Command update_camera;
	update_camera.category = Category::Player;
	update_camera.action = get_function<Hero>([this, &level, &window](Hero &m_player, sf::Time dt)
	{
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		Map *map = level.getMap().get();
		float map_width_max = map->getWidth() - desktop.width / 2;
		float map_height_max = map->getHeight() - desktop.height / 2;

		//std::cout << map_width_max << " " << m_player.getPosition().x << "   " << map_height_max  << " " << m_player.getPosition().y << std::endl;

		if (desktop.width < map->getWidth() && desktop.height < map->getHeight())
		{
			//Central rectangle
			if (desktop.width / 2.f <= m_player.getPosition().x && desktop.height / 2.f <= m_player.getPosition().y &&
				map_width_max >= m_player.getPosition().x && map_height_max >= m_player.getPosition().y)
			{
				setCenter(m_player.getPosition().x, m_player.getPosition().y);
			}
			else
			{
				//The four rectangle corners
				if (desktop.width / 2.f > m_player.getPosition().x && desktop.height / 2.f > m_player.getPosition().y) setCenter(desktop.width / 2.f, desktop.height / 2.f);
				else if (map_width_max < m_player.getPosition().x && desktop.height / 2.f > m_player.getPosition().y) setCenter(map_width_max, desktop.height / 2.f);
				else if (map_width_max < m_player.getPosition().x && map_height_max < m_player.getPosition().y) setCenter(map_width_max, map_height_max);
				else if (desktop.width / 2.f > m_player.getPosition().x && map_height_max < m_player.getPosition().y) setCenter(desktop.width / 2.f, map_height_max);

				//Four edge rectangles
				else if (desktop.width / 2.f > m_player.getPosition().x) setCenter(desktop.width / 2.f, m_player.getPosition().y);
				else if (desktop.height / 2.f > m_player.getPosition().y) setCenter(m_player.getPosition().x, desktop.height / 2.f);
				else if (map_width_max < m_player.getPosition().x) setCenter(map_width_max, m_player.getPosition().y);
				else if (map_height_max < m_player.getPosition().y) setCenter(m_player.getPosition().x, map_height_max);
			}
		}
		else if (desktop.width > map->getWidth() && desktop.height > map->getHeight())
		{
			setCenter(map->getWidth() / 2.f, map->getHeight() / 2);
		}
		else if (desktop.width > map->getWidth())
		{
			if (desktop.height / 2.f <= m_player.getPosition().y && map_height_max >= m_player.getPosition().y) setCenter(map->getWidth() / 2.f, m_player.getPosition().y);
			else if (desktop.height / 2.f > m_player.getPosition().y) setCenter(map->getWidth() / 2.f, desktop.height / 2.f);
			else if (map_height_max < m_player.getPosition().y) setCenter(map->getWidth() / 2.f, map_height_max);
		}
		else if (desktop.height > map->getHeight())
		{
			if (desktop.width / 2.f <= m_player.getPosition().x && map_width_max >= m_player.getPosition().x) setCenter(m_player.getPosition().x, map->getHeight() / 2.f);
			else if (desktop.width / 2.f > m_player.getPosition().x) setCenter(desktop.width / 2.f, map->getHeight() / 2.f);
			else if (map_width_max < m_player.getPosition().x) setCenter(map_width_max, map->getHeight() / 2.f);
		}

		setSize(sf::Vector2f(static_cast<float>(desktop.width), static_cast<float>(desktop.height)));
		window.setView(*this);

	});
	command_queue.push(update_camera);

}


void Camera::setTarget(const SceneNode &target, Map &map)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	float map_width_max = map.getWidth()  - desktop.width / 2.f;
	float map_height_max = map.getHeight()  - desktop.height / 2.f;

	if (desktop.width < map.getWidth() && desktop.height < map.getHeight())
	{
		//Central rectangle
		if (desktop.width / 2.f <= target.getPosition().x && desktop.height / 2.f <= target.getPosition().y &&
			map_width_max >= target.getPosition().x && map_height_max >= target.getPosition().y)
		{
			setCenter(target.getPosition().x, target.getPosition().y);
		}
		else
		{
			//The four rectangle corners
			if (desktop.width / 2.f > target.getPosition().x && desktop.height / 2.f > target.getPosition().y) setCenter(desktop.width / 2.f, desktop.height / 2.f);
			else if (map_width_max < target.getPosition().x && desktop.height / 2.f > target.getPosition().y) setCenter(map_width_max, desktop.height / 2.f);
			else if (map_width_max < target.getPosition().x && map_height_max < target.getPosition().y) setCenter(map_width_max, map_height_max);
			else if (desktop.width / 2.f > target.getPosition().x && map_height_max < target.getPosition().y) setCenter(desktop.width / 2.f, map_height_max);

			//Four edge rectangles
			else if (desktop.width / 2.f > target.getPosition().x) setCenter(desktop.width / 2.f, target.getPosition().y);
			else if (desktop.height / 2.f > target.getPosition().y) setCenter(target.getPosition().x, desktop.height / 2.f);
			else if (map_width_max < target.getPosition().x) setCenter(map_width_max, target.getPosition().y);
			else if (map_height_max < target.getPosition().y) setCenter(target.getPosition().x, map_height_max);
		}
	}
	else if (desktop.width > map.getWidth() && desktop.height > map.getHeight())
	{
		setCenter(map.getWidth() / 2.f, map.getHeight() / 2.f);
	}
	else if (desktop.width > map.getWidth())
	{
		if (desktop.height / 2.f <= target.getPosition().y && map_height_max >= target.getPosition().y) setCenter(map.getWidth() / 2.f, target.getPosition().y);
		else if (desktop.height / 2.f > target.getPosition().y) setCenter(map.getWidth() / 2.f, desktop.height / 2.f);
		else if (map_height_max < target.getPosition().y) setCenter(map.getWidth() / 2, map_height_max);
	}
	else if (desktop.height > map.getHeight())
	{

		if (desktop.width / 2.f <= target.getPosition().x && map_width_max >= target.getPosition().x) setCenter(target.getPosition().x, map.getHeight() / 2.f);
		else if (desktop.width / 2.f > target.getPosition().x) setCenter(desktop.width / 2.f, map.getHeight() / 2.f);
		else if (map_width_max < target.getPosition().x) setCenter(map_width_max, map.getHeight() / 2.f);
	}

	setSize(sf::Vector2f(static_cast<float>(desktop.width), static_cast<float>(desktop.height)));
}

