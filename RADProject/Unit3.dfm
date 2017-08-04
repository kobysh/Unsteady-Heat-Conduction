object Form3: TForm3
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1043#1088#1072#1092#1080#1082' '#1076#1083#1103' '#1085#1077#1103#1074#1085#1086#1081' '#1089#1093#1077#1084#1099
  ClientHeight = 468
  ClientWidth = 604
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 8
    Top = 5
    Width = 585
    Height = 453
    ActivePage = TabSheet5
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'tay nach'
      object Chart3: TChart
        Left = 3
        Top = 3
        Width = 571
        Height = 419
        Legend.Alignment = laBottom
        Title.Text.Strings = (
          'T(x)')
        View3D = False
        Color = clWhite
        TabOrder = 0
        object LineSeries1: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          Title = 'tay_nach'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = '1/3 tay'
      ImageIndex = 1
      ExplicitLeft = 0
      object Chart1: TChart
        Left = 3
        Top = 3
        Width = 571
        Height = 419
        Legend.Alignment = laBottom
        Title.Text.Strings = (
          'T(x)')
        View3D = False
        Color = clWhite
        TabOrder = 0
        object LineSeries2: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          SeriesColor = 33023
          Title = '1/3_tay'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = '1/2 tay'
      ImageIndex = 2
      object Chart2: TChart
        Left = 0
        Top = 0
        Width = 574
        Height = 422
        Legend.Alignment = laBottom
        Title.Text.Strings = (
          'T(x)')
        View3D = False
        Color = clWhite
        TabOrder = 0
        object LineSeries3: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          SeriesColor = 4259584
          Title = '1/2_tay'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = '2/3 tay'
      ImageIndex = 3
      object Chart4: TChart
        Left = 3
        Top = 0
        Width = 571
        Height = 422
        Legend.Alignment = laBottom
        Title.Text.Strings = (
          'T(x)')
        View3D = False
        Color = clWhite
        TabOrder = 0
        object LineSeries4: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          SeriesColor = 16744576
          Title = '2/3_tay'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'tay kon'
      ImageIndex = 4
      object Chart5: TChart
        Left = 3
        Top = 3
        Width = 571
        Height = 419
        Legend.Alignment = laBottom
        Title.Text.Strings = (
          'T(x)')
        View3D = False
        Color = clWhite
        TabOrder = 0
        object LineSeries5: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          SeriesColor = clBlue
          Title = 'tay_kon'
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
  end
end
