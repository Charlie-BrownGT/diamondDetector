#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	G4double A = 12.01 * g/mole;
   	G4double Z = 6.;
   	G4Material* diamond = new G4Material("diamond", Z, A, 3.515*g/cm3);
	
	G4double boxSize = 0.5*m;
	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexWorld[2] = {1.0, 1.0};
	
	G4double diamondX = 4.5*mm;
	G4double diamondY = 4.5*mm;
	G4double diamondZ = 0.5*mm;
	//need to add refractive index to diamond
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	G4Box *solidWorld = new G4Box("solidWorld", boxSize, boxSize, boxSize);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	G4Box *solidDiamond = new G4Box("solidDiamond", diamondX, diamondY, diamondZ);
	G4LogicalVolume *logicDiamond = new G4LogicalVolume(solidDiamond, diamond, "logicDiamond");
	G4VPhysicalVolume *physDiamond = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.1*m), logicDiamond, "physDiamond", logicWorld, false, 0, true);
		
	return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
	//MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	//logicDetector->SetSensitiveDetector(sensDet);
}
