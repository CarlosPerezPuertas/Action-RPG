#pragma once

#include <iostream>
#include <string>

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
#include "tolua_Level.h"
#include "tolua_Npc.h"
#include "tolua_Map.h"
#include "tolua_Hero.h"


class Level;

class LuaScripting
{
	public:
		LuaScripting();
		~LuaScripting();

		//template<typename DataType>
		/*DataType* bindData(DataType *data)
		{
			lua_call(lua, 0, 0);  // calling a function that returns an Object
			if (luaL_loadfile(lua, "scripts/level01.lua")) std::cout << "Failled script loading" << std::endl;
			DataType *lua_object = (DataType*)(lua_touserdata(lua, -1));
			return lua_object;
		}*/

		bool loadScript(std::string filename);
		lua_State* getLuaState(){ return lua; }

	private:
		lua_State *lua;
};

