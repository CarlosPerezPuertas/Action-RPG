#pragma once

#include "SceneNode.h"
#include "Animation.h"
#include "ActionTree.h"

//Drawable entities
class Entity : public SceneNode
{
	public:
		Entity() : animation(sprite, sf::seconds(0.08f), 0), action_tree(3){}
		Entity(sf::Texture &texture);
		virtual ~Entity();
		const Entity* getObject(){ return this; }

		sf::FloatRect getLocalRect();
		sf::FloatRect getGlobalRect();
		sf::Vector2f getCenter();
		sf::Vector2f getColisionCenter();
		void setOrigin(sf::Vector2f pos);
		inline void setTexture(sf::Texture &texture){ sprite.setTexture(texture); }
		
		inline sf::Vector2f getInitPos(){ return initial_pos; }
		inline void setInitPos(sf::Vector2f pos){ initial_pos = pos; }
		inline void restartPosition(){ setPosition(initial_pos);}
		
		void setCollisionRect(sf::FloatRect c_col_rect);
		inline sf::FloatRect getCollisionRect(){ return getWorldTransform().transformRect(collision_rect.getGlobalBounds()); }
		sf::FloatRect getCollisionRectExt();
		void setCollision(bool x) { is_colliding = x; }
		sf::FloatRect getLeftSensor();
		sf::FloatRect getRightSensor();
		sf::FloatRect getUpSensor();
		sf::FloatRect getDownSensor();


		inline void playAnimation(){ animation.play(); }
		inline void stopAnimation(){ animation.reset();  animation.stop(); }
		inline bool isAnimating(){ return animation.isPlaying(); }
		inline bool isAnimationEnd(){ return animation.isEndLoop(); } //UniqueLoop
		bool isOtherAnimation(const int state){ return state != animation.getState(); }
		void changeAnimation(int anim){ animation.changeState(anim); }
		inline int getTextureType(){ return texture_id; }
		sf::Vector2f getFrameCenter() { return animation.getFrameCenter(); }
		inline ga::Animation getAnimation(){ return animation; }
		void updateAnimation(sf::Time dt){ animation.update(dt); }
		inline int getAnimationState() { return animation.getState(); }

		void pushAction(Action &action){ action_tree.push(action); }
		ActionTree& getActionQueue(){ return action_tree; }

		void setPosition(sf::Vector2f pos);
		void setPosition(float x, float y);
		void scale(sf::Vector2f factor);
		void scale(float x, float y);
		void setAnimationVelocity(float speed);
		void initAnimation(const int state);
		void addAnimationFrames(int anim_type, std::string distribution, std::string loop_type, int num_frames, int position, int width, int height);
		void setCollisionRect(float x, float y, float w, float h);



		
	protected:
		sf::Sprite  sprite;
		sf::Vector2f  initial_pos;
		sf::RectangleShape collision_rect;
		sf::RectangleShape up_sensor_rect;
		sf::RectangleShape down_sensor_rect;
		sf::RectangleShape left_sensor_rect;
		sf::RectangleShape right_sensor_rect;

		bool is_colliding;	

		ga::Animation animation;
		ActionTree action_tree;
		int texture_id;
};

