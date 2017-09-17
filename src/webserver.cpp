/*******************************************************//**
 *    Implementation for webserver.h
 *
 *    \file       webserver.cpp
 *    \author     Hannes de Jager
 *    \date       2006/07/31
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#pragma hdrstop
#include "webserver.h"
#pragma package(smart_init)

#include "shttpd.h"
#include <classes.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
 #include <vcl.h>

struct shttpd_ctx	*ctx;

void WebServer::Init(AnsiString _sSitesPath, AnsiString _sPHPPath, int port)
{
	ctx = shttpd_init(
    NULL,
		"document_root", _sSitesPath.c_str(),
    "cgi_extention", ".php",
    "cgi_interpreter", _sPHPPath.c_str(),
    "mime_types", "builtin",
    NULL);

	/* Let pass 'data' variable to callback, user can change it */
	//shttpd_register_url(ctx, "/", &index_html, (void *) &data);
	//shttpd_register_url(ctx, "/index.html", &index_html, (void *) &data);

	/* Open listening socket */
	int sock = shttpd_open_port(port);
	shttpd_listen(ctx, sock);
};

void WebServer::Service()
{
  shttpd_poll(ctx, 1000);
}

void WebServer::Done()
{
	/* Probably unreached, because we will be killed by signal */
	shttpd_fini(ctx);
}

/**
 * Thread in which webserver execute.
 */
class CWebServerThread :public TThread
{
public:
  /**
   *
   */
  CWebServerThread()
    : TThread(false)
    , m_bEnd(false)
  {

  }

protected:
  /**
   *
   */
  bool m_bEnd;
  /**
   *
   */
  void __fastcall Execute()
  {
    while (!Terminated)
    {
      WebServer::Service();
      Sleep(100);
    }
  }

};


CWebServerThread* g_pThread;

void WebServer::Start()
{
  g_pThread = new CWebServerThread();
}

void WebServer::Stop()
{
  g_pThread->Terminate();
  delete g_pThread;
}


