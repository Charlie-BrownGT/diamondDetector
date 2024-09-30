#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

#include "G4IonTable.hh"
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"

#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
        MyPrimaryGenerator();
        ~MyPrimaryGenerator();
        
        void GeneratePrimaries(G4Event* anEvent);

private:
	G4GeneralParticleSource* particleGun;
};
#endif
