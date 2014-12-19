#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <functional>
//#include "ResourceTypes.h"
//#include "Resources.h"

class Effect;


class Affector
{
	public:
		typedef std::function<void(Effect&, sf::Time)> MainAffector;

	public:
		virtual ~Affector(){}
		std::function<void(Effect&, sf::Time)> get(){ return Affector::affector; }
		virtual void init(Effect &effect) = 0;
		

	protected:
		MainAffector affector;	
};



