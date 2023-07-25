#include "MOLLEROptConstruction.hh"

MOLLEROptConstruction::MOLLEROptConstruction(MOLLEROptTrackingReadout *trReadout, MOLLEROptMaterial* mat) 
  : G4VUserDetectorConstruction()
{
  World_Solid    = NULL;  
  World_Logical  = NULL;  
  World_Physical = NULL;
  
  MOLLERMessenger = NULL;
  Materials       = mat;

  Detector        = NULL;
  //LightGuide1      = NULL;
  //Detector2        = NULL;

  fWorldLengthInX = 0.0; 
  fWorldLengthInY = 0.0;
  fWorldLengthInZ = 0.0;

  TrackingReadout = trReadout;

  MOLLERMessenger = new MOLLEROptMessenger(this);
}

MOLLEROptConstruction::~MOLLEROptConstruction()
{
  if (Detector)          delete Detector;
  //if (Material)         delete Material;
  if (MOLLERMessenger)    delete MOLLERMessenger;             
}

G4VPhysicalVolume* MOLLEROptConstruction::Construct()
{
  Detector = new MOLLEROptDetector(TrackingReadout,"1Ring","2Ring",Materials);
  //DetMessenger = new MOLLEROptDetectorMessenger(Detector);
  
  fWorldLengthInX =  15.0*m;
  fWorldLengthInY =  15.0*m;
  fWorldLengthInZ =  30.0*m;
  
  World_Material   = Materials->GetMaterial("Vacuum");
  
  World_Solid = new G4Box("World_Solid",
			  0.5* fWorldLengthInX , 
			  0.5* fWorldLengthInY ,
			  0.5* fWorldLengthInZ );
  
  World_Logical = new G4LogicalVolume( World_Solid, 
				       World_Material, 
				       "World_Logical", 
				       0, 0, 0);
  World_Physical = new G4PVPlacement(0, // no rotation
				     G4ThreeVector(), // at (0,0,0)
				     World_Logical,  
				     "World_Physical", 
				     0,false,0);             
  
  // Detector->ConstructComponent(World_Physical);
  // Detector->SetCenterPositionInZ(0.0*cm);
  // LightGuide->ConstructComponent(World_Physical);
  // LightGuide->SetCenterPositionInY(7.5*cm);

  //Ring 1
  Detector->SetQuartzSizeX1(8.4*cm);
  Detector->SetQuartzSizeY1(15*cm);  //without the 45 degree cut region
  Detector->SetQuartzSizeZ1(1.5*cm);
  Detector->SetLowerInterfacePlane1(5.6*cm);
  Detector->SetMiddleBoxHeight1(9.0*cm);
  Detector->SetUpperInterfacePlane1(25*cm);
  Detector->SetLowerConeFrontFaceAngle1(28*degree);
  Detector->SetLowerConeBackFaceAngle1(22*degree);
  Detector->SetLowerConeSideFaceAngle1(0*degree);
  Detector->SetQuartzInterfaceOpeningZ1(1.8*cm);
  Detector->SetQuartzInterfaceOpeningX1(9.2*cm);
  Detector->SetQuartzToPMTOffsetInZ1(-0.3*cm);  
  
  //Ring 2
  Detector->SetQuartzSizeX2(8.4*cm);
  Detector->SetQuartzSizeY2(15*cm);  //without the 45 degree cut region
  Detector->SetQuartzSizeZ2(1.5*cm);
  Detector->SetLowerInterfacePlane2(5.6*cm);
  Detector->SetMiddleBoxHeight2(9.0*cm);
  Detector->SetUpperInterfacePlane2(25*cm);
  Detector->SetLowerConeFrontFaceAngle2(28*degree);
  Detector->SetLowerConeBackFaceAngle2(22*degree);
  Detector->SetLowerConeSideFaceAngle2(0*degree);
  Detector->SetQuartzInterfaceOpeningZ2(1.8*cm);
  Detector->SetQuartzInterfaceOpeningX2(9.2*cm);
  Detector->SetQuartzToPMTOffsetInZ2(-0.3*cm);  

  //General objects
  Detector->SetPMTInterfaceOpeningZ(5.6*cm);
  Detector->SetPMTInterfaceOpeningX(5.6*cm);  
  Detector->SetPMTCathodeRadius(3.5*cm);
  Detector->SetPMTCathodeThickness(0.1*cm);
  Detector->SetAzimuthalRotationAngle(0);
  Detector->SetPolarRotationAngle(0);
  Detector->Initialize();
  Detector->ConstructDetector(World_Physical);

  World_Logical->SetVisAttributes (G4VisAttributes::Invisible);
  
  DumpGeometricalTree(World_Physical);
  
  return World_Physical;
}

void MOLLEROptConstruction::GetQuartzLimits(G4double *vals)
{
  Detector->GetQuartzLimits(vals);
}

void MOLLEROptConstruction::GetLightGuideLimits(G4double *vals)
{
  Detector->GetLightGuideLimits(vals);
}


void MOLLEROptConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
{
  for(int isp=0;isp<depth;isp++)
    { G4cout << "  "; }
  G4cout << aVolume->GetName() << "[" << aVolume->GetCopyNo() << "] "
         << aVolume->GetLogicalVolume()->GetName() << " "
         << aVolume->GetLogicalVolume()->GetNoDaughters() << " "
	 << aVolume->GetLogicalVolume()->GetMaterial()->GetName();
  if(aVolume->GetLogicalVolume()->GetSensitiveDetector())
  {
    G4cout << " " << aVolume->GetLogicalVolume()->GetSensitiveDetector()
                            ->GetFullPathName();
  }
  G4cout << G4endl;
  for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++){
    
    DumpGeometricalTree(aVolume->GetLogicalVolume()->GetDaughter(i),depth+1);


  }
}


void MOLLEROptConstruction::UpdateGeometry()
{
  G4GeometryManager::GetInstance()->OpenGeometry();

  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  G4LogicalBorderSurface::CleanSurfaceTable();


  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

