/*******************************************************//**
 *    Implementation for FAbout.h
 *
 *    \file       FAbout.cpp
 *    \author     Hannes de Jager
 *    \date       2005/04/01
 *
 *//*
 *    Copyright(c) 2005 Softeagle Systems CC.
 *    All rights reserved.
 **********************************************************/

#include <vcl.h>
#include "tchar.h"
#include <stdio.h>
#pragma hdrstop

#include "FAbout.h"
//--------------------------------------------------------------------- 
#pragma link "HTMLText"
#pragma link "AdvPicture"
#pragma link "AdvShaper"
#pragma link "LayeredForm"
#pragma link "frmshape"
#pragma resource "*.dfm"

TfrmAbout *frmAbout;

//==============================================================================
//  Local types and functions
//==============================================================================


/**
 * A type used by the GetFileInfoForKey function
 */
struct TransArray
{
  WORD LanguageID,
  CharacterSet;
};

/**
 * Gets file information for a certain key.
 */
String __fastcall GetFileInfoForKey(String _strKey, String _exeName = ExtractFileName(ParamStr(0)))
{
  String strKey = "";
  DWORD VerInfo, VerSize;
  HANDLE MemHandle;
  LPVOID MemPtr, BufferPtr;
  UINT BufferLength;
  TransArray *Array;
  char QueryBlock[45];

  String strPath = _exeName; //(pszFileName);
  VerSize = GetFileVersionInfoSize(strPath.c_str(), &VerInfo);
  if (VerSize > 0)
  {
    MemHandle = GlobalAlloc(GMEM_MOVEABLE, VerSize);
    MemPtr = GlobalLock(MemHandle);
    GetFileVersionInfo(strPath.c_str(), VerInfo, VerSize, MemPtr);
    VerQueryValue(MemPtr, "\\VarFileInfo\\Translation", &BufferPtr,
                  &BufferLength);
    Array = (TransArray *)BufferPtr;

    // Get Key Value for _strKey.
    _strKey = "\\StringFileInfo\\%04x%04x\\" + _strKey;
    wsprintf(QueryBlock,
             _strKey.c_str(),
             Array[0].LanguageID,
             Array[0].CharacterSet);
    VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
    strKey = (char *)BufferPtr;

    GlobalUnlock(MemHandle);
    GlobalFree(MemHandle);
  }
  return strKey;
}

//==============================================================================
// TfrmAbout 
//==============================================================================

__fastcall TfrmAbout::TfrmAbout(TComponent* AOwner)
	: TForm(AOwner)
  , m_bSplashMode(false)
{
}
//---------------------------------------------------------------------
void __fastcall TfrmAbout::txtInfoClick(TObject *Sender)
{
  if (!m_bSplashMode)
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::Image1Click(TObject *Sender)
{
  if (!m_bSplashMode)
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::FormShow(TObject *Sender)
{
  AnsiString s;
  txtInfo->HTMLText->Text = s.sprintf(
    txtInfo->HTMLText->Text.c_str(),
    GetFileInfoForKey(m_bSplashMode?"ProductVersion":"FileVersion"));
}
//---------------------------------------------------------------------------

