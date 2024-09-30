#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "G4Types.hh"
#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "Randomize.hh"
#include "G4ParticleHPManager.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
	G4RunManager *runManager = new G4RunManager();
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	runManager->Initialize();
	
	G4ParticleHPManager::GetInstance()->SetSkipMissingIsotopes( false );
	G4ParticleHPManager::GetInstance()->SetDoNotAdjustFinalState( true );
	G4ParticleHPManager::GetInstance()->SetUseOnlyPhotoEvaporation( true );
	G4ParticleHPManager::GetInstance()->SetNeglectDoppler( false );
	G4ParticleHPManager::GetInstance()->SetProduceFissionFragments( true );
	G4ParticleHPManager::GetInstance()->SetUseWendtFissionModel( false );
	G4ParticleHPManager::GetInstance()->SetUseNRESP71Model( false );
	
	G4UIExecutive *ui = 0;
	
	if(argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if(ui)
	{	
		UImanager->ApplyCommand("/control/execute visualization.mac");
		UImanager->ApplyCommand("/control/execute beam.mac");
		ui->SessionStart();
	}
	else 
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	
	delete ui;
	delete runManager;
	delete visManager;
}
