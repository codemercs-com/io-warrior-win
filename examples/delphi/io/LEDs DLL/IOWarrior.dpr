program IOWarrior;

uses
  Forms,
  Unit1 in 'Unit1.pas' {MainForm},
  iowkit in 'iowkit.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
