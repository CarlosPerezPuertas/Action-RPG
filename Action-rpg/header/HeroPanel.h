#pragma once

#include "Text.h"
#include "ImageContainer.h"
#include "ImageContainer.h"

class HeroPanel : public SceneNode
{
	public:
		HeroPanel(TextureGenerator &c_tg);
		~HeroPanel();

		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

		inline virtual unsigned int getCategory() const { return Category::HeroPanel; }

		void initPosition();
		void setLifes(int num);



	private:
		TextureGenerator &tg;
		ImageContainer *lifes;
};

