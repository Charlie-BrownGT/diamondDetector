#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	//Real world data
	G4ThreeVector posParticle = preStepPoint->GetPosition();
	G4cout << "Particle position: " << posParticle << G4endl;
	
	//Detector data
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();
	G4cout << "Detector number: " << copyNo << G4endl;
	
	//Detector position in world volume
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4cout << "Detector position: " << posDetector << G4endl;
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); //Gets event number
	
	//Fills the Ntuples defined in run.hh
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, evt);
	man->FillNtupleDColumn(1, posParticle[0]);
	man->FillNtupleDColumn(2, posParticle[1]);
	man->FillNtupleDColumn(3, posParticle[2]);
	man->AddNtupleRow(0);
	
	return true;
}
