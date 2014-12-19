#pragma once

#include "StaticObject.h"
#include "Animation.h"
#include "Map.h"

//class Map;

class Door : public StaticObject
{
public:
	Door(const TMX_Door &tiled_data, const unsigned int c_open_animation_id, const unsigned int c_close_animation_id);
	~Door();

	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void updateCurrent(CommandQueue &command_queue, const sf::Time dt);
	virtual unsigned int getCategory() const;
	Door& getObject(){  return *this; }

	void open();
	void close();
	void initClosed(){is_colliding = true; changeAnimation(open_animation_id);}
	void initOpened(){ is_colliding = false; changeAnimation(close_animation_id);}
	bool isClosed();

	bool isState();
	void loadState();


private:
	unsigned int open_animation_id;
	unsigned int close_animation_id;
	static std::set<std::pair<std::string, bool>> states; // We make static the logic 

};

