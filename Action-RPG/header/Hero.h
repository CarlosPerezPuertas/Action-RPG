#pragma once


#include "MoveableObject.h"

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
		
		template <typename T>
		T& getObject(){ return *this; }
		
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
		void shit(){ std::cout << "Shit" << std::endl; }


	private:
		
		sf::Time time_invincible;
		FadeAffector fade;
		Weapon *current_weapon;
		bool is_invincible;
		bool is_attacking;


};
