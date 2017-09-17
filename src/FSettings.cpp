/*******************************************************//**
 *    Implementation for FSettings.h
 *
 *    \file       FSettings.cpp
 *    \author     Hannes de Jager
 *    \date       2006/07/24
 *
 *//*
 *    Copyright(c) 2006 Inspired Archetypes cc.
 *    All rights reserved.
 **********************************************************/

#include <vcl.h>
#pragma hdrstop

#include "FSettings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmSettings *frmSettings;

//---------------------------------------------------------------------------
__fastcall TfrmSettings::TfrmSettings(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
