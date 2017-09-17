/*******************************************************//**
 *    Implementation for iexplore.h
 *
 *    \file       iexplore.cpp
 *    \author     Hannes de Jager
 *    \date       2006/07/26
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#pragma hdrstop
#include "iexplore.h"
#pragma package(smart_init)

THTMLBrowserUIHandler g_pBrowserUIHandler;

//===========================================================================
// THTMLBrowserUIHandler
//===========================================================================

/***************************************************************************//**
    Class contructor.
*//****************************************************************************/
THTMLBrowserUIHandler::THTMLBrowserUIHandler()
    :m_nRefCount(1)
{
}

/***************************************************************************//**
    Implementation of IUnknown::QueryInterface
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::QueryInterface(REFIID pClassID, void** pInterface)
{
    if (pClassID == IID_IUnknown)
        *pInterface = (IUnknown*)this;
    else if (pClassID == IID_IDocHostUIHandler)
        *pInterface = (IDocHostUIHandler*)this;
    else
        return E_NOINTERFACE;
    return S_OK;
}

/***************************************************************************//**
    Implementation of IUnknown::AddRef
*//****************************************************************************/
ULONG STDMETHODCALLTYPE THTMLBrowserUIHandler::AddRef()
{
    InterlockedIncrement(&m_nRefCount);
    return m_nRefCount;
}

/***************************************************************************//**
    Implementation of IUnknown::Release
*//****************************************************************************/
ULONG STDMETHODCALLTYPE THTMLBrowserUIHandler::Release()
{
    InterlockedDecrement(&m_nRefCount);
    return m_nRefCount;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::ShowContextMenu.
    
    Returning S_OK tells the web browser that it need not display its
    own context menu, presumably because the application hosting it has
    displayed its own menu to replace it.
    Since our host does not display any, no context menu is shown.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::ShowContextMenu(
/* [in] */ DWORD dwID,
/* [in] */ POINT __RPC_FAR *ppt,
/* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
/* [in] */ IDispatch __RPC_FAR *pdispReserved) {
    return S_OK; // Cause context menu not to be displayed
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::GetHostInfo.
    
    Disable the border and scroll bars.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::GetHostInfo(
/* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo)
{
  pInfo->cbSize = sizeof(DOCHOSTUIINFO);
  pInfo->dwFlags =
   // DOCHOSTUIFLAG_DIALOG                     |
   // DOCHOSTUIFLAG_DISABLE_HELP_MENU          |
      DOCHOSTUIFLAG_NO3DBORDER                 |  /* No 3D Border   */
   //   DOCHOSTUIFLAG_SCROLL_NO                  |  /* Hide Scrollbar */
   // DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE    |
   // DOCHOSTUIFLAG_OPENNEWWIN                 |
   // DOCHOSTUIFLAG_DISABLE_OFFSCREEN          |
      DOCHOSTUIFLAG_FLAT_SCROLLBAR             |
   // DOCHOSTUIFLAG_DIV_BLOCKDEFAULT           |
   // DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY    |
   // DOCHOSTUIFLAG_OVERRIDEBEHAVIORFACTORY    |
   // DOCHOSTUIFLAG_CODEPAGELINKEDFONTS        |
   // DOCHOSTUIFLAG_URL_ENCODING_DISABLE_UTF8  |
   // DOCHOSTUIFLAG_URL_ENCODING_ENABLE_UTF8   |
   // DOCHOSTUIFLAG_ENABLE_FORMS_AUTOCOMPLETE  |
   // DOCHOSTUIFLAG_ENABLE_INPLACE_NAVIGATION  | 
   // DOCHOSTUIFLAG_IME_ENABLE_RECONVERSION    |
   // DOCHOSTUIFLAG_THEME                      |
   // DOCHOSTUIFLAG_NOTHEME                    |
   // DOCHOSTUIFLAG_NOPICS                     |
   0x00200000/*DOCHOSTUIFLAG_NO3DOUTERBORDER*/ |
      0                                        ;
  // What happens if user double clicks?
  pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;
  return S_OK ;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::ShowUI.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::ShowUI(
/* [in] */ DWORD dwID,
/* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
/* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
/* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
/* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc) {
    return S_OK;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::HideUI.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::HideUI( void) {
    return S_OK;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::UpdateUI.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::UpdateUI( void) {
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::EnableModeless.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::EnableModeless(
/* [in] */ BOOL fEnable) {
    return S_OK;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::OnDocWindowActivate.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::OnDocWindowActivate(
/* [in] */ BOOL fActivate) {
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::OnFrameWindowActivate.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::OnFrameWindowActivate(
/* [in] */ BOOL fActivate) {
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::ResizeBorder.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::ResizeBorder(
    /* [in] */ LPCRECT prcBorder,
    /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
    /* [in] */ BOOL fRameWindow)
{
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::TranslateAccelerator.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::TranslateAccelerator(
    /* [in] */ LPMSG lpMsg,
    /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
    /* [in] */ DWORD nCmdID)
{
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::GetOptionKeyPath.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::GetOptionKeyPath(
    /* [out] */ LPOLESTR __RPC_FAR *pchKey,
    /* [in] */ DWORD dw)
{
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::GetDropTarget.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::GetDropTarget(
    /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
    /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget)
{
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::GetExternal.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::GetExternal(
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch)
{
    *ppDispatch = NULL;
    return S_OK;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::TranslateUrl.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::TranslateUrl(
    /* [in] */ DWORD dwTranslate,
    /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut)
{
    return S_FALSE;
}

/***************************************************************************//**
    Implementation of IDocHostUIHandler::FilterDataObject.
*//****************************************************************************/
HRESULT STDMETHODCALLTYPE THTMLBrowserUIHandler::FilterDataObject(
    /* [in] */ IDataObject __RPC_FAR *pDO,
    /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet)
{
    return S_FALSE;
}