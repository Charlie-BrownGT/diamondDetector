#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	G4PhysListUtil::InitialiseParameters();
	
	const G4double meanLife = 1*picosecond;  
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
