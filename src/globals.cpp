/*******************************************************//**
 *    Implementation for Globals.h
 *
 *    \file       Globals.cpp
 *    \author     Hannes de Jager
 *    \date       2006/08/01
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#pragma hdrstop
#include "Globals.h"
#pragma package(smart_init)

AnsiString Globals::g_sAppPath;
AnsiString Globals::g_sDocRootPath;
AnsiString Globals::g_sPHPPath;
AnsiString Globals::g_sInitialHTML = "<html><head>"\
    "<style type='text/css'>\r\n"\
    "#idLoading { padding-left: 5px; background-color: red; display:block; color: white;} </style>\r\n"\
    "</head><body><div id='idLoading'>Loading...</div></body></html>";
int Globals::g_iPort = 80;
