#ifndef MOLLEROptQuartzSD_h
#define MOLLEROptQuartzSD_h 

#include "cpp_include.h"
#include "Geant4_include.hh"

#include "MOLLEROptQuartzHit.hh"
#include "MOLLEROptTrackingReadout.hh"

class G4Step;
class G4HCofThisEvent;

class MOLLEROptQuartzSD : public G4VSensitiveDetector
{

public:
  MOLLEROptQuartzSD(G4String name, MOLLEROptTrackingReadout* TrRO);
  virtual ~MOLLEROptQuartzSD();

  virtual void Initialize(G4HCofThisEvent* HCE);
  virtual G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
  virtual void EndOfEvent(G4HCofThisEvent* HCE);

private:

  MOLLEROptTrackingReadout* TrackingReadout;
  //MOLLEROptTrackingReadout* TrackingReadout2;  
  
  MOLLEROptQuartzHitsCollection*  HitsCollection;
  MOLLEROptQuartzHitsCollection*  HitsCollection2;
  MOLLEROptQuartzHitsCollection*  HitsCollection3;
  MOLLEROptQuartzHitsCollection*  HitsCollection4;
  MOLLEROptQuartzHitsCollection*  HitsCollection5;
  MOLLEROptQuartzHitsCollection*  HitsCollection6;
  MOLLEROptQuartzHitsCollection*  HitsCollection7;
  MOLLEROptQuartzHitsCollection*  HitsCollection8;
  
  G4String theCollectionName;
  //G4String theCollectionName2;  
  G4int theCollectionID;
  //G4int theCollectionID2;  
  const std::vector<const G4Track*>* Secondaries;

};
#endif

