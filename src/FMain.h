/*******************************************************//**
 *    Contains the main form
 *
 *    \file       FMain.cpp
 *    \author     Hannes de Jager
 *    \date       2006/07/24
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#ifndef FMainH
#define FMainH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <StdActns.hpp>

#include "iexplore.h"
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <ComCtrls.hpp>

/***************************************************************************//**
  The main from class.
*//****************************************************************************/
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
  TCppWebBrowser *cmpBrowser;
  TActionManager *cmpActions;
  TFileExit *actFileExit;
  TAction *actRefresh;
  TAction *actSettings;
  TAction *actPrint;
  TAction *actFindSupplier;
  TStatusBar *StatusBar1;
  void __fastcall MenuItemClick(TObject *Sender);
  void __fastcall actRefreshExecute(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall actPrintExecute(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
  THTMLBrowserUIHandler*  m_pBrowserUIHandler; ///< The IDocHostUIHandler interface that handles the customization of internet explorer component interface.
  ICustomDoc *m_pBrowserCustomDoc; ///< Interface implemented by MSHTML, used to set the UI handler to our interface in m_pBrowserUIHandler.
  AnsiString m_sHTMLCache;
  void OpenHTML(AnsiString sHTML);  
public:		// User declarations
  __fastcall TfrmMain(TComponent* Owner);
  void LoadSaveSettings(bool _bLoad);
};

#define CAPTIONTITLE "IA Weabers"

//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------

#endif
