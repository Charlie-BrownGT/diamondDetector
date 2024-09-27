#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	//set verbosity level
	G4int verb = 1;  
 	SetVerboseLevel(verb);
	
	//set radioactive decay parameters
	G4PhysListUtil::InitialiseParameters();
	
	const G4double meanLife = 22.45*second;  
  	G4NuclideTable::GetInstance()->SetMeanLifeThreshold(meanLife);  
  	G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*eV);
	
	G4EmParameters::Instance()->SetDefaults();
  	G4EmParameters::Instance()->SetAugerCascade(true);
  	G4EmParameters::Instance()->SetDeexcitationIgnoreCut(true);
	
	G4DeexPrecoParameters* deex = G4NuclearLevelData::GetInstance()->GetParameters();
	deex->SetCorrelatedGamma(false);
	deex->SetStoreAllLevels(true);
	deex->SetInternalConversionFlag(true);	  
	deex->SetIsomerProduction(true);  
	deex->SetMaxLifeTime(meanLife);
	SetDefaultCutValue(1*mm);
	
	//register required physics
	RegisterPhysics ( new G4EmStandardPhysics());
	RegisterPhysics ( new G4OpticalPhysics());
	
	// Hadron Elastic scattering
	RegisterPhysics( new G4HadronElasticPhysicsXS(verb));
	// Hadron Inelastic physics
	RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));
	// Ion Elastic scattering
	RegisterPhysics( new G4IonElasticPhysics(verb));
	// Ion Inelastic physics
	RegisterPhysics( new G4IonPhysicsXS(verb));
	// Radioactive decay
	RegisterPhysics( new G4RadioactiveDecayPhysics());
	// Gamma physics
	//RegisterPhysics( new GammaNuclearPhysics("gamma"));
}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::ConstructParticle()
{
  G4EmBuilder::ConstructMinimalEmSet();
}

void MyPhysicsList::ConstructProcess()
{
	AddTransportation();

	G4Radioactivation* radioactiveDecay = new G4Radioactivation();

	G4bool ARMflag = false;
	radioactiveDecay->SetARM(ARMflag);

	G4LossTableManager* man = G4LossTableManager::Instance();
	G4VAtomDeexcitation* deex = man->AtomDeexcitation();
	
	if (nullptr == deex) {
		deex = new G4UAtomicDeexcitation();
		man->SetAtomDeexcitation(deex);
	}
	deex->InitialiseAtomicDeexcitation();

	G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
	ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
}
