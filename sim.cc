#include "G4Types.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4SteppingVerbose.hh"
#include "Randomize.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "G4ParticleHPManager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc,char** argv){

	//define ui session
	G4UIExecutive* ui = nullptr;
	//if (argc == 1) ui = new G4UIExecutive(argc, argv);
	
	//use G4 stepping with verbose units
	G4int precision = 4;
	G4SteppingVerbose::UseBestUnit(precision);

	//construct the run manager
	auto runManager = G4RunManagerFactory::CreateRunManager();
	if (argc == 3){
		G4int nThreads = G4UIcommand::ConvertToInt(argv[2]);
		runManager->SetNumberOfThreads(nThreads);
	}
	
	//set the required initialization classes
	DetectorConstruction* det = new DetectorConstruction;
	runManager->SetUserInitialization(det);
	
	PhysicsList* phys = new PhysicsList;
	runManager->SetUserInitialization(phys);
	runManager->SetUserInitialization(new Actioninitialization(det));
	
	//replaced HP environmental variables with C++ calls
	G4ParticleHPManager::GetInstance()->SetSkipMissingIsotopes( false );
	G4ParticleHPManager::GetInstance()->SetDoNotAdjustFinalState( true );
	G4ParticleHPManager::GetInstance()->SetUseOnlyPhotoEvaporation( true );
	G4ParticleHPManager::GetInstance()->SetNeglectDoppler( false );
	G4ParticleHPManager::GetInstance()->SetProduceFissionFragments( true );
	G4ParticleHPManager::GetInstance()->SetUseWendtFissionModel( false );
	G4ParticleHPManager::GetInstance()->SetUseNRESP71Model( false );
	
	//initialize visualization
	//G4VisManager* visManager = nullptr;
	
	if (argc == 1){
		ui = new G4UIExecutive(argc, argv);
	}
	
	//initialize visualization
	G4VisManager* visManager = new G4visExecutive();
	visManager->Initialize();
	
	//get the pointer to the user interface manager
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui){
		//for interactive mode
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
	}
	else {
		//for batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
        }
	
	//job termination
	delete visManager;
	delete runManager;
}
