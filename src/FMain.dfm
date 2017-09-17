object frmMain: TfrmMain
  Left = 242
  Top = 183
  Width = 696
  Height = 480
  Caption = 'IA Weabers'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object cmpBrowser: TCppWebBrowser
    Left = 0
    Top = 0
    Width = 688
    Height = 427
    Align = alClient
    TabOrder = 0
    ControlData = {
      4C0000001B470000222C00000000000000000000000000000000000000000000
      000000004C000000000000000000000001000000E0D057007335CF11AE690800
      2B2E126208000000000000004C0000000114020000000000C000000000000046
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000100000000000000000000000000000000000000}
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 427
    Width = 688
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object cmpActions: TActionManager
    Left = 368
    Top = 24
    object actFileExit: TFileExit
      Category = 'File'
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object actRefresh: TAction
      Category = 'File'
      ShortCut = 116
      OnExecute = actRefreshExecute
    end
    object actSettings: TAction
      Category = 'File'
    end
    object actPrint: TAction
      Category = 'File'
      ShortCut = 16464
      OnExecute = actPrintExecute
    end
    object actFindSupplier: TAction
      Category = 'File'
      ShortCut = 113
    end
  end
end
