#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	particleGun = new G4GeneralParticleSource();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete particleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
	particleGun -> GeneratePrimaryVertex(anEvent);
}
