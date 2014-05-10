#include "..\header\LuaScripting.h"
#include "..\header\World.h"

static int hola(lua_State *L){ return 1; }

LuaScripting::LuaScripting()
{
	lua = lua_open();
	luaL_openlibs(lua);
	tolua_open(lua);
	tolua_Level_open(lua);
	tolua_Npc_open(lua);
	tolua_Map_open(lua);
	tolua_Hero_open(lua);

	//CONSTANT FROM ENUMS BINDINGS
	lua_pushnumber(lua, 0);
	lua_setglobal(lua, "GHOST_BLINKY");
	lua_pushnumber(lua, 1);
	lua_setglobal(lua, "GHOST_PINKY");
	lua_pushnumber(lua, 2);
	lua_setglobal(lua, "GHOST_INKY");
	lua_pushnumber(lua, 3);
	lua_setglobal(lua, "GHOST_CLYDE");


	lua_pushnumber(lua, static_cast<int>(Animations::GoLeft));
	lua_setglobal(lua, "A_PACMAN_GOLEFT");
	lua_pushnumber(lua, static_cast<int>(Animations::GoRight));
	lua_setglobal(lua, "A_PACMAN_GORIGHT");
	lua_pushnumber(lua, static_cast<int>(Animations::GoUp));
	lua_setglobal(lua, "A_PACMAN_GOUP");
	lua_pushnumber(lua, static_cast<int>(Animations::GoDown));
	lua_setglobal(lua, "A_PACMAN_GODOWN");
	lua_pushnumber(lua, static_cast<int>(Animations::Die));
	lua_setglobal(lua, "A_PACMAN_DIE");

	
	//FUNCTION BINDINGS
	lua_pushcfunction(lua, &World::setViewTarget);
	lua_setglobal(lua, "setViewTarget");
	lua_pushcfunction(lua, &World::setLevel);
	lua_setglobal(lua, "setLevel");
	
}


LuaScripting::~LuaScripting()
{
}

/*Level* LuaScripting::loadLevelFromScript(std::string filename)
{
	if (luaL_loadfile(lua, filename.c_str())) std::cout << "Failled script loading" << std::endl;
	lua_call(lua, 0, 1);  // calling a function that returns an Object

	

	lua_getglobal(lua, "level01");
	
	
	Level *level = static_cast<Level*>(tolua_touserdata(lua, -1, NULL));
	return level;
}*/

bool LuaScripting::loadScript(std::string filename)
{
	if (luaL_loadfile(lua, filename.c_str())) { std::cout << "Failled script loading" << std::endl; return false; }
	lua_call(lua, 0, 1);  // calling a function that returns an Object

	return true;

}

bool LuaScripting::callLuaFunction(std::string filename)
{
	return true;
}


bool LuaScripting::removeScript(std::string filename)
{
	

	return true;

}




