/*
** Lua binding: Map
** Generated automatically by tolua++-1.0.92 on 04/24/14 17:12:21.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Map_open (lua_State* tolua_S);

#include "..\header\Map.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Map (lua_State* tolua_S)
{
 Map* self = (Map*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Map");
}

/* method: new of class  Map */
#ifndef TOLUA_DISABLE_tolua_Map_Map_new00
static int tolua_Map_Map_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Map",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Map* tolua_ret = (Map*)  Mtolua_new((Map)(filename));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Map");
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Map */
#ifndef TOLUA_DISABLE_tolua_Map_Map_new00_local
static int tolua_Map_Map_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Map",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Map* tolua_ret = (Map*)  Mtolua_new((Map)(filename));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Map");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Map_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Map","Map","",tolua_collect_Map);
  #else
  tolua_cclass(tolua_S,"Map","Map","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Map");
   tolua_function(tolua_S,"new",tolua_Map_Map_new00);
   tolua_function(tolua_S,"new_local",tolua_Map_Map_new00_local);
   tolua_function(tolua_S,".call",tolua_Map_Map_new00_local);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Map (lua_State* tolua_S) {
 return tolua_Map_open(tolua_S);
};
#endif

