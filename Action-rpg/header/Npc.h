#pragma once

#include "MoveableObject.h"

#include "ActionTree.h"
#include "ScreenAffectors.h"
#include "Image.h"

class Npc : public MoveableObject
{
public:
	Npc(int c_texture_id);
	virtual ~Npc();

	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void updateCurrent(CommandQueue &command_queue, const sf::Time df);
	virtual unsigned int getCategory() const;

	void setPosition(sf::Vector2f pos);
	void scale(sf::Vector2f factor);
	
	inline int getAnimationState() { return animation.getState(); }
	inline ga::Animation getAnimation(){ return animation; }
	inline int getTextureType() { return texture_id; }
	sf::Vector2f getFrameCenter() { return animation.getFrameCenter(); }
	inline void playAnimation(){ animation.play(); }
	inline void stopAnimation(){ animation.reset();  animation.stop(); }
	inline bool isAnimating(){ return animation.isPlaying(); }
	inline bool isAnimationEnd(){ return animation.isEndLoop(); } //UniqueLoop

	void updateAnimation(sf::Time dt){ animation.update(dt); }
	void changeAnimation(int anim){ animation.changeState(anim); }
	void discardOppositeDirection();
	void restart();
	void pushAction(Action action){ action_tree.push(action); }

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
	
	//Artificial inteligence
	void chase(sf::Vector2f pos);

	//#####SCRIPTS#####
	//Standard functions
	void setPosition(float x, float y);
	void scale(float x, float y);
	void setCollisionRect(float x, float y, float w, float h); 
	void addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height);
	void setText(std::string c_text);
	void displayText();

	//Actions
	void moveRight(int px);
	void moveLeft(int px);
	void moveDown(int px);
	void moveUp(int px);
	void die();


	//Conditions for quest system
	bool isTalking();
	
private:
	ga::Animation animation;
	ActionTree action_tree;
	int texture_id;
	bool is_attacking;
	Image *die_explosion_effect;


	FadeAffector fade;
	bool is_invincible;
	sf::Time time_invincible;
	int life;


	//script
	bool is_talking;
	std::string text;
	
};

