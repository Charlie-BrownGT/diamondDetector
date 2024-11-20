#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include <string>
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Para.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"

#include "G4GenericMessenger.hh"

#include "globals.hh"
#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	virtual void ConstructSDandField();
	
private:
	
	//defining the stuff for the user defined message
	G4VPhysicalVolume *physWorld, *physDD, *physSD, *physID, *physFinger;
	G4LogicalVolume *logicSD, *logicID, *logicDD, *logicFinger;
	G4Box *solidWorld, *solidDD, *solidSD, *solidFinger;
	
	//G4Tubs *solidID;
	G4Para *solidID;
	G4LogicalVolume *logicWorld;
	
	G4Material *vacuum, *diamond, *CF4, *YAPCe, *FeMat;
	G4Element *C, *F, *Y, *Ce, *Al, *O, *Fe;
	
	//defining user message on SD
	G4int nCols, nRows;
	G4GenericMessenger *fMessenger;

	G4double FingerPositionZ;
	
	G4double DDPositionz, DDPosition;
	G4GenericMessenger *gMessenger;
	
	G4double DDSize, DDSizexy;
	G4GenericMessenger *hMessenger;
	
	G4int SD, ID, DD;
	G4GenericMessenger *iMessenger;
	
	//virtual void ConstructSDandField();
	void DefineMaterials();
};
#endif
