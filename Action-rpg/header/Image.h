#pragma once

#include "SceneNode.h"
#include "Animation.h"

class Image : public SceneNode
{
	public:
		Image(const int type, const TextureGenerator &tg);
		Image();

		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		
		sf::FloatRect getRect() { return getWorldTransform().transformRect(sprite.getGlobalBounds()); }
		void moveDuring(sf::Vector2f c_displacement, float seconds);
		void setTexture(sf::Texture &texture){ sprite.setTexture(texture); }
		void updateAnimation(sf::Time dt){ animation.update(dt); }
		void addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height);
		inline void play(){ animation.play(); }
		inline void stop(){ animation.stop(); }
		inline bool isAnimationEnd(){ return animation.isEndLoop(); }

	private:
		sf::Sprite sprite;
		bool has_movement;
		bool is_animated;
		ga::Animation animation;
		sf::Vector2f displacement;
		sf::Time movement_time;

};

