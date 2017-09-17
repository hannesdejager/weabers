object frmSettings: TfrmSettings
  Left = 237
  Top = 208
  BorderStyle = bsDialog
  Caption = 'Settings'
  ClientHeight = 133
  ClientWidth = 339
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblURL: TLabel
    Left = 33
    Top = 16
    Width = 22
    Height = 13
    Caption = 'URL'
  end
  object Label1: TLabel
    Left = 11
    Top = 40
    Width = 44
    Height = 13
    Caption = 'App Path'
  end
  object Label2: TLabel
    Left = 8
    Top = 64
    Width = 47
    Height = 13
    Caption = 'PHP Path'
  end
  object edtUrl: TEdit
    Left = 61
    Top = 12
    Width = 249
    Height = 21
    TabOrder = 0
    Text = 'http://localhost/'
  end
  object btnOK: TButton
    Left = 92
    Top = 96
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 172
    Top = 96
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object edtAppPath: TEdit
    Left = 61
    Top = 36
    Width = 249
    Height = 21
    TabOrder = 3
  end
  object edtPHPPath: TEdit
    Left = 61
    Top = 60
    Width = 249
    Height = 21
    TabOrder = 4
  end
end
