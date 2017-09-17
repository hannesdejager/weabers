/*******************************************************//**
 *    Implementation for FMain.h
 *
 *    \file       FMain.cpp
 *    \author     Hannes de Jager
 *    \date       2006/08/01
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#include <vcl.h>
#pragma hdrstop

#include "FMain.h"
//#include "FSettings.h"
//#include <memory>
//#include <Registry.hpp>
#include <SysUtils.hpp>

#include "webserver.h"
#include "globals.h"
#include "lua.h"

#define REFRESH_COMPLETELY 3

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"

TfrmMain *frmMain;

//==============================================================================
//  Local functions
//==============================================================================

namespace MenuBuilding
{

class MenuItemCommand
{
public:
  AnsiString m_sCmd;
  const TMenuItem* m_poMenuItem;
};

class Menu
{
public:
  static Menu* m_bBusy;
  static int m_uiMenuCount;
  static const TMenuItem * m_pMenus[10];
  static unsigned m_uiTotalItemCount;
  static MenuItemCommand m_aoMenuItemCmds[100];

  const TMenuItem * m_pMenuItems[10];
  int m_uiItemCount;

  Menu()
  {
    m_uiItemCount = -1;
    m_bBusy = this;
  }

  ~Menu()
  {
    m_bBusy = NULL;  
  }

  void AddItem(AnsiString _sName, AnsiString _sCaption, AnsiString _sShortcut, AnsiString _sCmd)
  {
    if (m_bBusy == this)
    {
      m_uiItemCount++;
      m_pMenuItems[m_uiItemCount] = NewItem(_sCaption, TextToShortCut(_sShortcut), false,
        true, frmMain->MenuItemClick, 0, _sName);
      m_aoMenuItemCmds[m_uiTotalItemCount].m_sCmd = _sCmd;
      m_aoMenuItemCmds[m_uiTotalItemCount].m_poMenuItem = m_pMenuItems[m_uiItemCount];
      m_uiTotalItemCount++;
    }
  }

  void AddMenu(AnsiString _sName, AnsiString _sCaption)
  {
    if (m_bBusy == this)
    {
      m_uiMenuCount++;
      m_pMenus[m_uiMenuCount] = NewSubMenu(_sCaption, 0, _sName, m_pMenuItems, m_uiItemCount, true);
      m_bBusy = NULL;
    }
  }

};

int Menu::m_uiMenuCount = -1;
const TMenuItem * Menu::m_pMenus[10];
unsigned Menu::m_uiTotalItemCount = 0;
MenuItemCommand Menu::m_aoMenuItemCmds[100];
Menu* Menu::m_bBusy;

Menu* g_pCurMenu = NULL;



TMainMenu* BuildMainMenu()
{
  Lua::Exec("onBuildMainMenu.lua");
  if (Menu::m_uiMenuCount >= 0)
  {
    return NewMenu(frmMain, "mnuMain", Menu::m_pMenus, Menu::m_uiMenuCount);
  }
  else return NULL;
}

};

//---------------------------------------------------------------------------
void WebPostData(TCppWebBrowser* CppWebBrowser, String sURL, String sPostData)
{
  BSTR bstrHeaders = NULL;
  TVariant vFlags = {0}, vTargetFrameName={0}, vPostData={0}, vHeaders={0};
  LPSAFEARRAY psa;
  LPCTSTR cszPostData = sPostData.c_str();
  UINT cElems = lstrlen(cszPostData);
  LPSTR pPostData;
  LPVARIANT pvPostData;

  bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
  if (!bstrHeaders){
    Application->MessageBox("Could not allocate bstrHeaders", "Warning", MB_OK | MB_ICONWARNING);
    return;
  }

  V_VT(&vHeaders) = VT_BSTR;
  V_BSTR(&vHeaders) = bstrHeaders;

  pvPostData = vPostData;

  if(pvPostData)
  {
    VariantInit(pvPostData);

    psa = SafeArrayCreateVector(VT_UI1, 0, cElems);
    if(!psa){
      return;
    }

    SafeArrayAccessData(psa, (LPVOID*)&pPostData);
    memcpy(pPostData, cszPostData, cElems);
    SafeArrayUnaccessData(psa);

    V_VT(pvPostData) = VT_ARRAY | VT_UI1;
    V_ARRAY(pvPostData) = psa;
  }

  CppWebBrowser->Navigate((TVariant)sURL, &vFlags, &vTargetFrameName, &vPostData, &vHeaders);
}
//---------------------------------------------------------------------------


//==============================================================================
//  LUA Functions
//==============================================================================

static int l_SetTitle( lua_State* luaVM)
{
  const char* title = luaL_checkstring(luaVM, 1);
  if (frmMain)
    frmMain->Caption = title;
  return 0;
}

static int l_SetTaskbarTitle( lua_State* luaVM)
{
  const char* title = luaL_checkstring(luaVM, 1);
  Application->Title = title;
  return 0;
}

static int l_SetTitleAndTaskbar( lua_State* luaVM)
{
  const char* title = luaL_checkstring(luaVM, 1);
  Application->Title = title;
  if (frmMain)
    frmMain->Caption = title;
  return 0;
}

static int l_SetBaseURL( lua_State* luaVM)
{
  const char* url = luaL_checkstring(luaVM, 1);
  //frmSettings->edtUrl->Text = url;
  return 0;
}

static int l_SetWebserverPort( lua_State* luaVM)
{
  const int port = luaL_checkinteger(luaVM, 1);
  Globals::g_iPort = port;
  return 0;
}

static int l_SetInitialHTML( lua_State* luaVM)
{
  const char* html = luaL_checkstring(luaVM, 1);
  Globals::g_sInitialHTML = html;
  return 0;
}

static int l_SetSitesPath( lua_State* luaVM)
{
  const char* dir = luaL_checkstring(luaVM, 1);
  Globals::g_sDocRootPath = dir;
  return 0;
}

static int l_SetPHPPath( lua_State* luaVM)
{
  const char* dir = luaL_checkstring(luaVM, 1);
  Globals::g_sPHPPath = dir;
  return 0;
}



static int l_NavigateTo(lua_State* luaVM)
{
  const char* url = luaL_checkstring(luaVM, 1);
  if (frmMain)
    frmMain->cmpBrowser->Navigate(WideString(url));
  return 0;
}

static int l_NewMenu(lua_State* luaVM)
{
  if (!MenuBuilding::g_pCurMenu)
    MenuBuilding::g_pCurMenu = new MenuBuilding::Menu();
  return 0;
}

static int l_AddMenuItem(lua_State* luaVM)
{
  if (MenuBuilding::g_pCurMenu)
  {
    const char* name = luaL_checkstring(luaVM, 1);
    const char* caption = luaL_checkstring(luaVM, 2);
    const char* shortcut = luaL_checkstring(luaVM, 3);
    const char* cmd = luaL_checkstring(luaVM, 4);
    MenuBuilding::g_pCurMenu->AddItem(name, caption, shortcut, cmd);
  }
  return 0;
}

static int l_AddMenu(lua_State* luaVM)
{
  const char* name = luaL_checkstring(luaVM, 1);
  const char* caption = luaL_checkstring(luaVM, 2);
  if (MenuBuilding::g_pCurMenu)
  {
    MenuBuilding::g_pCurMenu->AddMenu(name, caption);
    delete MenuBuilding::g_pCurMenu;
    MenuBuilding::g_pCurMenu = NULL;
  }
  return 0;
}

//==============================================================================
// TfrmMain 
//==============================================================================

__fastcall TfrmMain::TfrmMain(TComponent* Owner)
  : TForm(Owner)
{
  Globals::g_sAppPath = IncludeTrailingBackslash(ExtractFilePath(ParamStr(0)));

  // Initialize LUA
  Lua::Init();
  lua_register(Lua::g_pLua, "SetTitle", l_SetTitle);
  lua_register(Lua::g_pLua, "SetTaskbarTitle", l_SetTaskbarTitle);
  lua_register(Lua::g_pLua, "SetTitleAndTaskbar", l_SetTitleAndTaskbar);
  lua_register(Lua::g_pLua, "SetBaseURL", l_SetBaseURL);
  lua_register(Lua::g_pLua, "SetWebserverPort", l_SetWebserverPort);
  lua_register(Lua::g_pLua, "SetInitialHTML", l_SetInitialHTML);
  lua_register(Lua::g_pLua, "SetPHPPath", l_SetPHPPath);
  lua_register(Lua::g_pLua, "NavigateTo", l_NavigateTo);
  lua_register(Lua::g_pLua, "NewMenu", l_NewMenu);
  lua_register(Lua::g_pLua, "AddMenuItem", l_AddMenuItem);
  lua_register(Lua::g_pLua, "AddMenu", l_AddMenu);
  lua_register(Lua::g_pLua, "SetSitesPath", l_SetSitesPath);


  OleInitialize(NULL);
  // Set loading message or something

  m_pBrowserUIHandler = &g_pBrowserUIHandler;
  OpenHTML("");
  while(cmpBrowser->Busy)
      Application->ProcessMessages();
  m_pBrowserCustomDoc = NULL;
  if (cmpBrowser->Document)
    cmpBrowser->Document->QueryInterface(&m_pBrowserCustomDoc);
  if (m_pBrowserCustomDoc)
    m_pBrowserCustomDoc->SetUIHandler(m_pBrowserUIHandler);
  else
  {
    MessageDlg("Error customizing browser component.", mtError, TMsgDlgButtons() << mbOK, 0);
  }

  Caption = CAPTIONTITLE;
  Lua::Exec("onInit.lua");
  OpenHTML(Globals::g_sInitialHTML);
  Menu = MenuBuilding::BuildMainMenu();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
  Lua::Done();
  WebServer::Done();
}
//---------------------------------------------------------------------------
void TfrmMain::LoadSaveSettings(bool _bLoad)
{
/*  std::auto_ptr<TRegistry> pReg(new TRegistry(KEY_ALL_ACCESS));
  pReg->RootKey = HKEY_CURRENT_USER;
  pReg->OpenKey("Software\\Inspired Archetypes\\Weabers\\1.0", true);
  if (_bLoad)
  {
    frmSettings->edtUrl->Text = pReg->ReadString("URL");
  }
  else
  {
    pReg->WriteString("URL", frmSettings->edtUrl->Text);
  }
  pReg->CloseKey();   */
}
//---------------------------------------------------------------------------
void TfrmMain::OpenHTML(AnsiString sHTML)
{
    try
    {
        if (cmpBrowser->Document == NULL || sHTML.IsEmpty())
        {
            m_sHTMLCache = sHTML;
            cmpBrowser->Navigate(L"About:blank");
        }
        else
        {

            AnsiString sBase = "<BASE HREF=\""+IncludeTrailingBackslash(ExtractFilePath(ParamStr(0)))+"\">";
            int nHeadPos = sHTML.LowerCase().Pos("<head>");
            if (nHeadPos > 0)
                sHTML.Insert(sBase, nHeadPos + 6);

            m_sHTMLCache = "";
            Variant pDoc = cmpBrowser->Document;
            if (!VarIsClear(pDoc))
            {
                pDoc.Exec(Procedure("close"));
                pDoc.Exec(Procedure("write") << sHTML);
                pDoc = Unassigned;
            }
        }
    }
    catch (...)
    {
        Close();
    }
}
//---------------------------------------------------------------------------

AnsiString NormalizeFPath(AnsiString _sPath, AnsiString _sDef)
{
  if (!FileExists(_sPath))
  {
    _sPath = Globals::g_sAppPath + _sPath;
    if (!FileExists(_sPath))
    {
      _sPath = Globals::g_sAppPath + _sDef;
    }
  }

  return ExpandFileName(_sPath);
}

AnsiString NormalizeDPath(AnsiString _sPath, AnsiString _sDef)
{
  if (!DirectoryExists(_sPath))
  {
    _sPath = Globals::g_sAppPath + _sPath;
    if (!DirectoryExists(_sPath))
    {
      _sPath = Globals::g_sAppPath + _sDef;
    }
  }

  return ExpandFileName(_sPath);
}

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
  // Load settings from the registry
  LoadSaveSettings(true);

  //Lua::Exec("onInit.lua");
  Globals::g_sDocRootPath = NormalizeDPath(Globals::g_sDocRootPath, "sites");
  Globals::g_sPHPPath = NormalizeFPath(Globals::g_sPHPPath, "php\\php-cgi.exe");

  // Initialize and start the Webserver
  WebServer::Init(Globals::g_sDocRootPath, Globals::g_sPHPPath, Globals::g_iPort);
  WebServer::Start();

  Lua::Exec("onReady.lua");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::MenuItemClick(TObject *Sender)
{
  if (MenuBuilding::Menu::m_uiTotalItemCount > 0)
  {
    for (int i=0; i < MenuBuilding::Menu::m_uiTotalItemCount; i++)
    {
      if (MenuBuilding::Menu::m_aoMenuItemCmds[i].m_poMenuItem == (void*)Sender)
      {
        AnsiString sCmd = MenuBuilding::Menu::m_aoMenuItemCmds[i].m_sCmd;
        if (sCmd.Pos("cmd:") == 1)
        {
          if (sCmd == "cmd:Exit")
          {
            Close();
          }
          else if (sCmd == "cmd:Print")
          {
            actPrint->Execute();
          }
          else if (sCmd == "cmd:Refresh")
          {
            actRefresh->Execute();
          }
        }
        else if (sCmd.Pos("lua:") == 1)
        {
          AnsiString sFile = sCmd.Delete(1, 4);
          if (FileExists(sFile))
            Lua::Exec(sFile);
          else
            MessageDlg("File "+sFile+" not found.", mtError, TMsgDlgButtons() << mbOK, 0);
        }
        else
          cmpBrowser->Navigate(WideString(sCmd));
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actRefreshExecute(TObject *Sender)
{
  cmpBrowser->Refresh2(Variant(REFRESH_COMPLETELY));
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actPrintExecute(TObject *Sender)
{
  Variant empty;
  cmpBrowser->ExecWB(Shdocvw_tlb::OLECMDID_PRINT, Shdocvw_tlb::OLECMDEXECOPT_DODEFAULT, empty, empty);
}
//---------------------------------------------------------------------------




