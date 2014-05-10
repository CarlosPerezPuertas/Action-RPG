#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <chrono>
#include <memory>
#include <tolua++.h>

#include "Command.h"
#include "CommandQueue.h"
#include "Resources.h"
#include "ResourceTypes.h"

namespace Category
{
	enum Type
	{
		Other,
		Player,
		Npc,
		Warp,
		Text
	};
}



class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> PtrNode;

	public:
		SceneNode();
		virtual ~SceneNode();

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

		void update(CommandQueue &command_queue, const sf::Time df);
		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time df);
		void updateChildren(CommandQueue &command_queue, const sf::Time df);

		void addChild(PtrNode child);
		void deleteChild(SceneNode &node);
		void recieveCommand(Command &command, const sf::Time df);

		void removeFromScene();
		void removeFromSceneNow();
		void deleteRemovable(std::vector<SceneNode*> &scene_vector);
		void release();
		inline bool isRemovable(){ return delete_from_scene == true; }

		inline void activate(){ active = true; }
		inline void desactivate(){ active = false; }
		inline void desactivate(const float seconds){ active = false; time_disabled = sf::seconds(seconds); isTemporalDisabled = true; }
		inline const bool isActive() const { return active; }
		inline void activateAll(){ activate(); for (auto &itr : children) itr->activateAll(); }
		inline void setLifeTime(const float seconds){ hasLifetime = true; lifetime = sf::seconds(seconds); lifetime_elapsed = lifetime; }
			
		
		virtual unsigned int getCategory() const;
		sf::Transform getWorldTransform();

		void makeGlobal();
		void deleteNonGlobal();
		 
	protected:
		sf::Time lifetime;
		sf::Time lifetime_elapsed;
		bool hasLifetime;

		sf::Time time_disabled;
		bool isTemporalDisabled;
		bool is_global;

	private:
		SceneNode* parent;
		std::vector<PtrNode> children;	
		bool delete_from_scene;
		bool active;
		
		
};

