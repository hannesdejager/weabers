/*******************************************************//**
 *    Extentions to the Internet Explorer component.
 *
 *    \file       iexplore.cpp
 *    \author     Hannes de Jager
 *    \date       2006/07/26
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#ifndef iexploreH
#define iexploreH

#include <SHDocVw_OCX.h>
#include <OleCtrls.hpp>
#include <mshtmhst.h>

/***************************************************************************//**
    An implementation of the IDocHostUIHandler interface. This interfaces allows
    customizations to be done to the interface of the Internet Explorer
    ActiveX component.

    It is used here for the Overview Window to disable the default internet
    explorer component popup menu, to hide the 3d borders and to make the
    scrollbars flat.
*//****************************************************************************/
class THTMLBrowserUIHandler :public IDocHostUIHandler
{
private:
    long m_nRefCount; // The reference count for the COM object.
public:
    THTMLBrowserUIHandler();
    
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID classid, void** pInterface);
    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();
    virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(
        /* [in] */ DWORD dwID,
        /* [in] */ POINT __RPC_FAR *ppt,
        /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
        /* [in] */ IDispatch __RPC_FAR *pdispReserved);
    virtual HRESULT STDMETHODCALLTYPE GetHostInfo(
        /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo);
    virtual HRESULT STDMETHODCALLTYPE ShowUI(
        /* [in] */ DWORD dwID,
        /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
        /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
        /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
        /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc);
    virtual HRESULT STDMETHODCALLTYPE HideUI(void);
    virtual HRESULT STDMETHODCALLTYPE UpdateUI(void);
    virtual HRESULT STDMETHODCALLTYPE EnableModeless(/* [in] */ BOOL fEnable);
    virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(/* [in] */ BOOL fActivate);
    virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(/* [in] */ BOOL fActivate);
    virtual HRESULT STDMETHODCALLTYPE ResizeBorder(
        /* [in] */ LPCRECT prcBorder,
        /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
        /* [in] */ BOOL fRameWindow);
    virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(
        /* [in] */ LPMSG lpMsg,
        /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
        /* [in] */ DWORD nCmdID);
    virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath(
        /* [out] */ LPOLESTR __RPC_FAR *pchKey,
        /* [in] */ DWORD dw);
    virtual HRESULT STDMETHODCALLTYPE GetDropTarget(
        /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
        /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget);
    virtual HRESULT STDMETHODCALLTYPE GetExternal(
        /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);
    virtual HRESULT STDMETHODCALLTYPE TranslateUrl(
        /* [in] */ DWORD dwTranslate,
        /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
        /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut);
    virtual HRESULT STDMETHODCALLTYPE FilterDataObject(
        /* [in] */ IDataObject __RPC_FAR *pDO,
        /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet);
};

extern THTMLBrowserUIHandler g_pBrowserUIHandler;

//---------------------------------------------------------------------------
#endif
