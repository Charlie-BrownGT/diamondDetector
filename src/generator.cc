#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4int n_particle = 1;
	fParticleGun = new G4ParticleGun(n_particle);
	
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("chargedgeantino");

	fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();

	if (particle == G4ChargedGeantino::ChargedGeantino()) 
	{  
		G4int Z = 11, A = 21;
		G4double ionCharge   = 11.*eplus;
		G4double excitEnergy = 0.*keV;
		G4ThreeVector pos(0.,0.,-0.25*m);
		G4ThreeVector mom(0.,0.,1.);
		G4double energy = 5.*MeV;
		
		G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
		
		fParticleGun->SetParticleEnergy(energy);
		fParticleGun->SetParticlePosition(pos);
		fParticleGun->SetParticleMomentumDirection(mom);
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(ionCharge);
  	}      
  	fParticleGun->GeneratePrimaryVertex(anEvent);
}
