/*******************************************************//**
 *    The settings form.
 *
 *    \file       FSettings.cpp
 *    \author     Hannes de Jager
 *    \date       2006/07/24
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#ifndef FSettingsH
#define FSettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmSettings : public TForm
{
__published:	// IDE-managed Components
  TLabel *lblURL;
  TEdit *edtUrl;
  TButton *btnOK;
  TButton *btnCancel;
  TEdit *edtAppPath;
  TEdit *edtPHPPath;
  TLabel *Label1;
  TLabel *Label2;
private:	// User declarations
public:		// User declarations
  __fastcall TfrmSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSettings *frmSettings;
//---------------------------------------------------------------------------
#endif
