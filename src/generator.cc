#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);
	
	fParticleGun->SetParticleEnergy(0*eV);
	fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {  
	    G4int Z = 10, A = 24;
	    G4double ionCharge   = 1.*eplus;
	    G4double excitEnergy = 0.*keV;
	    
	    G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
	    fParticleGun->SetParticleDefinition(ion);
	    fParticleGun->SetParticleCharge(ionCharge);
  	}      
  	fParticleGun->GeneratePrimaryVertex(anEvent);
}
