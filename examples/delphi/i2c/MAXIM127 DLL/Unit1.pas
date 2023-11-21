unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls,
  iowkit;

type
  TForm1 = class(TForm)
    Kicker: TTimer;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Image1: TImage;
    Label25: TLabel;
    procedure FormDestroy(Sender: TObject);
    procedure KickerTimer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  public
    IOWIIC: IOWKIT_HANDLE;
    Pid: ULONG;
    Values: array [0..7] of TLabel;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var
  I: Integer;
  Report: IOWKIT_SPECIAL_REPORT;
begin
  Values[0] := Label1;
  Values[1] := Label2;
  Values[2] := Label3;
  Values[3] := Label4;
  Values[4] := Label5;
  Values[5] := Label6;
  Values[6] := Label7;
  Values[7] := Label8;

  LoadIowKitAPI;
  IOWIIC := IowKitOpenDevice;
  Pid := IowKitGetProductId(IOWIIC);

  if Assigned(IOWIIC) and ((Pid = IOWKIT_PID_IOW40) or (Pid = IOWKIT_PID_IOW24)) then
  begin
    // IOW found, enable IIC
    FillChar(Report, SizeOf(Report), 0);
    Report.ReportID := $01;
    Report.Bytes[0] := $01; // enable IIC
    IowKitWrite(IOWIIC, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);
    // enable reader timer
    Kicker.Enabled := True;
  end
  else
    for I := Low(Values) to High(Values) do
      // no IOW, show bogus value
      Values[I].Caption := '?,??';
end;

procedure TForm1.FormDestroy(Sender: TObject);
var
  Report: IOWKIT_SPECIAL_REPORT;
begin
  // if IOW found
  if Assigned(IOWIIC) and ((Pid = IOWKIT_PID_IOW40) or (Pid = IOWKIT_PID_IOW24)) then
  begin
    // disable IIC
    FillChar(Report, SizeOf(Report), 0);
    Report.ReportID := $01;
    // Report.Bytes[0] := $00;
    IowKitWrite(IOWIIC, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);
  end;
  IowKitCloseDevice(IOWIIC);
  UnloadIowKitAPI;
end;

procedure TForm1.KickerTimer(Sender: TObject);
var
  I: Integer;
  Report: IOWKIT_SPECIAL_REPORT;
  N: Integer;
begin
  if Assigned(IOWIIC) and ((Pid = IOWKIT_PID_IOW40) or (Pid = IOWKIT_PID_IOW24)) then
  begin
    for I := 0 to 7 do
    begin
      FillChar(Report, SizeOf(Report), 0);
      Report.ReportID := $02; // ReportID IIC write request
      Report.Bytes[0] := $C2; // 2 bytes with IIC Start and Stop
      Report.Bytes[1] := $50; // MAXIM127 address byte = ADR 0, write
      // MAXIM127 control byte
      // START, I = Channel index, +/-10 V = RNG 1 and BIP 1, normal operation
      Report.Bytes[2] := $8C or (I shl 4);
      IowKitWrite(IOWIIC, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);
      // swallow ACK report
      IowKitRead(IOWIIC, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);

      FillChar(Report, SizeOf(Report), 0);
      Report.ReportID := $03; // ReportID IIC read request
      Report.Bytes[0] := $02; // 2 bytes
      Report.Bytes[1] := $51; // MAXIM127 address byte = ADR 0, read
      // MAXIM127 control byte
      // START, I = Channel index, +/-10 V = RNG 1 and BIP 1, normal operation
      Report.Bytes[2] := $8C or (I shl 4);
      IowKitWrite(IOWIIC, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);
      // read answer containing voltage value
      IowKitRead(IOWIIC, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);

      // extract bytes of value
      N := (Report.Bytes[1] shl 8) or Report.Bytes[2];
      // value is upper 12 bits of 16 bits
      N := (N shr 4);
      // value is 12 bit signed!
      // We need to add the upper twos complement sign bits for the Integer.
      // This is a sign extension from 12 bit to 32 bit.
      if (N and $800) <> 0 then
        N := N or Integer($FFFFF000);
      // value now is a signed integer with 2047 = 10 V and -2047 = -10 V
      Values[I].Caption := Format('%.2f', [N * 10.0 / 2048.0]);
    end;
  end;
end;

end.
