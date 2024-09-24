#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->OpenFile("energy.root");
	
	man->CreateNtuple("Hits", "Ion energy data");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("energy");
	man->FinishNtuple(0);
	
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
