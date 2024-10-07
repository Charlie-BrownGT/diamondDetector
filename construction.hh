#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include <string>
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4GenericMessenger.hh"

#include "globals.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	
private:
	virtual void ConstructSDandField();
	
	//defining the stuff for the user defined message
	G4LogicalVolume *logicSD, *logicID, *logicDD;
	G4Box *solidWorld, *solidDD, *solidSD;
	G4Tubs *solidID;
	G4LogicalVolume *logicWorld;
	G4VPhysicalVolume *physWorld, *physDD, *physSD, *physID;
	G4Material *vacuum, *diamond, *CF4;
	G4Element *C, *F;
	
	G4int nCols, nRows;
	G4GenericMessenger *fMessenger;
	
	//G4GenericMessenger *gMessenger;
	
	void DefineMaterials();
};
#endif
