#include "run.hh"
#include "construction.hh"

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	DDPosition = 40.;
	gMessenger2 = new G4GenericMessenger(this, "/DDPos2/", "DD position in z (cm)");
	gMessenger2->DeclareProperty("DDPosition", DDPosition, "Position of DD in z (cm)");
	
	DDSize = 2.25;
	hMessenger2 = new G4GenericMessenger(this, "/DDSize2/", "DD size in x and y(mm)");
	hMessenger2->DeclareProperty("DDSize", DDSize, "Size of DD in x and y(mm)");
	
	SD = 1, ID = 0, DD = 1;
	iMessenger2 = new G4GenericMessenger(this, "/DetectorsOnOrOff2/", "Detector status");
	iMessenger2->DeclareProperty("SD", SD, "SD on = 1, off = 0"); 
	iMessenger2->DeclareProperty("ID", ID, "ID on = 1, off = 0"); 
	iMessenger2->DeclareProperty("DD", DD, "DD on = 1, off = 0"); 
	
	man->CreateNtuple("Position", "Position");
	man->CreateNtupleIColumn("Event");
	man->CreateNtupleDColumn("X");
	man->CreateNtupleDColumn("Y");
	man->CreateNtupleDColumn("Z");
	man->FinishNtuple(0);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4cout << SD << G4endl;
	G4cout << ID << G4endl;
	G4cout << DD << G4endl;
	
	//DD position string
	std::stringstream DDPosStr;
	DDPosStr << DDPosition;
	
	//DD size string
	DDSizePH = 2 * DDSize;
	std::stringstream DDSizeStr;
	DDSizeStr << DDSizePH;
	
	//angular componenet to file name
	G4double runID = run->GetRunID();
	runID = runID / 2.;
	std::stringstream strRunID;
	strRunID << runID;
	
	//Detectors on or off
	//std::stringstream IDStr, DDStr;
	G4String IDStr, DDStr;
	if (ID == 1){IDStr = "On";}
	if (ID == 0){IDStr = "Off";}
	if (DD == 1){DDStr = "On";}
	if (DD == 0){DDStr = "Off";}
	
	
	man->OpenFile("75cmIDpos"+DDPosStr.str()+"cmDDpos_"+DDSizeStr.str()+"mmDD_ID"+IDStr+"DD"+DDStr+"_ang"+strRunID.str()+".root");
	//man->OpenFile("75cmIDOff_70cmDD_20mmOn"+strRunID.str()+".root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
