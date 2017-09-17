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

#pragma hdrstop
#include "Lua.h"
#pragma package(smart_init)

namespace Lua
{

//==============================================================================
//  Globals
//==============================================================================
lua_State* g_pLua = NULL;


void Init()
{
	/* initialize Lua */
	g_pLua = lua_open();

  luaopen_base(g_pLua );     /* opens the basic library */
  luaopen_table(g_pLua );    /* opens the table library */
//  luaopen_io(g_pLua );       /* opens the I/O library */
  luaopen_string(g_pLua );   /* opens the string lib. */
  luaopen_math(g_pLua );     /* opens the math lib. */

  if (!g_pLua)
  {
    throw Exception("Error Initializing lua\n");
  }

}

void Done()
{
	/* cleanup Lua */
	lua_close(g_pLua);
}

void Exec(AnsiString _sFile)
{
	luaL_dofile(g_pLua, _sFile.c_str());
}

};
