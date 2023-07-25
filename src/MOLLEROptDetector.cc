#include "MOLLEROptDetector.hh"

MOLLEROptDetector::MOLLEROptDetector(MOLLEROptTrackingReadout *TrRO, G4String type1, G4String type2, MOLLEROptMaterial* mat)
{	    	    
  TrackingReadout = TrRO;
  DetType1 = type1;
  DetType2 = type2;
  Materials = mat;
  DetMaterial = Materials->GetMaterial("Air");  

  Quartz1 = new  MOLLEROptDetectorQuartz(TrackingReadout,type1,Materials);
  LightGuide1 = new  MOLLEROptDetectorLightGuide(TrackingReadout,type1,Materials);
  PMT1 = new  MOLLEROptDetectorPMT(TrackingReadout,type1,Materials,LightGuide1);

  Quartz2 = new  MOLLEROptDetectorQuartz2(TrackingReadout,type2,Materials);
  LightGuide2 = new  MOLLEROptDetectorLightGuide(TrackingReadout,type2,Materials);
  PMT2 = new  MOLLEROptDetectorPMT(TrackingReadout,type2,Materials,LightGuide2);

  detMessenger = NULL;

  MotherVolume = NULL;
  
  DetLogical  = NULL;
  DetPhysical = NULL;
  DetSolid = NULL;

  //DetLogical2  = NULL;
  //DetPhysical2 = NULL;
  //DetSolid2 = NULL;

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

  delete Quartz2;
  delete LightGuide2;
  delete PMT2;
}

//General Ring objects

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
  if(PMT2)
    PMT2->SetCathodeThickness(val);
}

void MOLLEROptDetector::SetPMTCathodeRadius(G4double val)
{
  if(PMT1)
    PMT1->SetCathodeRadius(val);
  if(LightGuide1)
    LightGuide1->SetPMTOpeningRadius(val);
  if(PMT2)
    PMT2->SetCathodeRadius(val);
  if(LightGuide2)
    LightGuide2->SetPMTOpeningRadius(val);
}

void MOLLEROptDetector::SetPMTInterfaceOpeningZ(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetPMTInterfaceOpeningZ(size);
  if(PMT1)
    PMT1->SetLGInterfaceOpeningZ(size);
  if(LightGuide2)
    LightGuide2->SetPMTInterfaceOpeningZ(size);
  if(PMT2)
    PMT2->SetLGInterfaceOpeningZ(size);
}

void MOLLEROptDetector::SetPMTInterfaceOpeningX(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetPMTInterfaceOpeningX(size);
  if(PMT1)
    PMT1->SetLGInterfaceOpeningX(size);
  if(LightGuide2)
    LightGuide2->SetPMTInterfaceOpeningX(size);
  if(PMT2)
    PMT2->SetLGInterfaceOpeningX(size);
}

void MOLLEROptDetector::SetQuartzRotX(G4double rX)
{
  if(Quartz1)
    Quartz1->SetQuartzRotX(rX);
  if(Quartz2)
    Quartz2->SetQuartzRotX(rX);
}


//Ring 1 objects


void MOLLEROptDetector::SetQuartzSizeX1(G4double x)
{
  if(Quartz1)
    Quartz1->SetQuartzSizeX(x);
}

void MOLLEROptDetector::SetQuartzSizeY1(G4double y)
{
  if(Quartz1)
    Quartz1->SetQuartzSizeY(y);
}
				       
void MOLLEROptDetector::SetQuartzSizeZ1(G4double z)
{
  if(Quartz1)
    Quartz1->SetQuartzSizeZ(z);
}
				       
void MOLLEROptDetector::SetLowerInterfacePlane1(G4double LowerPlane)
{
  if(LightGuide1)
    LightGuide1->SetLowerInterfacePlane(LowerPlane);
}

void MOLLEROptDetector::SetMiddleBoxHeight1(G4double MiddlePlane)
{
  if(LightGuide1)
    LightGuide1->SetMiddleBoxHeight(MiddlePlane);
}

void MOLLEROptDetector::SetUpperInterfacePlane1(G4double UpperPlane)
{
  if(LightGuide1)
    LightGuide1->SetUpperInterfacePlane(UpperPlane); 
}

void MOLLEROptDetector::SetLowerConeFrontFaceAngle1(G4double angle)
{
  if(LightGuide1)
    LightGuide1->SetLowerConeFrontFaceAngle(angle);
}

void MOLLEROptDetector::SetLowerConeBackFaceAngle1(G4double angle)
{
  if(LightGuide1)
    LightGuide1->SetLowerConeBackFaceAngle(angle);
}

void MOLLEROptDetector::SetLowerConeSideFaceAngle1(G4double angle)
{  
  if(LightGuide1)
    LightGuide1->SetLowerConeSideFaceAngle(angle);
}

void MOLLEROptDetector::SetQuartzInterfaceOpeningZ1(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetQuartzInterfaceOpeningZ(size);
}

void MOLLEROptDetector::SetQuartzInterfaceOpeningX1(G4double size)
{
  if(LightGuide1)
    LightGuide1->SetQuartzInterfaceOpeningX(size);
}

void MOLLEROptDetector::SetQuartzToPMTOffsetInZ1(G4double val)
{
  PMTToQuartzOffset1 = val;
  if(LightGuide1)
    LightGuide1->SetQuartzToPMTOffsetInZ(val);
  if(PMT1)
    PMT1->SetCenterPositionInZ(val);
}


//Ring 2 objects


void MOLLEROptDetector::SetQuartzSizeX2(G4double x)
{
  if(Quartz2)
    Quartz2->SetQuartzSizeX(x);
}

void MOLLEROptDetector::SetQuartzSizeY2(G4double y)
{
  if(Quartz2)
    Quartz2->SetQuartzSizeY(y);
}
				       
void MOLLEROptDetector::SetQuartzSizeZ2(G4double z)
{
  if(Quartz2)
    Quartz2->SetQuartzSizeZ(z);
}
				       
void MOLLEROptDetector::SetLowerInterfacePlane2(G4double LowerPlane)
{
  if(LightGuide2)
    LightGuide2->SetLowerInterfacePlane(LowerPlane);
}

void MOLLEROptDetector::SetMiddleBoxHeight2(G4double MiddlePlane)
{
  if(LightGuide2)
    LightGuide2->SetMiddleBoxHeight(MiddlePlane);
}

void MOLLEROptDetector::SetUpperInterfacePlane2(G4double UpperPlane)
{
  if(LightGuide2)
    LightGuide2->SetUpperInterfacePlane(UpperPlane); 
}

void MOLLEROptDetector::SetLowerConeFrontFaceAngle2(G4double angle)
{
  if(LightGuide2)
    LightGuide2->SetLowerConeFrontFaceAngle(angle);
}

void MOLLEROptDetector::SetLowerConeBackFaceAngle2(G4double angle)
{
  if(LightGuide2)
    LightGuide2->SetLowerConeBackFaceAngle(angle);
}

void MOLLEROptDetector::SetLowerConeSideFaceAngle2(G4double angle)
{  
  if(LightGuide2)
    LightGuide2->SetLowerConeSideFaceAngle(angle);
}

void MOLLEROptDetector::SetQuartzInterfaceOpeningZ2(G4double size)
{
  if(LightGuide2)
    LightGuide2->SetQuartzInterfaceOpeningZ(size);
}

void MOLLEROptDetector::SetQuartzInterfaceOpeningX2(G4double size)
{
  if(LightGuide2)
    LightGuide2->SetQuartzInterfaceOpeningX(size);
}

void MOLLEROptDetector::SetQuartzToPMTOffsetInZ2(G4double val)
{
  PMTToQuartzOffset2 = val;
  if(LightGuide2)
    LightGuide2->SetQuartzToPMTOffsetInZ(val);
  if(PMT2)
    PMT2->SetCenterPositionInZ(val);
}



void MOLLEROptDetector::UpdateThisGeometry()
{
  G4LogicalVolume *mLog;

  G4GeometryManager::GetInstance()->OpenGeometry();
  
  delete DetPhysical;
  //delete DetPhysical2;
  RotationDet->rotateX(PolarAngle);  
  PMT1->UpdateGeometry();
  Quartz1->UpdateGeometry();
  LightGuide1->UpdateGeometry();
  PMT2->UpdateGeometry();
  Quartz2->UpdateGeometry();
  LightGuide2->UpdateGeometry();
  CalculateDimensions();
  DetSolid = new G4Box(DetType1+"_Solid",
		       10* DetFullLengthX1, 
		       10* DetFullLengthY1,
		       20* DetFullLengthZ1);
  /*DetSolid2 = new G4Box(DetType2+"_Solid",
		       0.5* DetFullLengthX2, 
		       0.5* DetFullLengthY2,
		       0.5* DetFullLengthZ2);*/
  DetLogical = new G4LogicalVolume( DetSolid, DetMaterial, DetType1+"_Logical");
  //DetLogical2 = new G4LogicalVolume( DetSolid2, DetMaterial, DetType2+"_Logical");
  DetLogical->SetSolid(DetSolid);
  //DetLogical2->SetSolid(DetSolid2);
  ResetCenterLocation();
  ConstructDetector(MotherVolume);
  //ConstructMountingStructure(MotherVolume);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
   
}

void MOLLEROptDetector::CalculateDimensions()
{
  //Ring 1 
  if(LightGuide1->GetLightGuideWidth() > 2*PMT1->GetRadius())
    DetFullLengthX1 = LightGuide1->GetLightGuideWidth() + 1.0*cm;
  else
    DetFullLengthX1 = 2*PMT1->GetRadius() +1.0*cm;
  
  if(LightGuide1->GetLightGuideDepth() > 2*PMT1->GetRadius())
    DetFullLengthZ1 = LightGuide1->GetLightGuideDepth() + 2*PMTToQuartzOffset1 + 4.0*cm;
  else
    DetFullLengthZ1 = 2*PMT1->GetRadius() + 2*PMTToQuartzOffset1 + 4.0*cm;
  
  //Ring 2
  if(LightGuide2->GetLightGuideWidth() > 2*PMT2->GetRadius())
    DetFullLengthX2 = LightGuide2->GetLightGuideWidth() + 1.0*cm;
  else
    DetFullLengthX2 = 2*PMT2->GetRadius() +1.0*cm;
  
  if(LightGuide2->GetLightGuideDepth() > 2*PMT2->GetRadius())
    DetFullLengthZ2 = LightGuide2->GetLightGuideDepth() + 2*PMTToQuartzOffset2 + 4.0*cm;
  else
    DetFullLengthZ2 = 2*PMT2->GetRadius() + 2*PMTToQuartzOffset2 + 4.0*cm;
  

  DetFullLengthY1 = Quartz1->GetQuartzSizeY()+LightGuide1->GetLightGuideLength()+PMT1->GetPMTLength()+1.0*cm+LightGuide1->GetCurrentMiddleBoxHeight();
  DetFullLengthY2 = Quartz2->GetQuartzSizeY()+LightGuide2->GetLightGuideLength()+PMT2->GetPMTLength()+1.0*cm+LightGuide2->GetCurrentMiddleBoxHeight();
}

void MOLLEROptDetector::ResetCenterLocation()
{
  /*PositionDetX1 = 0.0*cm;
  PositionDetY1 = 0.0*cm;//DetFullLengthY/2 - Quartz->GetQuartzSizeY()/2;
  PositionDetZ1 = 0.0*cm;

  PositionDet1.setX(PositionDetX1);
  PositionDet1.setY(PositionDetY1);
  PositionDet1.setZ(PositionDetZ1);  

  PositionDetX2 = 0.0*cm;
  PositionDetY2 = 0.0*cm;
  PositionDetZ2 = 0.0*cm;

  PositionDet2.setX(PositionDetX2);
  PositionDet2.setY(PositionDetY2);
  PositionDet2.setZ(PositionDetZ2);*/
}

void MOLLEROptDetector::Initialize()
{
  //let these objects setup their default solids and logical volumes
  PMTToQuartzOffset1 = 0;
  PMTToQuartzOffset2 = 0;
  AzimuAngle = 0; 
  PolarAngle = 0;
  Quartz1->Initialize();
  LightGuide1->Initialize();
  PMT1->Initialize();
  Quartz2->Initialize();
  LightGuide2->Initialize();
  PMT2->Initialize();
  
  CalculateDimensions();
  ResetCenterLocation();

  RotationDet = new G4RotationMatrix;

  DetSolid = new G4Box(DetType1+"_Solid",
		       10* DetFullLengthX1, 
		       5* DetFullLengthY1,
		       10* DetFullLengthZ1);
  /*DetSolid2 = new G4Box(DetType2+"_Solid",
		       0.5* DetFullLengthX2, 
		       0.5* DetFullLengthY2,
		       0.5* DetFullLengthZ2);*/
  
  DetLogical = new G4LogicalVolume( DetSolid, DetMaterial, DetType1+"_Logical");
  //DetLogical2 = new G4LogicalVolume( DetSolid2, DetMaterial, DetType2+"_Logical");

}

G4VPhysicalVolume* MOLLEROptDetector::ConstructDetector(G4VPhysicalVolume* Mother)
{
  if(!Mother) return 0;
  
  if(!MotherVolume){
    MotherVolume = Mother;
  }

  DetPhysical = new G4PVPlacement(RotationDet,
				  PositionDet1,   
				  DetType1+"_Physical",
				  DetLogical,
				  MotherVolume,false,1);    
  /*DetPhysical2 = new G4PVPlacement(RotationDet,
				  PositionDet2,   
				  DetType2+"_Physical",
				  DetLogical2,
				  MotherVolume,false,1);*/
  
  G4double quartzY1 = Quartz1->GetQuartzSizeY();
  G4double quartzZ1 = Quartz1->GetQuartzSizeZ();  
  G4double lguideY1 = LightGuide1->GetCurrentUpperInterfacePlane();
  G4double quartzY2 = Quartz2->GetQuartzSizeY();
  G4double quartzZ2 = Quartz2->GetQuartzSizeZ();
  G4double lguideY2 = LightGuide2->GetCurrentUpperInterfacePlane();

  G4double Qrot = Quartz1->GetQuartzRotationX();
     
  //Ring 1
  Quartz1->Construct(DetPhysical);
  Quartz1->SetCenterPositionInZ(0.5*quartzY1*(TMath::Sin(Qrot)) + PositionDetZ1);
  Quartz1->SetCenterPositionInY(-0.5*DetFullLengthY1 + 0.5*quartzY1 + 0.5*quartzY1*(1.0-TMath::Cos(Qrot)) + 0.5*quartzZ1*fabs(TMath::Sin(Qrot)) + 5*mm + PositionDetY1);
  LightGuide1->Construct(DetPhysical);
  LightGuide1->SetCenterPositionInZ(PositionDetZ1);  
  LightGuide1->SetCenterPositionInY(-0.5*DetFullLengthY1+quartzY1 + 5*mm + PositionDetY1);// + 0.5*LightGuide->GetCurrentQuartzInterfaceOpeningY()*TMath::Sin(Qrot));
  PMT1->Construct(DetPhysical);
  // We have to let the PMT extend into the light guide lsig
  PMT1->SetCenterPositionInZ(PositionDetZ1);    
  PMT1->SetCenterPositionInY(-0.5*DetFullLengthY1+quartzY1+lguideY1+PMT1->GetPMTLength()/2.0 + 5.0*mm + LightGuide1->GetCurrentMiddleBoxHeight() + PositionDetY1);

  //Ring 2
  //Quartz2->Construct(DetPhysical2);
  Quartz2->Construct(DetPhysical);
  Quartz2->SetCenterPositionInZ(0.5*quartzY2*(TMath::Sin(Qrot)) + PositionDetZ2);
  Quartz2->SetCenterPositionInY(-0.5*DetFullLengthY2 + 0.5*quartzY2 + 0.5*quartzY2*(1.0-TMath::Cos(Qrot)) + 0.5*quartzZ2*fabs(TMath::Sin(Qrot)) + 5*mm + PositionDetY2);
  //LightGuide2->Construct(DetPhysical2);
  LightGuide2->Construct(DetPhysical);
  LightGuide2->SetCenterPositionInZ(PositionDetZ2);
  LightGuide2->SetCenterPositionInY(-0.5*DetFullLengthY2+quartzY2 + 5*mm + PositionDetY2);// + 0.5*LightGuide->GetCurrentQuartzInterfaceOpeningY()*TMath::Sin(Qrot));
  //PMT2->Construct(DetPhysical2);
  PMT2->Construct(DetPhysical);
  // We have to let the PMT extend into the light guide lsig
  PMT2->SetCenterPositionInZ(PositionDetZ2);  
  PMT2->SetCenterPositionInY(-0.5*DetFullLengthY2+quartzY2+lguideY2+PMT2->GetPMTLength()/2.0 + 5.0*mm + LightGuide2->GetCurrentMiddleBoxHeight() + PositionDetY2);

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
  G4double quartzY1 = Quartz1->GetQuartzSizeY();
  G4double quartzY2 = Quartz2->GetQuartzSizeY();
  
  G4ThreeVector Qpos1 = Quartz1->GetCurrentCenterPosition();
  G4ThreeVector Qpos2 = Quartz2->GetCurrentCenterPosition();
  
  G4double dz1 = 2*fabs(Qpos1.y())*TMath::Sin(PolarAngle/2)*TMath::Cos(PolarAngle/2);
  G4double dy1 = 2*fabs(Qpos1.y())*TMath::Sin(PolarAngle/2)*TMath::Sin(PolarAngle/2);
  G4double dz2 = 2*fabs(Qpos2.y())*TMath::Sin(PolarAngle/2)*TMath::Cos(PolarAngle/2);
  G4double dy2 = 2*fabs(Qpos2.y())*TMath::Sin(PolarAngle/2)*TMath::Sin(PolarAngle/2);
  
  G4ThreeVector Trans1 = G4ThreeVector(Qpos1.x(),Qpos1.y()+dy1,Qpos1.z()+dz1);
  G4ThreeVector Trans2 = G4ThreeVector(Qpos2.x(),Qpos2.y()+dy2,Qpos2.z()+dz2);
  
  G4ThreeVector LGpos1 = LightGuide1->GetCurrentCenterPosition();
  G4ThreeVector LGpos2 = LightGuide2->GetCurrentCenterPosition();
    
  G4VPhysicalVolume* MPhys1 = new G4PVPlacement(Rot1,
					       Trans1,   
					       DetType1+"_logV",
					       logV ,
					       Mother,false,1); 
  G4VPhysicalVolume* MPhys2 = new G4PVPlacement(Rot1,
					       Trans2,   
					       DetType2+"_logV",
					       logV ,
					       Mother,false,1);

    G4Colour green    (   0/255., 255/255.,   0/255.);
    G4VisAttributes *att2 = new G4VisAttributes(green);
    att2->SetVisibility(true);
    //att2->SetForceWireframe(true);
    logV->SetVisAttributes(att2);

    G4ThreeVector MPos1 = MPhys1->GetTranslation();
    G4ThreeVector MPos2 = MPhys2->GetTranslation();

    
  }  
}


//Ring 1 objects
void MOLLEROptDetector::SetCenterPositionInX1(G4double xPos)
{
    PositionDetX1 = xPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX1,
					      PositionDetY1, 
					      PositionDetZ1));
}

void MOLLEROptDetector::SetCenterPositionInY1(G4double yPos)
{
    PositionDetY1 = yPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX1,
					      PositionDetY1, 
					      PositionDetZ1));
}

void MOLLEROptDetector::SetCenterPositionInZ1(G4double zPos)
{
    PositionDetZ1 = zPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX1,
					      PositionDetY1, 
					      PositionDetZ1));
}

//Ring 2 objects
void MOLLEROptDetector::SetCenterPositionInX2(G4double xPos)
{
    PositionDetX2 = xPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX2,
					      PositionDetY2, 
					      PositionDetZ2));
}

void MOLLEROptDetector::SetCenterPositionInY2(G4double yPos)
{
    PositionDetY2 = yPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX2,
					      PositionDetY2, 
					      PositionDetZ2));
}

void MOLLEROptDetector::SetCenterPositionInZ2(G4double zPos)
{
    PositionDetZ2 = zPos;

    DetPhysical->SetTranslation(G4ThreeVector(PositionDetX2,
					      PositionDetY2, 
					      PositionDetZ2));
}

//General objects (with edits)
void MOLLEROptDetector::SetLightGuideOffsetInX(G4double x)
{
  G4double cX1;
  G4double cX2;

  if(LightGuide1 &&  PMT1){
    cX1 = LightGuide1->GetCurrentCenterPositionInX() + x*cm;
    LightGuide1->SetCenterPositionInX(cX1);
    cX1 = PMT1->GetCurrentCenterPositionInX() + x*cm;
    PMT1->SetCenterPositionInX(cX1);
  }

  if(LightGuide2 &&  PMT2){
    cX2 = LightGuide2->GetCurrentCenterPositionInX() + x*cm;
    LightGuide2->SetCenterPositionInX(cX2);
    cX2 = PMT2->GetCurrentCenterPositionInX() + x*cm;
    PMT2->SetCenterPositionInX(cX2);
  }
}

void MOLLEROptDetector::SetLightGuideOffsetInY(G4double y)
{
  G4double cY1;
  G4double cY2;
  
  if(LightGuide1 &&  PMT1){
    cY1 = LightGuide1->GetCurrentCenterPositionInY() + y*cm;
    LightGuide1->SetCenterPositionInY(cY1);
    cY1 = PMT1->GetCurrentCenterPositionInY() + y*cm;
    PMT1->SetCenterPositionInY(cY1);
  }
  if(LightGuide2 &&  PMT2){
    cY2 = LightGuide2->GetCurrentCenterPositionInY() + y*cm;
    LightGuide2->SetCenterPositionInY(cY2);
    cY2 = PMT2->GetCurrentCenterPositionInY() + y*cm;
    PMT2->SetCenterPositionInY(cY2);
  }
}

void MOLLEROptDetector::SetLightGuideOffsetInZ(G4double z)
{
  G4double cZ1;
  G4double cZ2;
  
  if(LightGuide1 &&  PMT1){
    cZ1 = LightGuide1->GetCurrentCenterPositionInZ() + z*cm;
    LightGuide1->SetCenterPositionInZ(cZ1);
    cZ1 = PMT1->GetCurrentCenterPositionInZ() + z*cm;
    PMT1->SetCenterPositionInZ(cZ1);
  }
  if(LightGuide2 &&  PMT2){
    cZ2 = LightGuide2->GetCurrentCenterPositionInZ() + z*cm;
    LightGuide2->SetCenterPositionInZ(cZ2);
    cZ2 = PMT2->GetCurrentCenterPositionInZ() + z*cm;
    PMT2->SetCenterPositionInZ(cZ2);
  }
}

void MOLLEROptDetector::GetQuartzLimits(G4double *vals)
{
  Quartz1->GetQuartzLimits(vals);
  Quartz2->GetQuartzLimits(vals);
}

void MOLLEROptDetector::GetLightGuideLimits(G4double *vals)
{
  LightGuide1->GetLightGuideLimits(vals);
  LightGuide2->GetLightGuideLimits(vals);
}

void MOLLEROptDetector::SetMaterial(G4String materialName)
{
  DetMaterial = Materials->GetMaterial(materialName);
}

