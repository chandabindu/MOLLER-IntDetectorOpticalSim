#ifndef MOLLEROptDetectorMessenger_h
#define MOLLEROptDetectorMessenger_h 1

#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

#include "MOLLEROptDetector.hh"

class MOLLEROptDetector;

class MOLLEROptDetectorMessenger: public G4UImessenger
{
  public:
    MOLLEROptDetectorMessenger(MOLLEROptDetector*);
   ~MOLLEROptDetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:
  
  MOLLEROptDetector*         Det;
  G4UIdirectory*             Dir;
  G4UIdirectory*             Dir1;
  G4UIdirectory*             Dir2;
  G4UIcmdWithAString*        DetMatCmd;
  
  //Ring 1 objects
  G4UIcmdWithADoubleAndUnit* DetXPositionCmd1;
  G4UIcmdWithADoubleAndUnit* DetYPositionCmd1;
  G4UIcmdWithADoubleAndUnit* DetZPositionCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideUpperInterfaceCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideMiddleBoxCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerInterfaceCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerConeFrontAngleCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerConeBackAngleCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerConeSideAngleCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideQuartzInterfaceOpeningXCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideQuartzInterfaceOpeningZCmd1;
  G4UIcmdWithADoubleAndUnit* LightGuideQuartzToPMTOffsetCmd1;
  G4UIcmdWithADoubleAndUnit* QuartzSizeXCmd1;       
  G4UIcmdWithADoubleAndUnit* QuartzSizeYCmd1;       
  G4UIcmdWithADoubleAndUnit* QuartzSizeZCmd1;

  //Ring 2 objects
  G4UIcmdWithADoubleAndUnit* DetXPositionCmd2;
  G4UIcmdWithADoubleAndUnit* DetYPositionCmd2;
  G4UIcmdWithADoubleAndUnit* DetZPositionCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideUpperInterfaceCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideMiddleBoxCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerInterfaceCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerConeFrontAngleCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerConeBackAngleCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideLowerConeSideAngleCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideQuartzInterfaceOpeningXCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideQuartzInterfaceOpeningZCmd2;
  G4UIcmdWithADoubleAndUnit* LightGuideQuartzToPMTOffsetCmd2;
  G4UIcmdWithADoubleAndUnit* QuartzSizeXCmd2;       
  G4UIcmdWithADoubleAndUnit* QuartzSizeYCmd2;       
  G4UIcmdWithADoubleAndUnit* QuartzSizeZCmd2;

  G4UIcmdWithADoubleAndUnit* QuartzBevelCmd;                       
  G4UIcmdWithADoubleAndUnit* QuartzRotXCmd;
  G4UIcmdWithADoubleAndUnit* PolarRotationCmd;
  G4UIcmdWithADoubleAndUnit* LightGuidePMTInterfaceOpeningXCmd;
  G4UIcmdWithADoubleAndUnit* LightGuidePMTInterfaceOpeningZCmd;
  G4UIcmdWithADoubleAndUnit* LightGuideOffsetXCmd;
  G4UIcmdWithADoubleAndUnit* LightGuideOffsetYCmd;
  G4UIcmdWithADoubleAndUnit* LightGuideOffsetZCmd;

  G4UIcmdWithoutParameter*   UpdateGeometryCmd;
  G4UIcmdWithoutParameter*   SegRadDamageCmd;

};

#endif
