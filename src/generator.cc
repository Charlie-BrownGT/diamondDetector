#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle); //set the number of particles per event

	G4ThreeVector pos(0.,0.,0.);
	G4ThreeVector momDir(0.,0.,1.);
	G4double mom = 5.*MeV;

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(momDir);
	fParticleGun->SetParticleMomentum(mom);

	//fParticleGun->SetParticleEnergy(0*eV);
	//fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	//fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{	
	if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {  
	    G4int Z = 11, A = 21;
	    G4double ionCharge   = 11.*eplus;
	    G4double excitEnergy = 0.*keV;
	    
	    G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
	    fParticleGun->SetParticleDefinition(ion);
	    fParticleGun->SetParticleCharge(ionCharge);
  	}      
  	fParticleGun->GeneratePrimaryVertex(anEvent);
}
