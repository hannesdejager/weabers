/*******************************************************//**
 *    The about box of the application.
 *
 *    \file       FAbout.h
 *    \version    1.0
 *    \author     Hannes de Jager
 *    \date       2005/04/01
 *
 *//*
 *    Copyright(c) 2005 Softeagle Systems CC.
 *    All rights reserved.
 **********************************************************/

#ifndef FAboutH
#define FAboutH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include "HTMLText.hpp"
#include <ImgList.hpp>
#include "AdvPicture.hpp"
#include "AdvShaper.hpp"
#include "LayeredForm.hpp"
#include "frmshape.hpp"
#include <jpeg.hpp>
//----------------------------------------------------------------------------
class TfrmAbout : public TForm
{
__published:
    THTMLStaticText *txtInfo;
  TPanel *Panel1;
  TImage *Image1;
  TPanel *Panel2;
    void __fastcall txtInfoClick(TObject *Sender);
    void __fastcall Image1Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:
public:
  bool m_bSplashMode;
	virtual __fastcall TfrmAbout(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmAbout *frmAbout;
//----------------------------------------------------------------------------
#endif    
