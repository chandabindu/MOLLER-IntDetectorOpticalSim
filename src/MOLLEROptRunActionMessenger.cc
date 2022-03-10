#include "MOLLEROptRunActionMessenger.hh"

MOLLEROptRunActionMessenger::MOLLEROptRunActionMessenger(MOLLEROptRunAction* theRunAction)
  :RunAction(theRunAction)
{ 

  Dir = new G4UIdirectory("/RunAction/");
  Dir -> SetGuidance("My Run Action Control");

  MyRunIDCmd = new G4UIcmdWithAnInteger("/RunAction/SetID",this);
  MyRunIDCmd->SetGuidance("Set the run ID.");
  MyRunIDCmd->SetParameterName("choice",false);
  MyRunIDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ROOTFileFlagCmd = new G4UIcmdWithAnInteger("/RunAction/SetROOTFileFlag",this);
  ROOTFileFlagCmd->SetGuidance("Set the flag that specifies if ROOT files are written: 1 (yes)  0 (no).");
  ROOTFileFlagCmd->SetParameterName("flag",false);
  ROOTFileFlagCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ROOTFileName = new G4UIcmdWithAString("/RunAction/SetOutputName",this);
  ROOTFileName->SetGuidance("Set the output file name.");
  ROOTFileName->SetParameterName("setname",false);
  ROOTFileName->AvailableForStates(G4State_PreInit,G4State_Idle);
}

MOLLEROptRunActionMessenger::~MOLLEROptRunActionMessenger()
{
  if (MyRunIDCmd)   delete MyRunIDCmd;
  if(ROOTFileFlagCmd) delete ROOTFileFlagCmd;
  if(ROOTFileName) delete ROOTFileName;
  if (Dir) delete Dir;
}

void MOLLEROptRunActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == MyRunIDCmd ){
    if(RunAction)
      RunAction->SetMyRunID(MyRunIDCmd->GetNewIntValue(newValue)); 
  }
  if(command == ROOTFileFlagCmd){
    if(RunAction)
      RunAction->SetROOTFileFlag(ROOTFileFlagCmd->GetNewIntValue(newValue));
  }
  if(command == ROOTFileName){
    if(RunAction)
      RunAction->SetROOTFileName(newValue);
      //RunAction->SetROOTFileName(ROOTFileName->GetCurrentValue());
  }
}
