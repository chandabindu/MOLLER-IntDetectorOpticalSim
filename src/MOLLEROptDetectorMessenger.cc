#include "MOLLEROptDetectorMessenger.hh"

MOLLEROptDetectorMessenger::MOLLEROptDetectorMessenger(MOLLEROptDetector* theDet)
  :Det(theDet)
{ 

  Dir = new G4UIdirectory("/Det/");
  Dir1 = new G4UIdirectory("/R1/");
  Dir2 = new G4UIdirectory("/R2/");
  Dir1 -> SetGuidance("General ring control.");
  Dir1 -> SetGuidance("R1 control.");
  Dir2 -> SetGuidance("R2 control.");

  DetZPositionCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/SetCenterPositionInZ",this);
  DetZPositionCmd1->SetGuidance("Set the Z position of the Detetect container center"); 
  DetZPositionCmd1->SetParameterName("Size",true);
  DetZPositionCmd1->SetUnitCategory("Length");
  DetZPositionCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);

  DetYPositionCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/SetCenterPositionInY",this);
  DetYPositionCmd1->SetGuidance("Set the Y position of the Detector container center"); 
  DetYPositionCmd1->SetParameterName("Size",true);
  DetYPositionCmd1->SetUnitCategory("Length");
  DetYPositionCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);

  DetXPositionCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/SetCenterPositionInX",this);
  DetXPositionCmd1->SetGuidance("Set the X position of the Detector container center"); 
  DetXPositionCmd1->SetParameterName("Size",true);
  DetXPositionCmd1->SetUnitCategory("Length");
  DetXPositionCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);

  DetMatCmd = new G4UIcmdWithAString("/Det/SetMaterial",this);
  DetMatCmd->SetGuidance("Select Material of the Detetector.");
  DetMatCmd->SetParameterName("choice",false);
  DetMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  LightGuideUpperInterfaceCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideUpperInterface",this); 
  LightGuideUpperInterfaceCmd1->SetGuidance("Set the light guide to PMT interface Y location.") ;         
  LightGuideUpperInterfaceCmd1->SetParameterName("Size",true);                   
  LightGuideUpperInterfaceCmd1->SetUnitCategory("Length");                       
  LightGuideUpperInterfaceCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                      
  
  LightGuideMiddleBoxCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideMiddleBox",this); 
  LightGuideMiddleBoxCmd1->SetGuidance("Set the light guide straight middle box height.") ;         
  LightGuideMiddleBoxCmd1->SetParameterName("Size",true);                   
  LightGuideMiddleBoxCmd1->SetUnitCategory("Length");                       
  LightGuideMiddleBoxCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);

  LightGuideLowerInterfaceCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideLowerInterface",this); 
  LightGuideLowerInterfaceCmd1->SetGuidance("Set the light guide to Quartz interface Y location.") ;         
  LightGuideLowerInterfaceCmd1->SetParameterName("Size",true);                   
  LightGuideLowerInterfaceCmd1->SetUnitCategory("Length");                       
  LightGuideLowerInterfaceCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                      

  LightGuideLowerConeFrontAngleCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideLowerConeFrontAngle",this);   
  LightGuideLowerConeFrontAngleCmd1->SetGuidance("Set the upstream face angle of the lower cone wrt. the Y axis (up)");      
  LightGuideLowerConeFrontAngleCmd1->SetParameterName("Angle",true);                                            
  LightGuideLowerConeFrontAngleCmd1->SetRange("Angle>=0. && Angle<=45.");
  LightGuideLowerConeFrontAngleCmd1->SetDefaultUnit("deg");
  LightGuideLowerConeFrontAngleCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                         

  LightGuideLowerConeBackAngleCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideLowerConeBackAngle",this);   
  LightGuideLowerConeBackAngleCmd1->SetGuidance("Set the downstream face angle of the lower cone wrt. the Y axis");      
  LightGuideLowerConeBackAngleCmd1->SetParameterName("Angle",true);                                            
  LightGuideLowerConeBackAngleCmd1->SetRange("Angle>=0. && Angle<=45.");
  LightGuideLowerConeBackAngleCmd1->SetDefaultUnit("deg");
  LightGuideLowerConeBackAngleCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                         

  LightGuideLowerConeSideAngleCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideLowerConeSideAngle",this);   
  LightGuideLowerConeSideAngleCmd1->SetGuidance("Set the side face angle of the lower cone wrt. the Y axis");      
  LightGuideLowerConeSideAngleCmd1->SetParameterName("Angle",true);                                            
  LightGuideLowerConeSideAngleCmd1->SetRange("Angle>=0. && Angle<=45.");
  LightGuideLowerConeSideAngleCmd1->SetDefaultUnit("deg");
  LightGuideLowerConeSideAngleCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                         

  LightGuideQuartzInterfaceOpeningXCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideQuartzInterfaceOpeningX",this); 
  LightGuideQuartzInterfaceOpeningXCmd1->SetGuidance("Set the light guide to Quartz interface beam-left/right opening.") ;    
  LightGuideQuartzInterfaceOpeningXCmd1->SetParameterName("Size",true);                                          
  LightGuideQuartzInterfaceOpeningXCmd1->SetUnitCategory("Length");                                              
  LightGuideQuartzInterfaceOpeningXCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                       

  LightGuideQuartzInterfaceOpeningZCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideQuartzInterfaceOpeningZ",this); 
  LightGuideQuartzInterfaceOpeningZCmd1->SetGuidance("Set the light guide to Quartz interface beam direction opening.") ;    
  LightGuideQuartzInterfaceOpeningZCmd1->SetParameterName("Size",true);                                          
  LightGuideQuartzInterfaceOpeningZCmd1->SetUnitCategory("Length");                                              
  LightGuideQuartzInterfaceOpeningZCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                       

  LightGuidePMTInterfaceOpeningXCmd =  new G4UIcmdWithADoubleAndUnit("/Det/LightGuidePMTInterfaceOpeningX",this); 
  LightGuidePMTInterfaceOpeningXCmd->SetGuidance("Set the light guide to PMT interface beam-left/right opening.") ;    
  LightGuidePMTInterfaceOpeningXCmd->SetParameterName("Size",true);                                          
  LightGuidePMTInterfaceOpeningXCmd->SetUnitCategory("Length");                                              
  LightGuidePMTInterfaceOpeningXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);                       

  LightGuidePMTInterfaceOpeningZCmd =  new G4UIcmdWithADoubleAndUnit("/Det/LightGuidePMTInterfaceOpeningZ",this); 
  LightGuidePMTInterfaceOpeningZCmd->SetGuidance("Set the light guide to PMT interface beam direction opening.") ;    
  LightGuidePMTInterfaceOpeningZCmd->SetParameterName("Size",true);                                          
  LightGuidePMTInterfaceOpeningZCmd->SetUnitCategory("Length");                                              
  LightGuidePMTInterfaceOpeningZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  LightGuideQuartzToPMTOffsetCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/LightGuideQuartzToPMTOffset",this);      
  LightGuideQuartzToPMTOffsetCmd1->SetGuidance("Set the offset between the quartz and PMT light guide openings in the beam direction.") ;         
  LightGuideQuartzToPMTOffsetCmd1->SetParameterName("Size",true);                                               
  LightGuideQuartzToPMTOffsetCmd1->SetUnitCategory("Length");                                                   
  LightGuideQuartzToPMTOffsetCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                            
  
  LightGuideOffsetZCmd =  new G4UIcmdWithADoubleAndUnit("/Det/LightGuideToQuartzOverallOffsetInZ",this);
  LightGuideOffsetZCmd->SetGuidance("Set the offset of the entire light guide w.r.t the quartz"); 
  LightGuideOffsetZCmd->SetParameterName("Size",true);
  LightGuideOffsetZCmd->SetUnitCategory("Length");
  LightGuideOffsetZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);                  

  LightGuideOffsetYCmd =  new G4UIcmdWithADoubleAndUnit("/Det/LightGuideToQuartzOverallOffsetInY",this);
  LightGuideOffsetYCmd->SetGuidance("Set the offset of the entire light guide w.r.t the quartz"); 
  LightGuideOffsetYCmd->SetParameterName("Size",true);
  LightGuideOffsetYCmd->SetUnitCategory("Length");
  LightGuideOffsetYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  LightGuideOffsetXCmd =  new G4UIcmdWithADoubleAndUnit("/Det/LightGuideToQuartzOverallOffsetInX",this);
  LightGuideOffsetXCmd->SetGuidance("Set the offset of the entire light guide w.r.t the quartz"); 
  LightGuideOffsetXCmd->SetParameterName("Size",true);
  LightGuideOffsetXCmd->SetUnitCategory("Length");
  LightGuideOffsetXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  QuartzSizeZCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/QuartzSizeZ",this);
  QuartzSizeZCmd1->SetGuidance("Set the size of the quartz in Z"); 
  QuartzSizeZCmd1->SetParameterName("Size",true);
  QuartzSizeZCmd1->SetUnitCategory("Length");
  QuartzSizeZCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);                  

  QuartzSizeYCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/QuartzSizeY",this);
  QuartzSizeYCmd1->SetGuidance("Set the size of the quartz in Y"); 
  QuartzSizeYCmd1->SetParameterName("Size",true);
  QuartzSizeYCmd1->SetUnitCategory("Length");
  QuartzSizeYCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);

  QuartzSizeXCmd1 =  new G4UIcmdWithADoubleAndUnit("/R1/QuartzSizeX",this);
  QuartzSizeXCmd1->SetGuidance("Set the size of the quartz in X"); 
  QuartzSizeXCmd1->SetParameterName("Size",true);
  QuartzSizeXCmd1->SetUnitCategory("Length");
  QuartzSizeXCmd1->AvailableForStates(G4State_PreInit,G4State_Idle);

  QuartzRotXCmd =  new G4UIcmdWithADoubleAndUnit("/Det/QuartzRotX",this);
  QuartzRotXCmd->SetGuidance("Set the rotation angle of the quartz around X"); 
  QuartzRotXCmd->SetParameterName("Angle",true);
  QuartzRotXCmd->SetRange("Angle>=-90. && Angle<=90.");
  QuartzRotXCmd->SetDefaultUnit("deg");
  QuartzRotXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  PolarRotationCmd =  new G4UIcmdWithADoubleAndUnit("/Det/PolarRotation",this);
  PolarRotationCmd->SetGuidance("Set the rotation angle of the enitre detector around X"); 
  PolarRotationCmd->SetParameterName("Angle",true);
  PolarRotationCmd->SetRange("Angle>=-90. && Angle<=90.");
  PolarRotationCmd->SetDefaultUnit("deg");
  PolarRotationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  UpdateGeometryCmd = new G4UIcmdWithoutParameter("/Det/UpdateGeometry",this);
  UpdateGeometryCmd->SetGuidance("Update the geometry");
  UpdateGeometryCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SegRadDamageCmd = new G4UIcmdWithoutParameter("/Det/SetSegmentedRadDamageFlag",this);
  SegRadDamageCmd->SetGuidance("Implement segmented radiation damage simulation");
  SegRadDamageCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  QuartzBevelCmd =  new G4UIcmdWithADoubleAndUnit("/Det/QuartzBevelSize",this);
  QuartzBevelCmd->SetGuidance("Set the size of the quartz edge bevel"); 
  QuartzBevelCmd->SetParameterName("Bevel",true);
  QuartzBevelCmd->SetUnitCategory("Length");
  QuartzBevelCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  
}

MOLLEROptDetectorMessenger::~MOLLEROptDetectorMessenger()
{
  if (DetXPositionCmd1)      delete DetXPositionCmd1;
  if (DetYPositionCmd1)      delete DetYPositionCmd1;
  if (DetZPositionCmd1)      delete DetZPositionCmd1;

  if(LightGuideUpperInterfaceCmd1          ) delete LightGuideUpperInterfaceCmd1;          
  if(LightGuideMiddleBoxCmd1               ) delete LightGuideMiddleBoxCmd1;
  if(LightGuideLowerInterfaceCmd1          ) delete LightGuideLowerInterfaceCmd1;          
  if(LightGuideLowerConeFrontAngleCmd1     ) delete LightGuideLowerConeFrontAngleCmd1;     
  if(LightGuideLowerConeBackAngleCmd1      ) delete LightGuideLowerConeBackAngleCmd1;      
  if(LightGuideLowerConeSideAngleCmd1      ) delete LightGuideLowerConeSideAngleCmd1;      
  if(LightGuideQuartzInterfaceOpeningXCmd1 ) delete LightGuideQuartzInterfaceOpeningXCmd1; 
  if(LightGuideQuartzInterfaceOpeningZCmd1 ) delete LightGuideQuartzInterfaceOpeningZCmd1; 
  if(LightGuidePMTInterfaceOpeningXCmd    ) delete LightGuidePMTInterfaceOpeningXCmd;    
  if(LightGuidePMTInterfaceOpeningZCmd    ) delete LightGuidePMTInterfaceOpeningZCmd;    
  if(LightGuideQuartzToPMTOffsetCmd1       ) delete LightGuideQuartzToPMTOffsetCmd1;       
  if(LightGuideOffsetXCmd                 ) delete LightGuideOffsetXCmd;                 
  if(LightGuideOffsetYCmd                 ) delete LightGuideOffsetYCmd;                 
  if(LightGuideOffsetZCmd                 ) delete LightGuideOffsetZCmd;

  if(UpdateGeometryCmd                    ) delete UpdateGeometryCmd;
  if(SegRadDamageCmd                      ) delete SegRadDamageCmd;
  
  if(QuartzSizeXCmd1                       ) delete QuartzSizeXCmd1;                       
  if(QuartzSizeYCmd1                       ) delete QuartzSizeYCmd1;                       
  if(QuartzSizeZCmd1                       ) delete QuartzSizeZCmd1;                       
  if(QuartzBevelCmd                       ) delete QuartzBevelCmd;                       
  if(QuartzRotXCmd                        ) delete QuartzRotXCmd;                       
  if(PolarRotationCmd                     ) delete PolarRotationCmd;                       
  
  if (DetMatCmd)                            delete DetMatCmd;
  if (Dir)                                  delete Dir;
}

void MOLLEROptDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue1,G4String newValue2)
{ 
  if( command.contains("DetXPositionCmd") ) Det->SetCenterPositionInX(DetXPositionCmd1->GetNewDoubleValue(newValue),DetXPositionCmd2->GetNewDoubleValue(newValue));
  if( command == DetYPositionCmd1 ) Det->SetCenterPositionInY(DetYPositionCmd1->GetNewDoubleValue(newValue));
  if( command == DetZPositionCmd1 ) Det->SetCenterPositionInZ(DetZPositionCmd1->GetNewDoubleValue(newValue));
  if( command == DetMatCmd ) Det->SetMaterial(newValue);

  if( command == LightGuideUpperInterfaceCmd1 )         { Det->SetUpperInterfacePlane(LightGuideUpperInterfaceCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideMiddleBoxCmd1 )              { Det->SetMiddleBoxHeight(LightGuideMiddleBoxCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideLowerInterfaceCmd1 )         { Det->SetLowerInterfacePlane(LightGuideLowerInterfaceCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideLowerConeFrontAngleCmd1 )    { Det->SetLowerConeFrontFaceAngle(LightGuideLowerConeFrontAngleCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideLowerConeBackAngleCmd1 )     { Det->SetLowerConeBackFaceAngle(LightGuideLowerConeBackAngleCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideLowerConeSideAngleCmd1 )     { Det->SetLowerConeSideFaceAngle(LightGuideLowerConeSideAngleCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideQuartzInterfaceOpeningXCmd1 ){ Det->SetQuartzInterfaceOpeningX(LightGuideQuartzInterfaceOpeningXCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideQuartzInterfaceOpeningZCmd1 ){ Det->SetQuartzInterfaceOpeningZ(LightGuideQuartzInterfaceOpeningZCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuidePMTInterfaceOpeningXCmd )   { Det->SetPMTInterfaceOpeningX(LightGuidePMTInterfaceOpeningXCmd->GetNewDoubleValue(newValue));}
  if( command == LightGuidePMTInterfaceOpeningZCmd )   { Det->SetPMTInterfaceOpeningZ(LightGuidePMTInterfaceOpeningZCmd->GetNewDoubleValue(newValue));}
  if( command == LightGuideQuartzToPMTOffsetCmd1 )      { Det->SetQuartzToPMTOffsetInZ(LightGuideQuartzToPMTOffsetCmd1->GetNewDoubleValue(newValue));}
  if( command == LightGuideOffsetXCmd )                { Det->SetLightGuideOffsetInX(LightGuideOffsetXCmd->GetNewDoubleValue(newValue));}
  if( command == LightGuideOffsetYCmd )                { Det->SetLightGuideOffsetInY(LightGuideOffsetYCmd->GetNewDoubleValue(newValue));}
  if( command == LightGuideOffsetZCmd )                { Det->SetLightGuideOffsetInZ(LightGuideOffsetZCmd->GetNewDoubleValue(newValue));}
  
  if( command == UpdateGeometryCmd )                   { Det->UpdateThisGeometry();}
  if( command == SegRadDamageCmd)                      { Det->SetSegRadDamageFlag();}
  
  if( command == QuartzSizeXCmd1 )                      { Det->SetQuartzSizeX(QuartzSizeXCmd1->GetNewDoubleValue(newValue));}
  if( command == QuartzSizeYCmd1 )                      { Det->SetQuartzSizeY(QuartzSizeYCmd1->GetNewDoubleValue(newValue));}
  if( command == QuartzSizeZCmd1 )                      { Det->SetQuartzSizeZ(QuartzSizeZCmd1->GetNewDoubleValue(newValue));}
  if( command == QuartzBevelCmd )                      { Det->SetQuartzBevel(QuartzBevelCmd->GetNewDoubleValue(newValue));}
  if( command == QuartzRotXCmd )                       { Det->SetQuartzRotX(QuartzRotXCmd->GetNewDoubleValue(newValue));}
  if( command == PolarRotationCmd )                    { Det->SetPolarRotationAngle(PolarRotationCmd->GetNewDoubleValue(newValue));}

  
}
