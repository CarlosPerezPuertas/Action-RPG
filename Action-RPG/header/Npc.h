#pragma once

#include "MoveableObject.h"
#include "ScreenAffectors.h"
#include "Image.h"
#include "Weapon.h"

class Npc : public MoveableObject
{
public:
	Npc(int c_texture_id);
	virtual ~Npc();

	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void updateCurrent(CommandQueue &command_queue, const sf::Time df);
	virtual unsigned int getCategory() const;
	const Npc* getObject(){ return this; }

	void discardOppositeDirection();
	void restart();

	bool selectRightDirection();
	bool selectLeftDirection();
	bool selectUpDirection();
	bool selectDownDirection();

	inline void setTalking(bool x){ is_talking = x; }
	std::string getText();

	
	//Artificial inteligence
	void follow(sf::Vector2f pos);
	void walk();

	//#####SCRIPTS#####
	//Standard functions
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
	FadeAffector fade;

	//script
	bool is_talking;
	std::string text;
	sf::Time stop_time; //Time doing nothing
	
};

