#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "Randomize.hh"

class G4Event;

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
        MyPrimaryGenerator();
        ~MyPrimaryGenerator();

        void GeneratePrimaries(G4Event*);
        G4ParticleGun* GetParticleGun() { return fParticleGun;} ;

private:
	G4ParticleGun*  fParticleGun = nullptr;
};
#endif
