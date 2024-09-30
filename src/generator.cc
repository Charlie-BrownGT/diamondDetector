#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	particleGun = new G4GeneralParticleSource();
	//G4int n_particle = 1;
	//fParticleGun = new G4ParticleGun(n_particle);
	//G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//G4ParticleDefinition *particle = particleTable->FindParticle("chargedgeantino");
	//fParticleGun->SetParticleDefinition(particle);
	//fParticleSource->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete particleGun;
	//delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
	particleGun -> GeneratePrimaryVertex(anEvent);
	//G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
	//G4ParticleDefinition* particle = fParticleSource->GetParticleDefinition();

	//if (particle == G4ChargedGeantino::ChargedGeantino()) 
	//{  
		//G4int Z = 11, A = 21;
		//G4double ionCharge = 11.*eplus;
		//G4double excitEnergy = 0.*keV;
		//G4ThreeVector pos(0.,0.,-0.25*m);
		//G4ThreeVector mom(0.,0.,1.);
		//G4double energy = 5.*MeV;
		
		//fParticleSource->SetParticleDefinition(G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy));
		//fParticleSource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(gauss);
		//fParticleSource->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
		//fParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(pos));
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetAngDistType("sin");
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
		
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetMinTheta(0.0);
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetMaxTheta(90.0 * deg);
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetMinPhi(0.0);
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetMaxPhi(360.0 * deg);
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetSigmaTheta(0.1 * deg);
		//fParticleSource->GetCurrentSource()->GetAngDist()->SetSigmaPhi(0.1 * deg);

		
		//G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
		//fParticleGun->SetParticleEnergy(energy);
		//fParticleGun->SetParticlePosition(pos);
		//fParticleGun->SetParticleMomentumDirection(mom);
		//fParticleGun->SetParticleDefinition(ion);
		//fParticleGun->SetParticleCharge(ionCharge);
		
		//fParticleSource->SetParticleEnergy(energy);
		//fParticleSource->SetParticlePosition(pos);
		//fParticleSource->GetParticleMomentumDirection();
		//fParticleSource->SetParticleDefinition(ion);
		//fParticleSource->SetParticleCharge(ionCharge);
  	//}   
  	
  	//fParticleGun->GeneratePrimaryVertex(anEvent);
  	//fParticleSource->GeneratePrimaryVertex(anEvent);
  	
}
