#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	//World volume
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0);
	
	//Diamond material definition 
	G4double A = 12.01 * g/mole; 
	G4int Z = 6.0;
	G4Material* diamond = new G4Material("diamond", Z, A, 3.515*g/cm3);
	
	//Diamond detector volume
	G4Box *solidDetector1 = new G4Box("solidDetector1", 0.0045*m, 0.0045*m, 0.0005*m);
	logicDetector1 = new G4LogicalVolume(solidDetector1, diamond, "logicDetector1");
	G4VPhysicalVolume *physDetector1 = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.1*m), logicDetector1, "physDetector1", logicWorld, false, 0, true);

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	//Detector definition
	MySensitiveDetector *sensDet1 = new MySensitiveDetector("Sensitive Detector1");
	logicDetector1->SetSensitiveDetector(sensDet1);
}
