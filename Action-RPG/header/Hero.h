#pragma once


#include "MoveableObject.h"
#include "ActionQueue.h"


class Hero : public MoveableObject
{
	public:
		Hero(int texture_id);
		virtual ~Hero(){ std::cout << "Hero deleted " << std::endl; }

		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
		virtual unsigned int getCategory() const;

		inline void playAnimation(){ animation.play(); }
		inline void stopAnimation(){ animation.reset();  animation.stop(); }
		inline bool isAnimating(){ return animation.isPlaying(); }
		bool isOtherAnimation(const int state){ return state != animation.getState(); }
		void changeAnimation(const int state);

		inline int getTextureType(){return texture_id;}

	
		//Scripts
		void moveRight(int px);
		void moveLeft(int px);
		void moveDown(int px);
		void moveUp(int px);

		
		void setPosition(sf::Vector2f pos);
		void setPosition(float x, float y);
		void scale(sf::Vector2f factor);
		void scale(float x, float y);
		void addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height);
		void setAnimationVelocity(float speed);

	private:
		ga::Animation animation;
		ActionQueue<Hero> action_queue;
		int texture_id;


	
};
