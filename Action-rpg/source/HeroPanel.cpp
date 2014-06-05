#include "..\header\HeroPanel.h"
#include "..\header\World.h"


HeroPanel::HeroPanel(TextureGenerator &c_tg)
: lifes(nullptr)
, tg(c_tg)
{
	std::unique_ptr<ImageContainer> icl(new ImageContainer(ContainerType::Lifes));
	lifes = icl.get();
	this->addChild(std::move(icl));

	std::cout << "Created hero panel" << std::endl;
}


HeroPanel::~HeroPanel()
{
	std::cout << "Deleted hero panel" << std::endl;
}

void HeroPanel::updateCurrent(CommandQueue &command_queue, const sf::Time dt)
{
	if (hasLifetime == true)
	{
		lifetime_elapsed -= dt;

		if (lifetime_elapsed <= sf::Time::Zero)
		{
			hasLifetime = false;
			removeFromScene();
		}
	}

	initPosition();

}

void HeroPanel::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*lifes, states);
}

void HeroPanel::initPosition()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	float x = World::camera.getCenter().x + 600.f - 200.f;
	float y = World::camera.getCenter().y - desktop.height / 2.f + 100.f;

	setPosition(x, y);
}



void HeroPanel::setLifes(int num)
{
	if (num > 0)
	for (int i = 0; i < num; i++)
	{
		lifes->pushBack(102, tg);
	}
	else if (num < 0)
	{
		num = abs(num);

		for (int i = 0; i < num; i++)
		{
			if (!lifes->isEmpty()) lifes->popBack();
		}
	}
}



