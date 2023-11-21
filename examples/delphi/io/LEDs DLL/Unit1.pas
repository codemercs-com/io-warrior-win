unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Buttons,
  iowkit;

type
  TMainForm = class(TForm)
    WorkTimer: TTimer;
    Bits: TLabel;
    LED7: TSpeedButton;
    LED6: TSpeedButton;
    LED5: TSpeedButton;
    LED4: TSpeedButton;
    LED3: TSpeedButton;
    LED2: TSpeedButton;
    LED1: TSpeedButton;
    LED0: TSpeedButton;
    DllVersion: TLabel;
    IOWInfo: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure WorkTimerTimer(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  public
    LEDs: array [0..7] of TSpeedButton;
    IOWarrior: IOWKIT_HANDLE;
    Pid: ULONG;
  published
    procedure LEDClick(Sender: TObject);
  end;

var
  MainForm: TMainForm;

implementation

uses
  Math;

{$R *.dfm}

// OrdToBinary function taken from the Jedi Code Library

function OrdToBinary(Value: Byte): string;
var
  I: Integer;
begin
  SetLength(Result, 8);
  for I := Length(Result) - 1 downto 0 do
  begin
    Result[I + 1] := Chr(48 + (Value and $00000001));
    Value := Value shr 1;
  end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
var
  I: Integer;
  Buffer: array [0..16] of WideChar;
begin
  // place the SpeedButtons in an array for indexed access
  for I := Low(LEDs) to High(LEDs) do
    LEDs[I] := TSpeedButton(FindComponent(Format('LED%d', [I])));

  LoadIowKitAPI;
  IOWarrior := IowKitOpenDevice;
  if Assigned(IOWarrior) then
  begin
    IowKitGetSerialNumber(IOWarrior, Buffer);
    IOWInfo.Caption := Buffer;
    Pid := IowKitGetProductId(IOWarrior);
    WorkTimer.Enabled := True;
  end;
  for I := Low(LEDs) to High(LEDs) do
    LEDs[I].Enabled := Assigned(IOWarrior);
  LEDClick(nil);
  DllVersion.Caption := IowKitVersion;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
begin
  WorkTimer.Enabled := False;
  IowKitCloseDevice(IOWarrior);
  UnloadIowKitAPI;
end;

procedure TMainForm.WorkTimerTimer(Sender: TObject);
var
  I: Integer;
  Report: IOWKIT56_IO_REPORT;
  Size: Integer;
  S: string;
begin
  if Assigned(IOWarrior) then
  begin
    case Pid of
      IOWKIT_PID_IOW40:
        Size := IowKitReadNonBlocking(IOWarrior, IOW_PIPE_IO_PINS, PChar(@Report), IOWKIT40_IO_REPORT_SIZE);
      IOWKIT_PID_IOW24:
        Size := IowKitReadNonBlocking(IOWarrior, IOW_PIPE_IO_PINS, PChar(@Report), IOWKIT24_IO_REPORT_SIZE);
      IOWKIT_PID_IOW56:
        Size := IowKitReadNonBlocking(IOWarrior, IOW_PIPE_IO_PINS, PChar(@Report), IOWKIT56_IO_REPORT_SIZE);
    else
      Size := 0;
    end;
    if Size > 0 then
    begin
      S := '';
      for I := 0 to Size - 2 do
        S := Format('%u) ', [I]) + OrdToBinary(Report.Bytes[I]) + #13#10 + S;
      Bits.Caption := S;
    end;
  end;
end;

procedure TMainForm.LEDClick(Sender: TObject);
var
  LEDByte: Integer;
  I: Integer;
  Report: IOWKIT56_IO_REPORT;
begin
  if not Assigned(IOWarrior) then
    Exit;

  // initialize report to not interfere with input
  FillChar(Report, IOWKIT56_IO_REPORT_SIZE, $FF);
  Report.ReportID := 0;
  // the LEDs are connected to different ports
  case Pid of
    IOWKIT_PID_IOW40:
      LEDByte := 3;
    IOWKIT_PID_IOW24:
      LEDByte := 0;
    IOWKIT_PID_IOW56:
      LEDByte := 6;
  else
    LEDByte := 0;
  end;

  for I := Low(LEDs) to High(LEDs) do
    // translate SpeedButton state into correct bit in the byte
    // IO-Warrior uses negative logic
    if LEDs[I].Down then
      // set the bit to 0 to switch the LED on
      Report.Bytes[LEDByte] := Report.Bytes[LEDByte] and not (1 shl I)
    else
      // set the bit to 1 to switch the LED off
      Report.Bytes[LEDByte] := Report.Bytes[LEDByte] or (1 shl I);

  // write the bits to the IO-Warrior
  case Pid of
    IOWKIT_PID_IOW40:
      IowKitWrite(IOWarrior, IOW_PIPE_IO_PINS, PChar(@Report), IOWKIT40_IO_REPORT_SIZE);
    IOWKIT_PID_IOW24:
      IowKitWrite(IOWarrior, IOW_PIPE_IO_PINS, PChar(@Report), IOWKIT24_IO_REPORT_SIZE);
    IOWKIT_PID_IOW56:
      IowKitWrite(IOWarrior, IOW_PIPE_IO_PINS, PChar(@Report), IOWKIT56_IO_REPORT_SIZE);
  end;
end;

end.
