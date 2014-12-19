/*
** Lua binding: Hero
** Generated automatically by tolua++-1.0.92 on 05/26/14 18:28:44.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Hero_open (lua_State* tolua_S);

#include "..\header\Hero.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Hero (lua_State* tolua_S)
{
 Hero* self = (Hero*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Hero");
}

/* method: new of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_new00
static int tolua_Hero_Hero_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int texture_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Hero* tolua_ret = (Hero*)  Mtolua_new((Hero)(texture_id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Hero");
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

/* method: new_local of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_new00_local
static int tolua_Hero_Hero_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int texture_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Hero* tolua_ret = (Hero*)  Mtolua_new((Hero)(texture_id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Hero");
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

/* method: moveRight of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_moveRight00
static int tolua_Hero_Hero_moveRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  int px = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveRight'", NULL);
#endif
  {
   self->moveRight(px);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: moveLeft of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_moveLeft00
static int tolua_Hero_Hero_moveLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  int px = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveLeft'", NULL);
#endif
  {
   self->moveLeft(px);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: moveDown of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_moveDown00
static int tolua_Hero_Hero_moveDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  int px = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveDown'", NULL);
#endif
  {
   self->moveDown(px);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: moveUp of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_moveUp00
static int tolua_Hero_Hero_moveUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  int px = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveUp'", NULL);
#endif
  {
   self->moveUp(px);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_setPosition00
static int tolua_Hero_Hero_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scale of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_scale00
static int tolua_Hero_Hero_scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scale'", NULL);
#endif
  {
   self->scale(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionRect of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_setCollisionRect00
static int tolua_Hero_Hero_setCollisionRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float w = ((float)  tolua_tonumber(tolua_S,4,0));
  float h = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionRect'", NULL);
#endif
  {
   self->setCollisionRect(x,y,w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addAnimationFrames of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_addAnimationFrames00
static int tolua_Hero_Hero_addAnimationFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  int anim_type = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string distribution = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string loop_type = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  int num_frames = ((int)  tolua_tonumber(tolua_S,5,0));
  int position = ((int)  tolua_tonumber(tolua_S,6,0));
  int width = ((int)  tolua_tonumber(tolua_S,7,0));
  int height = ((int)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addAnimationFrames'", NULL);
#endif
  {
   self->addAnimationFrames(anim_type,distribution,loop_type,num_frames,position,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addAnimationFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initAnimation of class  Hero */
#ifndef TOLUA_DISABLE_tolua_Hero_Hero_initAnimation00
static int tolua_Hero_Hero_initAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Hero* self = (Hero*)  tolua_tousertype(tolua_S,1,0);
  const int state = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initAnimation'", NULL);
#endif
  {
   self->initAnimation(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Hero_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Hero","Hero","",tolua_collect_Hero);
  #else
  tolua_cclass(tolua_S,"Hero","Hero","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Hero");
   tolua_function(tolua_S,"new",tolua_Hero_Hero_new00);
   tolua_function(tolua_S,"new_local",tolua_Hero_Hero_new00_local);
   tolua_function(tolua_S,".call",tolua_Hero_Hero_new00_local);
   tolua_function(tolua_S,"moveRight",tolua_Hero_Hero_moveRight00);
   tolua_function(tolua_S,"moveLeft",tolua_Hero_Hero_moveLeft00);
   tolua_function(tolua_S,"moveDown",tolua_Hero_Hero_moveDown00);
   tolua_function(tolua_S,"moveUp",tolua_Hero_Hero_moveUp00);
   tolua_function(tolua_S,"setPosition",tolua_Hero_Hero_setPosition00);
   tolua_function(tolua_S,"scale",tolua_Hero_Hero_scale00);
   tolua_function(tolua_S,"setCollisionRect",tolua_Hero_Hero_setCollisionRect00);
   tolua_function(tolua_S,"addAnimationFrames",tolua_Hero_Hero_addAnimationFrames00);
   tolua_function(tolua_S,"initAnimation",tolua_Hero_Hero_initAnimation00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Hero (lua_State* tolua_S) {
 return tolua_Hero_open(tolua_S);
};
#endif

