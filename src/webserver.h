/*******************************************************//**
 *    Contains the embedded webserver.
 *
 *    \file       webserver.cpp
 *    \author     Hannes de Jager
 *    \date       2006/07/31
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#ifndef webserverH
#define webserverH

#include <Classes.hpp>

namespace WebServer
{

/**
 * Initializes the webserver
 */
void Init(AnsiString _sSitesPath, AnsiString _sPHPPath, int port);
/**
 * uninitializes the webserver
 */
void Done();
/**
 * Service the next request.
 */
void Service();
/**
 * Start the server thread.
 */
void Start();
/**
 * Stop the server thread.
 */
void Stop();

};
//---------------------------------------------------------------------------
#endif
