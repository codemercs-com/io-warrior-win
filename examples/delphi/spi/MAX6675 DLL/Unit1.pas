unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, TeEngine, Series, TeeProcs, Chart,
  iowkit;

const
  cCodeMercsVID = $07C0;
  cIOW24PID = $1501;

type
  TSPIReport = packed record
    ReportID: Byte;
    case Boolean of
    False:
     (Length: Byte;
      Value: array [0..1] of Byte;);
    True:
      (Bytes: array [0..63] of Byte;);
  end;

  TForm1 = class(TForm)
    Temperature: TLabel;
    Kicker: TTimer;
    Chart1: TChart;
    Series1: TLineSeries;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure KickerTimer(Sender: TObject);
  public
    IOWSPI: IOWKIT_HANDLE;
    Pid: ULONG;
    Counter: Integer;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var
  Report: TSPIReport;
begin
  LoadIowKitAPI;
  IOWSPI := IowKitOpenDevice;
  Pid := IowKitGetProductId(IOWSPI);
  if IOWSPI <> nil then
    if Pid = IOWKIT_PID_IOW24 then
    begin
      // IOW24 found, enable SPI
      FillChar(Report, SizeOf(Report), 0);
      Report.ReportID := $08;
      Report.Bytes[0] := $01; // enable SPI
      Report.Bytes[1] := $07; // mode /CPOL, CPHA, 62.5 KBit
      // the chip can even be contacted at 2 MBit, but this may cause
      // occasional corrupt data
      IowKitWrite(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);
      // init chart
      Chart1.Series[0].Clear;
      Counter := 0;
      // enable reader timer
      Kicker.Enabled := True;
    end
    else
    if Pid = IOWKIT_PID_IOW56 then
    begin
      // IOW56 found, enable SPI
      FillChar(Report, SizeOf(Report), 0);
      Report.ReportID := $08; //SPI-Mode
      Report.Bytes[0] := $01; //Enable SPI-Mode
      Report.Bytes[1] := $01; // mode MSB first, /CPOL, CPHA
      Report.Bytes[2] := $00; // 93.75 KBit
      // the chip can even be contacted at 2 MBit, but this may cause
      // occasional corrupt data
      IowKitWrite(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT56_SPECIAL_REPORT_SIZE);
      // init chart
      Chart1.Series[0].Clear;
      Counter := 0;
      // enable reader timer
      Kicker.Enabled := True;
    end;
end;

procedure TForm1.FormDestroy(Sender: TObject);
var
  Report: TSPIReport;
begin
  Kicker.Enabled := False;
  if IOWSPI <> nil then
  begin
    // disable SPI
    FillChar(Report, SizeOf(Report), 0);
    Report.ReportID := $08;
    // Report.Bytes[0] := $00; // disable SPI
    if Pid = IOWKIT_PID_IOW24 then
      IowKitWrite(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE)
    else
      IowKitWrite(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT56_SPECIAL_REPORT_SIZE);
  end;
  IowKitCloseDevice(IOWSPI);
  UnloadIowKitAPI;
end;

procedure TForm1.KickerTimer(Sender: TObject);
var
  Report: TSPIReport;
  Val: WORD;
begin
  // SPI transactions are always read/write pairs
  // write two bytes to SPI to trigger read of two bytes
  FillChar(Report, SizeOf(Report), 0);
  Report.ReportID := $09; // write SPI
  Report.Bytes[0] := $02; // two dummy bytes
  Report.Bytes[1] := $00; //flags for IOW56
  if Pid = IOWKIT_PID_IOW24 then
  begin
    if IowKitWrite(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE) =
      IOWKIT_SPECIAL_REPORT_SIZE then
    begin
      // read the two bytes triggered by the IowKitWrite
      IowKitRead(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT_SPECIAL_REPORT_SIZE);
      if Report.ReportID = $09 then
      begin
        // Bit 2 is high if the chip has no contact to thermo sensor
        // so we use the value only if bit is low
        if (Report.Value[1] and $4) = 0 then
        begin
          // extract temperature value
          Val := (Word(Report.Value[0]) shl 8) or Word(Report.Value[1]);
          // lower 3 bits are flags of no interest
          Val := Val shr 3;
          // temperature is in 1/4 degree Celsius
          Temperature.Caption := Format('%f °C', [Val / 4]);
          // display last 60 values in chart
          if Chart1.Series[0].Count > 60 then
            Chart1.Series[0].Delete(0);
          Chart1.Series[0].AddXY(Counter, Val / 4);
        end;
        Inc(Counter);
      end;
    end
  end
  else
  begin
    if IowKitWrite(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT56_SPECIAL_REPORT_SIZE) =
      IOWKIT56_SPECIAL_REPORT_SIZE then
    begin
      // read the two bytes triggered by the IowKitWrite
      IowKitRead(IOWSPI, IOW_PIPE_SPECIAL_MODE, @Report, IOWKIT56_SPECIAL_REPORT_SIZE);
      if Report.ReportID = $09 then
      begin
        // Bit 2 is high if the chip has no contact to thermo sensor
        // so we use the value only if bit is low
        if (Report.Value[1] and $4) = 0 then
        begin
          // extract temperature value
          Val := (Word(Report.Value[0]) shl 8) or Word(Report.Value[1]);
          // lower 3 bits are flags of no interest
          Val := Val shr 3;
          // temperature is in 1/4 degree Celsius
          Temperature.Caption := Format('%f °C', [Val / 4]);
          // display last 60 values in chart
          if Chart1.Series[0].Count > 60 then
            Chart1.Series[0].Delete(0);
          Chart1.Series[0].AddXY(Counter, Val / 4);
        end;
        Inc(Counter);
      end;
    end;
  end;
end;

end.
