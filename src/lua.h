/*******************************************************//**
 *    Implementation for Lua.h
 *
 *    \file       Lua.cpp
 *    \author     Hannes de Jager
 *    \date       2006/06/23
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#ifndef LuaH
#define LuaH

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <classes.hpp>

namespace Lua
{

/* the Lua interpreter */
extern lua_State* g_pLua;

void Init();
void Done();
void Exec(AnsiString _sFile);

};
#endif



