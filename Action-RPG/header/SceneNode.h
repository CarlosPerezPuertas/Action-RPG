#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <typeinfo>
#include <functional>
#include <chrono>
#include <random>
#include <memory>
#include <tolua++.h>

#include "Command.h"
#include "CommandQueue.h"
#include "Resources.h"
#include "ResourceTypes.h"


class Door;


namespace Category
{
	enum Type
	{
		Other,
		Player,
		Npc,
		Enemy,
		Warp,
		Text,
		HeroPanel,
		LifeContainer,
		ScreenEffect, 
		EntityEffect,
		Sword,
		Door
	};
}

enum class Direction
{
	None,
	Left,
	Right,
	Up,
	Down
};




class SceneNode : public sf::Drawable, public sf::Transformable,  private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> PtrNode;

	public:
		SceneNode();
		virtual ~SceneNode();

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;
		//const SceneNode* getObject(){ return this; }


		void update(CommandQueue &command_queue, const sf::Time df);
		virtual void updateCurrent(CommandQueue &command_queue, const sf::Time df);
		void updateChildren(CommandQueue &command_queue, const sf::Time df);

		void addChild(PtrNode child);
		void deleteChild(SceneNode &node);
		void recieveCommand(Command &command, const sf::Time df);

		void removeFromScene();
		void deleteRemovable(std::vector<SceneNode*> &scene_vector);
		inline bool isRemovable(){ return delete_from_scene == true; }

		inline void activate(){ active = true; }
		inline void desactivate(){ active = false; }
		inline void desactivate(const float seconds){ active = false; time_disabled = sf::seconds(seconds); isTemporalDisabled = true; }
		inline const bool isActive() const { return active; }
		inline void activateAll(){ activate(); for (auto &itr : children) itr->activateAll(); }
		inline void setLifeTime(const float seconds){ hasLifetime = true; lifetime = sf::seconds(seconds); lifetime_elapsed = lifetime; }
	

		template <typename T>
		T* getNode(std::string c_key)
		{
			SceneNode *aux_node = nullptr;
			findNode(c_key, aux_node);
			assert(aux_node != nullptr);
			return static_cast<T*>(aux_node);
		}

	
		/*bool isNode(std::string c_key)
		{
			bool aux_node = false;
			findNode(c_key, aux_node);
			return aux_node;
		}*/

		void findNode(std::string c_key, SceneNode *&aux);
		//void findNode(std::string c_key, bool &aux);
	

	
		virtual unsigned int getCategory() const;
		sf::Transform getWorldTransform();

		void makeGlobal();
		void deleteNonGlobal();

		inline std::string getKey(){ return key; }
		inline void setKey(std::string c_key){ key = c_key; }
		inline unsigned int size()
		{
			return num_nodes;
		}
		 
	protected:
		sf::Time lifetime;
		sf::Time lifetime_elapsed;
		bool hasLifetime;

		sf::Time time_disabled;
		bool isTemporalDisabled;
		bool is_global;
		std::string key;
		unsigned int num_nodes;

	private:
		SceneNode* parent;
		SceneNode* root;
		std::vector<PtrNode> children;	
		bool delete_from_scene;
		bool active;		
};

