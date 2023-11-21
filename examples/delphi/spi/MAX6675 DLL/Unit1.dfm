object Form1: TForm1
  Left = 233
  Top = 131
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MAXIM6675 SPI Temperature'
  ClientHeight = 261
  ClientWidth = 303
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    303
    261)
  PixelsPerInch = 96
  TextHeight = 13
  object Temperature: TLabel
    Left = 0
    Top = 8
    Width = 304
    Height = 37
    Alignment = taCenter
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = '?,?? '#176'C'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Chart1: TChart
    Left = 8
    Top = 64
    Width = 289
    Height = 193
    AllowPanning = pmHorizontal
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Font.Charset = DEFAULT_CHARSET
    Title.Font.Color = clBlack
    Title.Font.Height = -11
    Title.Font.Name = 'Arial'
    Title.Font.Style = []
    Title.Text.Strings = (
      'Temperature over last 60 secs')
    Legend.Visible = False
    View3D = False
    View3DWalls = False
    BevelOuter = bvNone
    TabOrder = 0
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Kicker: TTimer
    Enabled = False
    OnTimer = KickerTimer
    Left = 232
    Top = 8
  end
end
