#pragma once

#include "MoveableObject.h"

#include "ScreenAffectors.h"
#include "Image.h"
#include "Weapon.h"

class Enemy : public MoveableObject
{
public:
	Enemy(int c_texture_id);
	virtual ~Enemy();

	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void updateCurrent(CommandQueue &command_queue, const sf::Time df);
	virtual unsigned int getCategory() const;
	const Enemy* getObject(){ return this; }

	void discardOppositeDirection();
	void restart();

	bool selectRightDirection();
	bool selectLeftDirection();
	bool selectUpDirection();
	bool selectDownDirection();

	inline void setTalking(bool x){ is_talking = x; }
	std::string getText();
	void recieveDamage(int damage, float seconds);
	void setAttack(bool attack){ is_attacking = attack; }
	bool isAttack(){ return is_attacking; }
	inline bool isInvincible(){ return is_invincible; }
	inline bool isDead(){ if (life > 0)return false; return true; }
	inline void setExplosion(Image *image){ die_explosion_effect = image; }
	inline bool isExplosionEnd(){ assert(die_explosion_effect != nullptr);  return die_explosion_effect->isAnimationEnd(); }
	inline void runExplosion(){ assert(die_explosion_effect != nullptr); die_explosion_effect->activate();  die_explosion_effect->play(); }
	void addWeapon(WeaponType weapon_type, sf::Vector2f rect_size, float attack_delay, float attack_time, int damage);

	//Artificial inteligence
	void chase(sf::Vector2f pos);
	void patrol();
	void attack(float attack_delay, float attack_time, int damage);

	//#####SCRIPTS#####
	//Standard functions
	void setText(std::string c_text);
	void displayText();

	//Actions
	void moveRight(int px);
	void moveLeft(int px);
	void moveDown(int px);
	void moveUp(int px);
	void wait(sf::Time w_time);
	void die();


	//Conditions for quest system
	bool isTalking();

private:
	bool is_attacking;
	Image *die_explosion_effect;
	Weapon *current_weapon;


	FadeAffector fade;
	bool is_invincible;
	sf::Time time_invincible;
	int life;


	//script
	bool is_talking;
	std::string text;
	sf::Time stop_time; //Time doing nothing

};
