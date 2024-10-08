#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());
	//RegisterPhysics (new G4OpticalPhysics());
	
	//RegisterPhysics (new G4HadronElasticPhysicsXS());
	//RegisterPhysics (new G4HadronPhysicsQGSP_BIC_HP());
	//RegisterPhysics (new G4IonElasticPhysics());
	//RegisterPhysics (new G4IonPhysicsXS());
}

MyPhysicsList::~MyPhysicsList()
{}
