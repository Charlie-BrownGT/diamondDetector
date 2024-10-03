#include "run.hh"

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->CreateNtuple("Position", "Position");
	man->CreateNtupleIColumn("Event");
	man->CreateNtupleDColumn("X");
	man->CreateNtupleDColumn("Y");
	man->CreateNtupleDColumn("Z");
	man->FinishNtuple(0);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4double SD, ID, DD;
	SD = 1;
	ID = 1;
	DD = 1;
	
	//changing the file name of the root output here
	man->OpenFile("DD0cm_on_ID25cm_on_SD_off_beam-45cm_2deg.root");
	
	//if(SD == 1 && ID == 1 && DD == 1){
	//	man->OpenFile("SDon_IDon_DDon"+"45cmBeam.root");
	//}
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
