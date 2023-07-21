#ifndef MOLLEROptDetector_h
#define MOLLEROptDetector_h 

#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh"

#include "MOLLEROptMaterial.hh"
#include "MOLLEROptTrackingReadout.hh"
#include "MOLLEROptDetectorLightGuide.hh"
#include "MOLLEROptDetectorQuartz.hh"
#include "MOLLEROptDetectorPMT.hh"
#include "MOLLEROptDetectorMessenger.hh"

#include "G4GDMLParser.hh"

class MOLLEROptDetectorMessenger;

class MOLLEROptDetector
{
public:
  MOLLEROptDetector(MOLLEROptTrackingReadout*, G4String type1, G4String type2, MOLLEROptMaterial* mat);
  ~MOLLEROptDetector();

  G4VPhysicalVolume* ConstructDetector(G4VPhysicalVolume* Mother);
  void ConstructMountingStructure(G4VPhysicalVolume* Mother);
  
  void DestroyComponent();
  void Initialize();
  void SetMaterial(G4String materialName);

  //The standard coordinate system is: z=beam direction, y=beam up, x = beam left
  //Dimensions below assume a detector that is located at the origin with the 45 degreee
  //exit face at the upper y end and the width of the detector along +-x.
  
  //Ring 1 objects
  void SetCenterPositionInX1(G4double xPos);
  void SetCenterPositionInY1(G4double yPos);
  void SetCenterPositionInZ1(G4double zPos);
  void SetQuartzSizeX1(G4double x); 
  void SetQuartzSizeY1(G4double y); 
  void SetQuartzSizeZ1(G4double z);
  void SetLowerInterfacePlane1(G4double LowerPlane);
  void SetMiddleBoxHeight1(G4double MiddlePlane);
  void SetUpperInterfacePlane1(G4double UpperPlane);
  void SetLowerConeFrontFaceAngle1(G4double angle) ; //in radians
  void SetLowerConeBackFaceAngle1(G4double angle);
  void SetLowerConeSideFaceAngle1(G4double angle);
  void SetQuartzInterfaceOpeningZ1(G4double size);
  void SetQuartzInterfaceOpeningX1(G4double size);
  void SetQuartzToPMTOffsetInZ1(G4double val);

  //Ring 2 objects
  void SetCenterPositionInX2(G4double xPos);
  void SetCenterPositionInY2(G4double yPos);
  void SetCenterPositionInZ2(G4double zPos);
  void SetQuartzSizeX2(G4double x); 
  void SetQuartzSizeY2(G4double y); 
  void SetQuartzSizeZ2(G4double z);
  void SetLowerInterfacePlane2(G4double LowerPlane);
  void SetMiddleBoxHeight2(G4double MiddlePlane);
  void SetUpperInterfacePlane2(G4double UpperPlane);
  void SetLowerConeFrontFaceAngle2(G4double angle) ; //in radians
  void SetLowerConeBackFaceAngle2(G4double angle);
  void SetLowerConeSideFaceAngle2(G4double angle);
  void SetQuartzInterfaceOpeningZ2(G4double size);
  void SetQuartzInterfaceOpeningX2(G4double size);
  void SetQuartzToPMTOffsetInZ2(G4double val);

  void SetQuartzRotX(G4double r);
  void SetAzimuthalRotationAngle(G4double a); //w.r.t. to the positive y axis (up) in radians
  void SetPolarRotationAngle(G4double a); //w.r.t. to the positive z axis (downstream) in radians

  void SetLightGuideOffsetInX(G4double x);
  void SetLightGuideOffsetInY(G4double y);
  void SetLightGuideOffsetInZ(G4double z);

  void SetPMTInterfaceOpeningZ(G4double size);
  void SetPMTInterfaceOpeningX(G4double size);
  void SetQuartzBevel(G4double bev) {Quartz1->SetBevelSize(bev); Quartz2->SetBevelSize(bev);}

  void SetPMTCathodeRadius(G4double size);
  void SetPMTCathodeThickness(G4double size);
  
  void UpdateThisGeometry();
  void CalculateDimensions();
  void ResetCenterLocation();
  void SetSegRadDamageFlag() {if(Quartz1) Quartz1->SetSegRadDamageFlag(); if(Quartz2) Quartz2->SetSegRadDamageFlag(); Materials->SetSegRadDamage();}

  G4LogicalVolume*   GetLogicalVolume()    {return DetLogical1; return DetLogical2;}
  G4VPhysicalVolume* GetPhysicalVolume()   {return DetPhysical1; return DetPhysical2;}

  void GetQuartzLimits(G4double *vals);
  void GetLightGuideLimits(G4double *vals);


private:

  G4GDMLParser gdmlParser;

  G4String fReadFile;
  G4String fWriteFile;
  G4String fStepFile;
  G4int fWritingChoice;

  G4String DetType1; //like: Ring5, or Ring1 ...
  G4String DetType2;

  MOLLEROptDetectorMessenger*  detMessenger;
  MOLLEROptTrackingReadout *TrackingReadout;
  MOLLEROptMaterial* Materials;
  MOLLEROptDetectorLightGuide* LightGuide1; 
  MOLLEROptDetectorQuartz*     Quartz1;
  MOLLEROptDetectorPMT*        PMT1;
  MOLLEROptDetectorLightGuide* LightGuide2; 
  MOLLEROptDetectorQuartz*     Quartz2;
  MOLLEROptDetectorPMT*        PMT2;

  G4VPhysicalVolume* MotherVolume;

  G4LogicalVolume*   DetLogical1; 
  G4VPhysicalVolume* DetPhysical1;
  G4Box*             DetSolid1; 
  G4LogicalVolume*   DetLogical2; 
  G4VPhysicalVolume* DetPhysical2;
  G4Box*             DetSolid2;

  G4Material*        DetMaterial;

  G4double DetFullLengthX1;
  G4double DetFullLengthY1;
  G4double DetFullLengthZ1;
  G4double DetFullLengthX2;
  G4double DetFullLengthY2;
  G4double DetFullLengthZ2;

  G4ThreeVector     PositionDet1;
  G4ThreeVector     PositionDet2;

  G4RotationMatrix* RotationDet;  

  G4double PositionDetX1;
  G4double PositionDetY1;
  G4double PositionDetZ1;
  G4double PositionDetX2;
  G4double PositionDetY2;
  G4double PositionDetZ2;

  G4double AzimuAngle;
  G4double PolarAngle;

  G4double PMTToQuartzOffset1;
  G4double PMTToQuartzOffset2;

  //Detector Mounting structure

  //Left side of LG lower cone and quartz tray
  G4GenericTrap* QLGTray_Sld_Left_out;
  G4GenericTrap* QLGTray_Sld_Left_In; 
  G4SubtractionSolid* QLGTray_Sld_Left;

  
};
#endif
