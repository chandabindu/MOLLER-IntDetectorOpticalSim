#include "MOLLEROptDetector.hh"

MOLLEROptDetector::MOLLEROptDetector(MOLLEROptTrackingReadout *TrRO, G4String type, MOLLEROptMaterial* mat)
{	    	    
  TrackingReadout = TrRO;
  DetType = type;
  Materials = mat;
  DetMaterial = Materials->GetMaterial("Air");  

  Quartz1 = new  MOLLEROptDetectorQuartz(TrackingReadout,type,Materials);
  LightGuide1 = new  MOLLEROptDetectorLightGuide(TrackingReadout,type,Materials);
  PMT1 = new  MOLLEROptDetectorPMT(TrackingReadout,type,Materials,LightGuide1);     
  detMessenger = NULL;

  MotherVolume = NULL;
  
  DetLogical  = NULL;
  DetPhysical = NULL;
  DetSolid = NULL;

  RotationDet = NULL;

  fReadFile ="../data/December2021/GDML/Ring5/R5-Module-Al.gdml";
  fWriteFile="wtest.gdml";
  // fStepFile ="mbb";


}

MOLLEROptDetector::~MOLLEROptDetector()
{
  delete Quartz1;
  delete LightGuide1;
  delete PMT1;
  //  delete Structure;
  //delete Messenger;
}

void MOLLEROptDetector::SetQuartzSizeX(G4double x)
{
  if(Quartz1)
    Quartz1->SetQuartzSizeX(x);
}

void MOLLEROptDetector::SetQuartzSizeY(G4double y)
{
  if(Quartz1)
    Quartz1->SetQuartzSizeY(y);
}
				       
void MOLLEROptDetector::SetQuartzSizeZ(G4double z)
{
  if(Quartz1)
    Quartz1->SetQuartzSizeZ(z);
}

				       
void MOLLEROptDetector::SetQuartzRotX(G4double rX)
{
  if(Quartz1)
    Quartz1->SetQuartzRotX(rX);

  //need to counter rotate the entire detector, so that the events
  //still hit the detector at normal incidence.

  //RotationDet->rotateX(-rX);
}

void MOLLEROptDetector::SetLowerInterfacePlane(G4double LowerPlane)
{
  if(LightGuide1)
    LightGuide1->SetLowerInterfacePlane(LowerPlane);
}

void MOLLEROptDetector::SetMiddleBoxHeight(G4double MiddlePlane)
{
  if(LightGuide1)
    LightGuide1->SetMiddleBoxHeight(MiddlePlane);
}

void MOLLEROptDetector::SetUpperInterfacePlane(G4double UpperPlane)
{
  if(LightGuide1)
    LightGuide1->SetUpperInterfacePlane(UpperPlane); 
}

void MOLLEROptDetector::SetLowerConeFrontFaceAngle(G4double angle)
{
  if(LightGuide1)
    LightGuide1->SetLowerConeFrontFaceAngle(angle);
}

void MOLLEROptDetector::SetLowerConeBackFaceAngle(G4double angle)
{
  if(LightGuide1)
    LightGuide1->SetLowerConeBackFaceAngle(angle);
}

void MOLLEROptDetector::SetLowerConeSideFaceAngle(G4double angle)
{  
  if(LightGuide1){
    LightGuide1->SetLowerConeSideFaceAngle(angle);
  }
}

void MOLLEROptDetector::SetQuartzInterfaceOpeningZ(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetQuartzInterfaceOpeningZ(size);
}

void MOLLEROptDetector::SetQuartzInterfaceOpeningX(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetQuartzInterfaceOpeningX(size);
}

void MOLLEROptDetector::SetPMTInterfaceOpeningZ(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetPMTInterfaceOpeningZ(size);
  if(PMT1)
    PMT1->SetLGInterfaceOpeningZ(size);
}

void MOLLEROptDetector::SetPMTInterfaceOpeningX(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetPMTInterfaceOpeningX(size);
  if(PMT1)
    PMT1->SetLGInterfaceOpeningX(size);
}


void MOLLEROptDetector::SetQuartzToPMTOffsetInZ(G4double val)
{
  PMTToQuartzOffset = val;
  if(LightGuide1)
    LightGuide1->SetQuartzToPMTOffsetInZ(val);
  if(PMT1)
    PMT1->SetCenterPositionInZ(val);
}



void MOLLEROptDetector::SetAzimuthalRotationAngle(G4double val)
{
  AzimuAngle = val; 
}

void MOLLEROptDetector::SetPolarRotationAngle(G4double val)
{
  PolarAngle = val;

}

void MOLLEROptDetector::SetPMTCathodeThickness(G4double val)
{
  if(PMT1)
    PMT1->SetCathodeThickness(val);
}

void MOLLEROptDetector::SetPMTCathodeRadius(G4double val)
{
  if(PMT1)
    PMT1->SetCathodeRadius(val);
  if(LightGuide1)
    LightGuide1->SetPMTOpeningRadius(val);
}



void MOLLEROptDetector::UpdateThisGeometry()
{
  G4LogicalVolume *mLog;

  G4GeometryManager::GetInstance()->OpenGeometry();
  
  delete DetPhysical;
  RotationDet->rotateX(PolarAngle);  
  PMT1->UpdateGeometry();
  Quartz1->UpdateGeometry();
  LightGuide1->UpdateGeometry();
  CalculateDimensions();
  DetSolid = new G4Box(DetType+"_Solid",
		       0.5* DetFullLengthX, 
		       0.5* DetFullLengthY,
		       0.5* DetFullLengthZ);
  DetLogical = new G4LogicalVolume( DetSolid, DetMaterial, DetType+"_Logical");
  DetLogical->SetSolid(DetSolid);
  ResetCenterLocation();
  ConstructDetector(MotherVolume);
  //ConstructMountingStructure(MotherVolume);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
   
}

void MOLLEROptDetector::CalculateDimensions()
{
  if(LightGuide1->GetLightGuideWidth() > 2*PMT1->GetRadius())
    DetFullLengthX = LightGuide1->GetLightGuideWidth() + 1.0*cm;
  else
    DetFullLengthX = 2*PMT1->GetRadius() +1.0*cm;
  
  if(LightGuide1->GetLightGuideDepth() > 2*PMT1->GetRadius())
    DetFullLengthZ = LightGuide1->GetLightGuideDepth() + 2*PMTToQuartzOffset + 4.0*cm;
  else
    DetFullLengthZ = 2*PMT1->GetRadius() + 2*PMTToQuartzOffset + 4.0*cm;
  

  DetFullLengthY = Quartz1->GetQuartzSizeY()+LightGuide1->GetLightGuideLength()+PMT1->GetPMTLength()+1.0*cm+LightGuide1->GetCurrentMiddleBoxHeight();
}

void MOLLEROptDetector::ResetCenterLocation()
{
  PositionDetX = 0.0*cm;
  PositionDetY = 0.0*cm;//DetFullLengthY/2 - Quartz->GetQuartzSizeY()/2;
  PositionDetZ = 0.0*cm;

  PositionDet.setX(PositionDetX);
  PositionDet.setY(PositionDetY);
  PositionDet.setZ(PositionDetZ);  
}

void MOLLEROptDetector::Initialize()
{
  //let these objects setup their default solids and logical volumes
  PMTToQuartzOffset = 0;
  AzimuAngle = 0; 
  PolarAngle = 0;
  Quartz1->Initialize();
  LightGuide1->Initialize();
  PMT1->Initialize();
  
  // G4double quartzY = Quartz->GetQuartzSizeY();
  // G4double quartzZ = Quartz->GetQuartzSizeZ();  
  // G4double lguideY = LightGuide->GetCurrentUpperInterfacePlane();

  // Quartz->SetCenterPositionInY(-0.5*DetFullLengthY+quartzY/2.0 + 5*mm);
  // LightGuide->SetCenterPositionInY(-0.5*DetFullLengthY+quartzY + 5*mm);// + 0.5*LightGuide->GetCurrentQuartzInterfaceOpeningY()*TMath::Sin(Qrot));
  // PMT->SetCenterPositionInY(-0.5*DetFullLengthY+quartzY+lguideY+PMT->GetPMTLength()/2.0 + 5.0*mm);// + 0.5*LightGuide->GetCurrentQuartzInterfaceOpeningY()*TMath::Sin(Qrot));

  CalculateDimensions();
  ResetCenterLocation();

  RotationDet = new G4RotationMatrix;

  DetSolid = new G4Box(DetType+"_Solid",
		       0.5* DetFullLengthX, 
		       0.5* DetFullLengthY,
		       0.5* DetFullLengthZ);
  
  DetLogical = new G4LogicalVolume( DetSolid, DetMaterial, DetType+"_Logical");

}

G4VPhysicalVolume* MOLLEROptDetector::ConstructDetector(G4VPhysicalVolume* Mother)
{
  if(!Mother) return 0;
  
  if(!MotherVolume){
    MotherVolume = Mother;
  }

  DetPhysical = new G4PVPlacement(RotationDet,
				  PositionDet,   
				  DetType+"_Physical",
				  DetLogical,
				  MotherVolume,false,1);    
  
  G4double quartzY = Quartz1->GetQuartzSizeY();
  G4double quartzZ = Quartz1->GetQuartzSizeZ();  
  G4double lguideY = LightGuide1->GetCurrentUpperInterfacePlane();

  G4double Qrot = Quartz1->GetQuartzRotationX();
     
  Quartz1->Construct(DetPhysical);
  Quartz1->SetCenterPositionInZ(0.5*quartzY*(TMath::Sin(Qrot)));
  Quartz1->SetCenterPositionInY(-0.5*DetFullLengthY + 0.5*quartzY + 0.5*quartzY*(1.0-TMath::Cos(Qrot)) + 0.5*quartzZ*fabs(TMath::Sin(Qrot)) + 5*mm);
  LightGuide1->Construct(DetPhysical);
  LightGuide1->SetCenterPositionInY(-0.5*DetFullLengthY+quartzY + 5*mm);// + 0.5*LightGuide->GetCurrentQuartzInterfaceOpeningY()*TMath::Sin(Qrot));
  PMT1->Construct(DetPhysical);
  // We have to let the PMT extend into the light guide lsig
  PMT1->SetCenterPositionInY(-0.5*DetFullLengthY+quartzY+lguideY+PMT1->GetPMTLength()/2.0 + 5.0*mm + LightGuide1->GetCurrentMiddleBoxHeight());

  G4Colour  grey      ( 127/255., 127/255., 127/255.);
  G4VisAttributes *att = new G4VisAttributes(grey);
  att->SetVisibility(true);
  att->SetForceWireframe(true);
  DetLogical->SetVisAttributes(att);

  if(!detMessenger)
    detMessenger = new MOLLEROptDetectorMessenger(this);  


  return DetPhysical;
} 

void MOLLEROptDetector::ConstructMountingStructure(G4VPhysicalVolume* Mother)
{
  gdmlParser.Read(fReadFile);

  G4LogicalVolume *logV = gdmlParser.GetVolume("R5-Module-Aluminum");

  if(logV){

    G4RotationMatrix  *Rot1 = new G4RotationMatrix;
   Rot1->rotateZ(180*degree);
  G4double quartzY = Quartz1->GetQuartzSizeY();
  
  // cout << "Quartz center position X: " << Quartz->GetCurrentCenterPositionInX() << endl;
  // cout << "Quartz center position Y: " << Quartz->GetCurrentCenterPositionInY() << "Set = " << -0.5*DetFullLengthY+quartzY/2.0 + 5*mm << endl;
  // cout << "Quartz center position Z: " << Quartz->GetCurrentCenterPositionInZ() << endl;

  G4ThreeVector Qpos = Quartz1->GetCurrentCenterPosition();
  // cout << "Quartz center position X: " << Qpos.x() << endl;
  // cout << "Quartz center position Y: " << Qpos.y() << endl;
  // cout << "Quartz center position Z: " << Qpos.z() << endl;
  // cout << "Polar Angle = " << PolarAngle << endl;
  G4double dz = 2*fabs(Qpos.y())*TMath::Sin(PolarAngle/2)*TMath::Cos(PolarAngle/2);
  G4double dy = 2*fabs(Qpos.y())*TMath::Sin(PolarAngle/2)*TMath::Sin(PolarAngle/2);
  // cout << "dz: " << dz << endl;
  // cout << "dy: " << dy << endl;
  
  G4ThreeVector Trans1 = G4ThreeVector(Qpos.x(),Qpos.y()+dy,Qpos.z()+dz);
  // cout << "Quartz center position X: " << Trans1.x() << endl;
  // cout << "Quartz center position Y: " << Trans1.y() << endl;
  // cout << "Quartz center position Z: " << Trans1.z() << endl;
  
  G4ThreeVector LGpos = LightGuide1->GetCurrentCenterPosition();
  // cout << "Guide center position X: " << LGpos.x() << endl;
  // cout << "Guide center position Y: " << LGpos.y() << endl;
  // cout << "Guide center position Z: " << LGpos.z() << endl;
    
  G4VPhysicalVolume* MPhys = new G4PVPlacement(Rot1,
					       Trans1,   
					       DetType+"_logV",
					       logV ,
					       Mother,false,1); 
  
    G4Colour green    (   0/255., 255/255.,   0/255.);
    G4VisAttributes *att2 = new G4VisAttributes(green);
    att2->SetVisibility(true);
    //att2->SetForceWireframe(true);
    logV->SetVisAttributes(att2);

    G4ThreeVector MPos = MPhys->GetTranslation();
    // cout << "Mount center position X: " << MPos.x() << endl;
    // cout << "Mount center position Y: " << MPos.y() << endl;
    // cout << "Mount center position Z: " << MPos.z() << endl;
    
  }  
}



void MOLLEROptDetector::SetMaterial(G4String materialName)
{
  DetMaterial = Materials->GetMaterial(materialName);
}

void MOLLEROptDetector::SetCenterPositionInX(G4double xPos)
{
    PositionDetX = xPos;	 

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX,
					      PositionDetY, 
					      PositionDetZ));
}

void MOLLEROptDetector::SetCenterPositionInY(G4double yPos)
{
    PositionDetY = yPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX,
					      PositionDetY, 
					      PositionDetZ));
}

void MOLLEROptDetector::SetCenterPositionInZ(G4double zPos)
{
    PositionDetZ = zPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX,
					      PositionDetY, 
					      PositionDetZ));
}

void MOLLEROptDetector::SetLightGuideOffsetInX(G4double x)
{
  G4double cX;
  
  if(LightGuide1 &&  PMT1){

    cX = LightGuide1->GetCurrentCenterPositionInX() + x*cm;
    
    LightGuide1->SetCenterPositionInX(cX);

    cX = PMT1->GetCurrentCenterPositionInX() + x*cm;

    PMT1->SetCenterPositionInX(cX);
  }
}

void MOLLEROptDetector::SetLightGuideOffsetInY(G4double y)
{
  G4double cY;
  
  if(LightGuide1 &&  PMT1){

    cY = LightGuide1->GetCurrentCenterPositionInY() + y*cm;
    
    LightGuide1->SetCenterPositionInY(cY);

    cY = PMT1->GetCurrentCenterPositionInY() + y*cm;

    PMT1->SetCenterPositionInY(cY);
  }
}

void MOLLEROptDetector::SetLightGuideOffsetInZ(G4double z)
{
  G4double cZ;
  
  if(LightGuide1 &&  PMT1){

    cZ = LightGuide1->GetCurrentCenterPositionInZ() + z*cm;
    
    LightGuide1->SetCenterPositionInZ(cZ);

    cZ = PMT1->GetCurrentCenterPositionInZ() + z*cm;

    PMT1->SetCenterPositionInZ(cZ);
  }
}


void MOLLEROptDetector::GetQuartzLimits(G4double *vals)
{
  Quartz1->GetQuartzLimits(vals);
}

void MOLLEROptDetector::GetLightGuideLimits(G4double *vals)
{
  LightGuide1->GetLightGuideLimits(vals);
}


