/*
** Lua binding: Level
** Generated automatically by tolua++-1.0.92 on 10/17/14 17:09:10.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Level_open (lua_State* tolua_S);

#include "..\header\Level.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Level (lua_State* tolua_S)
{
 Level* self = (Level*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Hero");
 tolua_usertype(tolua_S,"Map");
 tolua_usertype(tolua_S,"Level");
 tolua_usertype(tolua_S,"Npc");
 tolua_usertype(tolua_S,"Enemy");
}

/* method: new of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_new00
static int tolua_Level_Level_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Level* tolua_ret = (Level*)  Mtolua_new((Level)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Level");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_new00_local
static int tolua_Level_Level_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Level* tolua_ret = (Level*)  Mtolua_new((Level)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Level");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_delete00
static int tolua_Level_Level_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Level* self = (Level*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTexture of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_addTexture00
static int tolua_Level_Level_addTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Level* self = (Level*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTexture'", NULL);
#endif
  {
   self->addTexture(type,filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addActor of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_addActor00
static int tolua_Level_Level_addActor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Hero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Level* self = (Level*)  tolua_tousertype(tolua_S,1,0);
  Hero* node = ((Hero*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addActor'", NULL);
#endif
  {
   self->addActor(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addActor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addActor of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_addActor01
static int tolua_Level_Level_addActor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Npc",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Level* self = (Level*)  tolua_tousertype(tolua_S,1,0);
  Npc* node = ((Npc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addActor'", NULL);
#endif
  {
   self->addActor(node);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Level_Level_addActor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addActor of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_addActor02
static int tolua_Level_Level_addActor02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Level* self = (Level*)  tolua_tousertype(tolua_S,1,0);
  Enemy* node = ((Enemy*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addActor'", NULL);
#endif
  {
   self->addActor(node);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Level_Level_addActor01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMap of class  Level */
#ifndef TOLUA_DISABLE_tolua_Level_Level_setMap00
static int tolua_Level_Level_setMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Level",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Map",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Level* self = (Level*)  tolua_tousertype(tolua_S,1,0);
  Map* map = ((Map*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMap'", NULL);
#endif
  {
   self->setMap(map);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Level_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Level","Level","",tolua_collect_Level);
  #else
  tolua_cclass(tolua_S,"Level","Level","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Level");
   tolua_function(tolua_S,"new",tolua_Level_Level_new00);
   tolua_function(tolua_S,"new_local",tolua_Level_Level_new00_local);
   tolua_function(tolua_S,".call",tolua_Level_Level_new00_local);
   tolua_function(tolua_S,"delete",tolua_Level_Level_delete00);
   tolua_function(tolua_S,"addTexture",tolua_Level_Level_addTexture00);
   tolua_function(tolua_S,"addActor",tolua_Level_Level_addActor00);
   tolua_function(tolua_S,"addActor",tolua_Level_Level_addActor01);
   tolua_function(tolua_S,"addActor",tolua_Level_Level_addActor02);
   tolua_function(tolua_S,"setMap",tolua_Level_Level_setMap00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Level (lua_State* tolua_S) {
 return tolua_Level_open(tolua_S);
};
#endif

