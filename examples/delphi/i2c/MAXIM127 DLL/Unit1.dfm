object Form1: TForm1
  Left = 233
  Top = 131
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MAXIM127 IIC Voltage'
  ClientHeight = 290
  ClientWidth = 242
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Arial'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 18
  object Label1: TLabel
    Left = 88
    Top = 40
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label2: TLabel
    Left = 88
    Top = 64
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label3: TLabel
    Left = 88
    Top = 88
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label4: TLabel
    Left = 88
    Top = 112
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label5: TLabel
    Left = 88
    Top = 136
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label6: TLabel
    Left = 88
    Top = 160
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label7: TLabel
    Left = 88
    Top = 184
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label8: TLabel
    Left = 88
    Top = 208
    Width = 81
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
  end
  object Label9: TLabel
    Left = 184
    Top = 40
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label10: TLabel
    Left = 184
    Top = 64
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label11: TLabel
    Left = 184
    Top = 88
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label12: TLabel
    Left = 184
    Top = 112
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label13: TLabel
    Left = 184
    Top = 136
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label14: TLabel
    Left = 184
    Top = 160
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label15: TLabel
    Left = 184
    Top = 184
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label16: TLabel
    Left = 184
    Top = 208
    Width = 11
    Height = 18
    Caption = 'V'
  end
  object Label17: TLabel
    Left = 48
    Top = 40
    Width = 36
    Height = 18
    Caption = 'CH0:'
  end
  object Label18: TLabel
    Left = 48
    Top = 64
    Width = 36
    Height = 18
    Caption = 'CH1:'
  end
  object Label19: TLabel
    Left = 48
    Top = 88
    Width = 36
    Height = 18
    Caption = 'CH2:'
  end
  object Label20: TLabel
    Left = 48
    Top = 112
    Width = 36
    Height = 18
    Caption = 'CH3:'
  end
  object Label21: TLabel
    Left = 48
    Top = 136
    Width = 36
    Height = 18
    Caption = 'CH4:'
  end
  object Label22: TLabel
    Left = 48
    Top = 160
    Width = 36
    Height = 18
    Caption = 'CH5:'
  end
  object Label23: TLabel
    Left = 48
    Top = 184
    Width = 36
    Height = 18
    Caption = 'CH6:'
  end
  object Label24: TLabel
    Left = 48
    Top = 208
    Width = 36
    Height = 18
    Caption = 'CH7:'
  end
  object Image1: TImage
    Left = 72
    Top = 240
    Width = 99
    Height = 45
    AutoSize = True
    Picture.Data = {
      07544269746D6170F2340000424DF23400000000000036000000280000006300
      00002D0000000100180000000000BC3400000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC3000000000000000000D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC20000000000000000
      00D4CBC2D4CBC2DAD3CBD5CCC3D4CBC2DBD3CCD4CCC3DAD2CADBD3CBD9D1C9D7
      CFC6DAD3CBD5CCC3D4CBC2D8D0C8DBD3CCDAD2CAD5CDC4D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D8D0C8DBD3CBD9D1C9D6CDC5D9D1C9D6CDC4D6CDC5D9D1C9D5CD
      C4DBD4CCD8D0C8DAD2CAD4CBC2D4CBC2D4CBC2DAD2CADBD4CCD9D1C9D4CBC2D6
      CDC5DBD4CCD9D2CAD4CBC2D8D0C7D7CFC6D4CBC2DBD4CCD7CEC6D8D0C7DBD3CC
      D4CBC2DBD4CCD5CCC3D4CBC2DBD3CCD9D1C9DAD3CBD4CCC3DBD4CCD4CBC2D5CC
      C4DBD3CCDAD3CBD4CCC3D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D9D1C9DBD4CCD8
      CFC7D8CFC7DAD2CAD5CDC4D7CFC6D8D0C8D5CCC4DAD2CBD5CCC3DAD3CBDBD3CC
      D7CFC7D5CCC3DBD3CBD4CBC2D5CDC4DAD2CAD4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2000000000000000000D4CBC2D4CBC27B5C42C7BBB0D7CFC7735438D1
      C7BD725235AC9A89795A3FBDAEA178593ECABEB3D7CEC675563AA18C79735337
      C1B4A8D4CBC2D4CBC2D4CBC2D4CBC2D8D0C8785A3EA08B777A5C41BAAB9D896E
      57BDAEA1B8A89A8D735C9E8875886D558E755E84674FD4CBC2D4CBC2C2B5A979
      5B40A08A7777583CD0C6BD8A6F58A6917F7C5F44D3CAC1A08A77AB9988D4CBC3
      705033C1B3A78C735C6F4E31D8CFC7704F32C7BBB0BCAEA07D5F45A693816E4D
      30D6CDC56D4C2ED7CEC69B846F99826D8A7159B2A191D4CCC3D4CBC2D4CBC2D4
      CBC2CBC0B6785A3FA28D7A856A52A28E7B83674FC1B4A7AA97859D8773C3B6AA
      7F6248C8BDB27151359B8570866A52CCC1B676563BD8CFC7C2B4A880634AD4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC27E
      6046CABFB4DAD3CB77583DD0C6BD735437AB99887E6046CDC2B77B5C42CABFB4
      B8A89A8A7058DAD3CB896E56C7BBAF8C725B8E745DC5B9ADD4CBC2DAD2CA6B49
      2BDED7D0917962BBAC9F8C725BBDAFA2B9AA9B9279636A4729DAD2CBC5B8AC86
      6A52D4CBC2D4CCC3B4A395C0B2A5DBD4CC876C54A89483745439D6CEC6A79482
      A89483A28C7AAC9B8AD4CCC37A5C40D5CCC47353387B5E44BFB1A4B2A1929880
      6CC6B9AE7A5C41BCADA06F4E31DDD6CF715033DAD2CA7B5D43A69280A99584B0
      9F8FD5CCC3D4CBC2D4CBC2D4CBC2A18D79A18C79D0C5BB9E8874A5917F866A53
      C1B4A8AB98879F8975C4B7AB82654CC9BDB283674EDAD3CB6A4729D0C6BD795B
      40DAD3CBC5B8AC83674ED4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC200000000
      0000000000D4CBC2D4CBC27E60467E614780644A715034D0C6BC9C8672CEC4BA
      7B5D42CCC1B67C5F45C1B3A6C1B3A77F6248E1DBD5806349C3B6AAC3B5A9C3B6
      AAD1C7BDD4CBC2DAD2CA6B492BDCD5CE907761BBAC9F8C725BB9AA9BBBAC9E90
      7761705033D2C8BFBEAFA2866B53D4CBC2D4CBC2D1C7BE8E745D7D6046A08A77
      D3CAC1715134DBD4CC9C8572B4A495A48F7DAF9E8DD9D1C97A5C41D9D2CA7454
      38AD9B8B896E57D1C8BE735337BBAD9FBBAC9ECABEB36B492CDDD6CE6E4C2FD8
      CFC77E6147BCAD9FAE9B8B927964D7CEC6D1C7BED0C6BCCFC5BB9B8470AA9785
      BEB0A3AD9B8BC4B8AC876B53BFB1A4AC9A899A846FC8BCB181654BC9BDB27D60
      46DDD5CE6C4A2DD0C6BC71503480644A7E604683674ED4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC27E6046CCC1B7DDD6CE
      77583DCDC3B8A4907D967E699C8672D7CEC69279639E8875BDAEA199826E957D
      687E6146C2B5A8D4CBC2D4CBC2D4CBC2D4CBC2D8D0C8856951DAD3CBA18C79C2
      B4A89F8976A79482896E56BFB1A4BCAD9F8A6F589D8773866B53D4CBC2D5CCC3
      99816D9F8A76DBD4CCA99684D6CEC5B5A49592796399816DD5CCC3856A518B70
      58977F6A75563AA38E7CA79482D5CBC3886D55D3CAC08F755FD0C6BC957D6893
      7B65B3A192DAD2CA8D735D907660BEB0A3957C67937B65C9BEB3D9D1C9B1A090
      BAAA9CB2A191AB99889A826ED7CFC7B8A99AB6A7989A8370A5917F896F57B3A1
      928D735DAF9E8DC6BAAF7A5B41927963A99583CBBFB4795B40DDD6CFC7BBAF83
      674ED4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2
      D4CBC278593EC7BBAFD7CFC7715034CCC0B6D5CCC3D7CFC6D5CCC4D4CBC2D7CE
      C6D5CDC4D5CCC3D6CDC4D9D2CA7F6248C1B3A7D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D7CFC7D4CBC2D6CEC5D5CCC3D6CEC5D5CCC3D7CFC6D4CBC2D4CBC2D7CFC6
      BFB1A481654BD4CBC2D4CBC2C7BBB07F62488C715A82664DD6CDC5D4CBC2D7CF
      C6D5CDC4D4CBC2B9A99C7D5F45D7CFC6896E56D7CEC6D6CDC4D4CBC2D7CFC6D4
      CBC2D7CEC6D4CBC2D6CDC5D7CFC6D4CBC3D4CBC2D7CFC6D6CEC5D4CBC2D6CEC5
      D6CEC5C1B4A8BAAB9EB4A495BBAC9EB3A293D4CBC3866A518D735C80644ACABF
      B4D6CEC5D5CCC3D7CFC6D4CBC2D7CFC6D5CCC3C5B8AD7A5C41DAD2CAD5CCC3C9
      BDB2735337D8D0C7C1B4A77E6046D5CCC3C5B8ACBCADA0D6CEC5D4CBC2D4CBC2
      000000000000000000D4CBC2D4CBC2DAD2CAD5CCC3D4CBC2DAD3CBD5CCC3D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D9D1CAD5CCC4D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D5CDC4D9D1C9D4CBC2D4CBC2D4CBC2D9D1C9DAD3
      CBD8D0C7D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D5CCC3DAD3CBD4CBC2D8CFC7D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2C5B8ACE8E2DEEAE5E1AE9D8DBBAC9EB3A293D4CB
      C2D7CFC7DAD3CBD9D1C9D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D5
      CCC3DAD2CAD4CBC2D4CBC2D5CCC3DAD2CBD4CBC2D5CCC4DAD3CBB8A899D3CAC1
      EEEAE7C6B9AED4CCC3D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2CFC5BBE6E1DCF9F9F7F7F5
      F4B1A091BBAC9EB4A495D6CEC5D6CDC5D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D7CEC6
      D7CFC6BAAB9DE7E2DDEBE7E4F8F6F4F8F6F4C1B3A7D4CBC20000000000000000
      00D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D5CC
      C3B8A799F1EEEBF6F5F3FFFFFFB1A090BBAC9EA38E7CB5A596B7A698BFB1A4D2
      C8BFD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D5CCC3C8BBB0BFB1A4B4A294B6A597D4CAC1F0EDEAF8F7F5F9F8F6F0EDEBE5DF
      DAD6CEC5000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D7CFC7C7BAAFE4DED8EEEAE6FEFEFEB1A090BBAC9EC4
      B7AAEAE5E1E3DDD7E1DAD4B6A698CDC3B9D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D5CCC3BCADA0D0C5BCE2DCD6E7E3DEEEEAE7F1EEEBF2EF
      ECF4F2F0F0EDEBE6E0DBDAD2CAD6CDC5000000000000000000D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2B7A798D0C5BCE3
      DDD7F5F3F0B1A091BBAC9EC9BEB2F8F6F5F0EDEAE9E4E0E3DDD7BCADA0D6CEC5
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2CABEB3D5CDC4E7E2DEF0ED
      E9F8F6F4F9F8F6FAF9F8B9AA9BEFEBE7E5E0DADCD4CDA79382D4CBC200000000
      0000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2C8BCB1C6B9ADE8E3DEB2A191BBAC9EC8BBB0F9F8F6F9F8F6
      F8F6F5F1EEEACABEB3D7CEC6D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2C6BAAEF2F1EDF5F3F1F9F9F7F9F8F6F6F4F3F3F1EFBEAFA1E7E2DDD3C9C0AD
      9A8AD5CDC4D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D9D1C9B2A192B4A495
      BBAC9EC0B3A6F1EDEAF6F4F2F9F8F6F9F8F6D5CCC3D6CEC5D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D6CDC5B8A89AFAF9F7F9F8F6F6F4F3F1EEEBEAE7E1E7
      E1DCDAD1CABBAC9EC4B7ABD4CBC2D4CBC2D4CBC2000000000000000000D4CBC2
      D4CBC2D2C8BFCEC3B9D3CAC1D4CBC2CEC4BAD2C8BFD4CBC2CFC4BACEC3B9D4CB
      C2D5CCC3D1C8BECEC3B9D2C9BFD4CBC3D4CBC2CFC5BBCEC3B9D4CBC2D4CBC2D4
      CBC2D5CCC3CEC4BACEC4BAD4CCC3D4CBC2D4CBC2D5CCC3CFC5BBCEC4BAD4CBC2
      D4CBC2D3C9C0CEC3B9D1C8BED4CBC2D0C6BCCEC3B9D4CBC2D4CCC3CEC4B9D1C7
      BDD3CAC1CEC3B9D1C8BED1C7BECEC3B9D3CAC1D4CBC2D4CBC2CEC4BACEC3B9D4
      CBC2D4CBC2D2C8BFCEC4B9D1C7BDD4CCC3D4CBC2D5CCC3D1C7BDCEC3B9D2C9BF
      D4CCC3D4CBC2D9D1C9B3A292BBAC9EBCAD9FE6E1DCEAE6E1F1EDEBF6F4F2CBBF
      B4D7CFC6D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2C9BEB3FCFAFAF1
      EEEBEAE7E2E7E1DCE2DCD7DDD6CFCCC0B6D8D0C7D4CBC2D4CBC2D4CBC2D4CBC2
      000000000000000000D4CBC2D4CBC2AA9786704F32C6B9ADD9D1CA6F4E319780
      6BD9D1C97B5D42694729D8D0C8A895846E4C2F704F326C4B2DB8A99BD8D0C783
      674F6B492BD3CAC1D4CBC2D5CDC481644B704F33704F3278593ED2C9C0D4CBC2
      846950704F32704F3276573BD3C9C1C0B2A5704F32A18C79D5CCC38C715A6F4F
      32D9D2CA9A84707050336F4F32A38E7B705033C9BDB2A18C79705033C5B9ADD4
      CBC2D5CDC47353376D4B2ED3CAC1BDAEA0704F32704F326F4E31AB9887D5CCC3
      A08A776E4D30704F326D4C2FB2A091D5CCC3D9D1C9B3A292BBAC9EB1A090DBD3
      CCE2DCD7E6E1DCEEEBE7BEAFA3D4CBC2D4CBC2D3CAC1CEC4BACEC4BACFC5BBD4
      CCC3D4CBC2C4B7ABEEEBE7E7E1DCE3DCD7DDD6CFD7CEC6B4A395D9D2CAD4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2AB98887252
      36C6BAAEB8A899725235745539DAD2CA7D5F466C4A2DDAD2CB6F4F327C5F44D8
      CFC77B5D436D4D2FDBD3CC856A516D4C2FD3CAC1D4CBC2A89482725135A38F7C
      BEB0A47050338F765FB19F907252369F8976C1B2A6705033896F57C0B3A67252
      36A38E7BD5CCC38E745D725236D5CCC471503477583CD6CDC576573B735337D5
      CDC4A38D7B735337C6B9AED4CBC2D5CDC475563A704F32D6CEC576573C705033
      D5CDC47F62486F4E31D2C8BF7353377F6348D7CFC880634A6E4C2FCDC2B8D9D1
      C9B3A292BBAC9EB6A697AD9B8BBFB1A4D8D0C8E2DCD7B5A496C8BCB1B1A090C7
      BAAEFFFFFEFDFCFBF2F0EDB7A798B2A192D4CBC2B3A393D9D0C9CCC1B7A38E7C
      C4B7ABD5CCC3D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC20000000000000000
      00D4CBC2D4CBC2AB9888725236C6BAAE8E755F7454386F4D31D2C8BF7D5F466C
      4A2DBEB1A3715034AA9887D4CBC2C5B8ACBBAB9DD6CDC5856A516D4C2FD3CAC1
      D6CEC68E755E6F4E31CEC2B8D9D1C9704F32866B5399836E704F32D1C7BED4CB
      C2BAAA9CC0B1A5C1B3A6725236A38E7BD5CCC38E745D725236D5CDC470503379
      5A40D4CBC3A08A78735337D5CDC4A38D7B735337C6B9AED4CBC2D5CDC475563A
      704F32D8D0C77353378F755FD4CBC2CABFB5BBAC9ED2C9BFBCAD9FCABDB3D1C8
      BF7D60466F4E31C8BCB1D9D1C9B3A292BBAC9EB3A293D4CBC2D5CCC3D5CDC4D5
      CCC4CABFB4D0C6BDF6F4F3F9F8F6F9F8F6F9F8F6F9F8F6F7F5F4F6F3F2B6A698
      D6CDC5D5CDC4D5CCC3D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2000000000000000000D4CBC2D4CBC2AB9888725236C8BCB07E6147A2
      8E7B715135C7BBAF7D5F466C4A2DB8A89A7151347352367252367252366F4E31
      C5B9AD856A516D4C2FD3CAC1D7CFC6896E576E4D30D2C9C0D4CBC2D4CBC2D6CE
      C59076607353377252367252367252367C5E44C4B7AB725236A38E7BD5CCC38E
      745D725236D9D2CAA18C7973533875573B917963735337D5CDC4A38D7B735337
      C6B9AED4CBC2D5CDC475563A704F32D8D0C87252367353377252367252367252
      36C2B5A8B2A092725236735337735337A18C79D5CDC4D9D1C9B3A292BBAC9EB3
      A293D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2BDAFA2FBFAF9F9F8F6F9F8F6F9F8F6
      F9F8F6F8F7F6C9BDB2D6CDC5D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2AB
      9888725236CABFB477583CC2B5A97C5D43B1A0907E60466C4A2DBFB1A4715034
      AA9786D3CAC1977F6A6F4E31CABEB3856A516F4E31C8BDB2D6CEC59178626F4E
      31CBC0B6D8D0C884684F977F6B99826D704F32D0C6BDD6CEC56C4A2D7F6148C3
      B6AA725236A38E7BD5CCC38E745D725236D9D1C9D4CCC3D4CBC2C3B5AA735437
      735337D5CDC4A38D7B735337B2A292D4CBC2D5CDC475563A704F32D8D0C77353
      378E755ED4CBC2AD9A8A725135CABEB3735336705033C6B9ADD4CBC2D5CCC3D4
      CBC2D9D1C9B3A292BBAC9EB3A293D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D7CFC6
      C5B8ADFDFDFBB3A292B4A495CEC4B9EDE9E6C1B3A7D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC200000000
      0000000000D4CBC2D4CBC2AB9888725236C0B2A66F4E32CABFB48468508E755E
      7F62486C4A2DDCD4CD7251357B5E43D9D1C97D5F456D4C2EDAD3CB856A517353
      3774543875563AB2A29272513598806BB6A5967150348E755EB5A5967251359D
      8773C4B7AC705033886E56C1B3A67353377E6046D6CDC4735437725236DAD2CA
      77583C77583DD5CCC48C715A735337D5CDC4A38D7B73533773533676573CD2C9
      BF75563A704F32D5CDC477583D705033D3CBC181654B704F32D1C8BE7353377A
      5D42D7CEC6856A516F4E31C9BEB3D9D1C9B3A292BBAC9EB3A293D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2C8BCB0CDC2B7F5F3F1F5F3F1E8E3DFB09F8FD7CF
      C6D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2AB98887252369A836F
      6D4C2FD1C7BE9E8874704F327E61476C4A2DD8CFC7B7A7986E4E307150346D4C
      2FB8A899D8D0C784684F6C4A2DA08B786F4E31DCD4CD927963704F3371503479
      5B40D3CAC1D5CCC4927A6470503371503476573BD4CBC2C0B2A5704F33A18B79
      6D4C2F7150347F6248D5CCC4CABEB36E4D307150347050338B7058D4CBC2A18C
      7A715134C1B3A7715034D2C8BF7353386D4C2FD3CAC1CCC0B571513571503370
      4F32AA9787D5CCC3AE9C8C704F32715033704F32A28D7BD5CCC3D9D1C9B3A292
      BBAC9EB3A293D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D7CFC7C7BBAFF7F5F4CABE
      B3B5A595E5E0DBF6F5F3B3A394D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2
      D4CBC2AB988872523674553977583DD6CDC4BFB1A47151347354386C4A2DD7CF
      C7D4CBC2D2C9C0CFC5BCD2C9BFD4CBC2D4CBC2D0C7BDCFC5BBD5CCC3D0C6BCD4
      CBC2D4CCC3D1C7BDD0C6BCD4CBC2D4CBC2D4CBC2D5CCC3D0C7BDD0C6BCD4CBC2
      D4CBC2D3CAC1CFC5BCD2C9C0D2C9C0D0C6BCD4CBC2D4CBC2D4CBC2D3CAC1CFC5
      BCD1C7BDD5CCC3D4CBC2D2C8BFD0C5BCD4CBC2D1C7BDD4CBC2C9BDB2C8BCB1D4
      CBC2D4CBC2D3CAC1D0C6BCD1C8BED4CBC2D4CBC2D4CBC2D2C9BFD0C5BCD1C7BE
      D4CBC3D4CBC2D9D1C9B3A292BBAC9EB3A293D4CBC2D4CBC2D9D1C9A18C7ADCD5
      CDC4B7ABF7F5F4F9F7F6EEEAE7DAD2CBF5F2F0F7F5F3F6F4F2B09E8EB8A89AC7
      BAAFD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      000000000000000000D4CBC2D4CBC2AB98887252367353379D8874D5CCC3DAD2
      CA7252357353376C4A2DD7CFC7D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D5CDC47454396E4D30D3CAC1D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D9D1C9B3A292BBAC9EB3A293D4CB
      C2D5CDC4AD9A8AAB9987A99685E2DCD6F8F7F5F9F8F6F9F8F6F9F8F7F9F8F6F9
      F7F6FAF8F7C7BBB0947B66AA9686DBD3CBD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2CDC2B8C3B6
      A9C3B6A9CEC4BAD4CBC2D5CCC3C4B7ABC3B6A9C2B4A8D5CCC3D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2C3B6AAC2B5A8D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D9D1
      C9B3A292BBAC9EB3A293D4CBC2D9D2CAA18B78A99684A28D7BFFFFFFFFFFFFFF
      FFFFFDFDFCFDFDFCFEFEFDFFFFFEFFFFFEE3DDD7967F69B3A393AD9B8BD4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC20000000000000000
      00D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D5CDC4B4A394B6A597D7CEC6D4CBC2D4CBC2D6CDC5C5B9ADB19F
      90CBBFB4D5CCC3D4CBC2D5CCC3CBC0B6B3A293D7CEC6B09E8FB5A495D4CBC2D8
      D0C8BBAC9EB1A091D2C9BFD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D9D1C9B3A292BBAC9EB3A293D4CBC2BBAC9FB2A2929B
      836FC8BCB18D735CC1B4A7CEC3BAE3DCD7E6E0DCD4CAC1C5B9AE957E68D9D1C8
      957E69AA97869D8772D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2B4A2937151356E4D306F4E31735337BAAB
      9DD5CDC49F8976704F326B492B715034A28E7CD4CBC2BFB1A4704F326F4E3177
      583C7050337B5D42D2C8BF795A3F6F4F326B492C705033B4A394D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D9D1C9B5A495BBAC9EB3
      A293D4CBC2B8A89AB0A08FA38E7BBDAFA1D7CEC6D3CAC1D9D1CAE3DCD6E6E1DB
      DED7D0D5CBC3DBD3CCBEAFA3866B53B09F8E9D8773D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2DAD2CA76573C7050
      33C8BBB0BBAC9E704F3282664DD6CDC56D4B2E7F6249DAD2CB704F32795B40DA
      D2CA856951725236C2B5A9B1A0917353377C5F45B8A99A735337A79281D4CAC2
      6C4B2D6F4E31D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D6CEC5BAAA9CBCAD9FB9AA9CD4CBC2C2B5A9AB9987C2B4A8B09F8FB19F8F
      D7CEC7EBE6E2F6F4F2F9F8F6F0EDEAE6E1DCBFB0A3A99684C0B2A5B6A6979C86
      71D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC200000000
      0000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2C9BEB36E4D30886D55D7CFC7D9D1C9715134715034CDC3B86F4E328A
      6F58D7CFC7876B53715134DDD6CF6E4D3077583DD8D0C8CCC1B67151357D5F45
      A08A77735336C1B3A7C9BCB1C2B4A8C3B5A8D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2CCC1B69F8976D7CFC6D4CBC2D7CFC7
      A18C79937A65B1A090D1C7BEE2DCD7EAE6E2F6F3F1F9F8F6F0EDEAE6E0DBDDD6
      CFBBAB9D9B8571917962C6B9ADD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2C1B3A7704F328F765FD6CEC5D5CCC4B9
      AA9CB4A494C8BCB1704F328B7059D7CFC6896F57705033DDD6CF6C4A2D78593E
      D8D0C8CDC2B77151347D5F459C86727353376A47296846286F4F32704F33D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D6CEC6D4CBC2D4CBC2D4CBC2D5CCC381644BBDAEA1B8A89AE0D9D3EEEAE6F8F7
      F5F9F8F6F3F1EFE9E4DFD0C6BDAB9887876C54A99685D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2BFB0A470
      4F32917862D6CDC5D4CBC2D4CBC2D4CBC2CEC3B96D4C2F866B53D9D2CA795B40
      755539DCD4CD7B5D42735337DCD5CECBC0B57252367D5F45AF9C8C735336CBBF
      B5DAD2CA715034745438D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D7CFC799826EB9A9
      9BECE8E4D0C5BBC9BDB2D0C6BCD3C9BFCCC0B6CABFB4D2C7BEE7E2DD977F6ADC
      D5CED4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2C2B6A96F4F328D735CD6CEC5D3C9C0BEB0A3C2B5A9D8D0C8
      82654C745439A28D7A70503382664CD6CEC6A9958473533780634978593E7353
      377C5F44CFC5BB6E4D307B5E43A18C7A735336886D55D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2B3A29299826DFCFBFBF6F4F2FBFAFAFBFAF9FBF9F9FBFAFAF8
      F6F5F6F4F2CEC3B98A7058D7CEC6D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D1C7BD6D4C2E82654CD9D1C9
      C9BEB26B492C81654CD7CFC6D0C6BC917862856850917862D0C6BDD4CBC2D3CA
      C0937B65866A52AF9D8D7150347C5F44D4CBC2BDAFA28B705A85695197806BD7
      CEC6D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2C7BBB09E8875CCC1B7F5F3F1F4
      F2F0F5F3F1F5F3F1F4F2F0F4F1EFEDE8E5AF9D8DA6917FD4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC20000000000000000
      00D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D8D0C783674E704F33A99684967E6972523698806CD4CCC3D4CBC2D5CDC4D8CF
      C7D6CDC5D4CBC2D4CBC2D4CBC2D5CDC4D7CFC7CCC1B77151347C5F44D4CBC2D4
      CBC2D7CEC6D7CFC7D5CCC3D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D6
      CDC5B2A1929D8774D0C5BCEFEBE9F5F3F1F4F1EFF8F6F5D5CCC4BAAB9D957D68
      DBD3CBD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2C7BBB081644B704F32715034886D56D6CD
      C5D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2CC
      C1B76D4B2E795A3FD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D7CFC6BCADA0AA9785B6A597C1B4A7CEC3B9
      B2A192C6B9AD9B8471DAD3CBD4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D7CF
      C7DBD4CCDBD3CCD6CEC5D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D5CCC3DBD4CCDAD3CBD4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D5CCC3
      C8BCB19C867299836F9E8874957D68B7A698D8D0C8D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC200000000
      0000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D7CEC6D8D0C7D8D0C8D8D0C7D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2000000000000000000D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2000000000000000000D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      000000000000000000D4CBC3D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CB
      C2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4
      CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2D4CBC2
      D4CBC2D4CBC2D4CBC2D5CCC30000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000}
  end
  object Label25: TLabel
    Left = 32
    Top = 8
    Width = 182
    Height = 18
    Caption = 'Supports IOWarrior 24, 40'
  end
  object Kicker: TTimer
    Enabled = False
    Interval = 300
    OnTimer = KickerTimer
    Left = 48
    Top = 232
  end
end
