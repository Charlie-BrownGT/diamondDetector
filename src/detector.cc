#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack(); //Gets track data
	//track->SetTrackStatus(fStopAndKill); //Stops particle once it's hit detector surface 
	
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //Gets particle entry point
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //Gets particle exit point
	
	G4double kineticEnergy = track->GetKineticEnergy();
	
	//Real world data
	G4ThreeVector posParticle = preStepPoint->GetPosition();
	G4cout << "Particle position: " << posParticle << G4endl;
	
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); //Gets event number
	
	//Fills the Ntuples defined in run.hh
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, evt);
	man->FillNtupleDColumn(1, kineticEnergy);
	man->AddNtupleRow(0);
	
	return true;
}
