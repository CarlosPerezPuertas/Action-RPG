#pragma once


#include "MoveableObject.h"
#include "ActionTree.h"

#include "ScreenAffectors.h"
#include "Weapon.h"


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
		inline bool isAnimationEnd(){ return animation.isEndLoop(); } //UniqueLoop
		bool isOtherAnimation(const int state){ return state != animation.getState(); }
		void changeAnimation(const int state);
		inline int getTextureType(){return texture_id;}
		sf::Vector2f getFrameCenter() { return animation.getFrameCenter(); }
		void pushAction(Action &action){ action_tree.push(action); }
		ActionTree& getActionQueue(){ return action_tree; }
		Weapon* getWeapon(){ return current_weapon; }
		void addWeapon(WeaponType weapon_type, sf::Vector2f rect_size, float attack_delay, float attack_time, int damage);

		void attack();
		void recieveDamage(float seconds);
		inline bool isInvincible(){ return is_invincible; }
		void setAttack(bool attack){ is_attacking = attack; }
		bool isAttack(){ return is_attacking; }
	
		//Scripts
		void moveRight(int px);
		void moveLeft(int px);
		void moveDown(int px);
		void moveUp(int px);

		void setPosition(sf::Vector2f pos);
		void setPosition(float x, float y);
		void scale(sf::Vector2f factor);
		void scale(float x, float y);
		void setCollisionRect(float x, float y, float w, float h);
		void addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height);
		void setAnimationVelocity(float speed);
		void initAnimation(const int state);

	private:
		ga::Animation animation;
		ActionTree action_tree;
		sf::Time time_invincible;
		FadeAffector fade;
		Weapon *current_weapon;
		int texture_id;
		bool is_invincible;
		bool is_attacking;


};
