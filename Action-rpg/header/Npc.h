#pragma once

#include "MoveableObject.h"
#include "ActionQueue.h"



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

	void updateAnimation(sf::Time dt){ animation.update(dt); }
	void changeAnimation(int anim){ animation.changeState(anim); }
	void discardOppositeDirection();
	void restart();

	bool selectRightDirection();
	bool selectLeftDirection();
	bool selectUpDirection();
	bool selectDownDirection();

	inline void setTalking(bool x){ is_talking = x; }
	inline void popActionQueue() { action_queue.pop(); }

	//#####SCRIPTS#####

	//Standard functions
	void setPosition(float x, float y);
	void scale(float x, float y);
	void addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height);
	void setText(std::string c_text);
	void displayText();

	//Actions
	void moveRight(int px);
	void moveLeft(int px);
	void moveDown(int px);
	void moveUp(int px);

	//Conditions for quest system
	bool isTalking();
	
private:
	ga::Animation animation;
	ActionQueue<Npc> action_queue;
	int texture_id;


	//script
	bool is_talking;
	std::string text;
	
};

