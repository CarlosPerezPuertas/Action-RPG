/*
** Lua binding: Enemy
** Generated automatically by tolua++-1.0.92 on 10/13/14 15:04:01.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Enemy_open (lua_State* tolua_S);

#include "..\header\Enemy.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Enemy (lua_State* tolua_S)
{
 Enemy* self = (Enemy*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Enemy");
}

/* method: new of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_new00
static int tolua_Enemy_Enemy_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int c_texture_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Enemy* tolua_ret = (Enemy*)  Mtolua_new((Enemy)(c_texture_id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Enemy");
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

/* method: new_local of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_new00_local
static int tolua_Enemy_Enemy_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int c_texture_id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Enemy* tolua_ret = (Enemy*)  Mtolua_new((Enemy)(c_texture_id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Enemy");
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

/* method: delete of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_delete00
static int tolua_Enemy_Enemy_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: moveRight of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_moveRight00
static int tolua_Enemy_Enemy_moveRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: moveLeft of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_moveLeft00
static int tolua_Enemy_Enemy_moveLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: moveDown of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_moveDown00
static int tolua_Enemy_Enemy_moveDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: moveUp of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_moveUp00
static int tolua_Enemy_Enemy_moveUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setText of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_setText00
static int tolua_Enemy_Enemy_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  std::string c_text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(c_text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: displayText of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_displayText00
static int tolua_Enemy_Enemy_displayText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'displayText'", NULL);
#endif
  {
   self->displayText();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'displayText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_setPosition00
static int tolua_Enemy_Enemy_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: scale of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_scale00
static int tolua_Enemy_Enemy_scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: setCollisionRect of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_setCollisionRect00
static int tolua_Enemy_Enemy_setCollisionRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
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
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: addAnimationFrames of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_addAnimationFrames00
static int tolua_Enemy_Enemy_addAnimationFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
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
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
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

/* method: isTalking of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_Enemy_Enemy_isTalking00
static int tolua_Enemy_Enemy_isTalking00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTalking'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTalking();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTalking'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Enemy_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Enemy","Enemy","",tolua_collect_Enemy);
  #else
  tolua_cclass(tolua_S,"Enemy","Enemy","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Enemy");
   tolua_function(tolua_S,"new",tolua_Enemy_Enemy_new00);
   tolua_function(tolua_S,"new_local",tolua_Enemy_Enemy_new00_local);
   tolua_function(tolua_S,".call",tolua_Enemy_Enemy_new00_local);
   tolua_function(tolua_S,"delete",tolua_Enemy_Enemy_delete00);
   tolua_function(tolua_S,"moveRight",tolua_Enemy_Enemy_moveRight00);
   tolua_function(tolua_S,"moveLeft",tolua_Enemy_Enemy_moveLeft00);
   tolua_function(tolua_S,"moveDown",tolua_Enemy_Enemy_moveDown00);
   tolua_function(tolua_S,"moveUp",tolua_Enemy_Enemy_moveUp00);
   tolua_function(tolua_S,"setText",tolua_Enemy_Enemy_setText00);
   tolua_function(tolua_S,"displayText",tolua_Enemy_Enemy_displayText00);
   tolua_function(tolua_S,"setPosition",tolua_Enemy_Enemy_setPosition00);
   tolua_function(tolua_S,"scale",tolua_Enemy_Enemy_scale00);
   tolua_function(tolua_S,"setCollisionRect",tolua_Enemy_Enemy_setCollisionRect00);
   tolua_function(tolua_S,"addAnimationFrames",tolua_Enemy_Enemy_addAnimationFrames00);
   tolua_function(tolua_S,"isTalking",tolua_Enemy_Enemy_isTalking00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Enemy (lua_State* tolua_S) {
 return tolua_Enemy_open(tolua_S);
};
#endif

