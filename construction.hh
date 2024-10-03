#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

#include <string>
#include "globals.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();

	G4String SDtxt;
	G4String IDtxt;
	G4String DDtxt;
	
	virtual G4VPhysicalVolume *Construct();
	
private:
	G4LogicalVolume *logicSD;
	G4LogicalVolume *logicID;
	G4LogicalVolume *logicDD;
	virtual void ConstructSDandField();
};
#endif
