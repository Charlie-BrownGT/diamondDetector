#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	//define nist
	G4NistManager *nist = G4NistManager::Instance();
	
	//define materials used
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4Element *C = nist->FindOrBuildElement("C");
	G4Element *F = nist->FindOrBuildElement("F");
	
	G4Material *diamond = new G4Material("diamond", 3.515*g/cm3, 1);
	G4Material *CF4 = new G4Material("C4F", 88*g/mole, 2);
	
	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
	G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
	G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
	
	G4Material* test  = nist->FindOrBuildMaterial("G4_CARBON_TETRACHLORIDE");
	
	//add elements to materials used
	diamond->AddElement(nist->FindOrBuildElement("C"), 4);
	CF4->AddElement(nist->FindOrBuildElement("C"), 1);
	CF4->AddElement(nist->FindOrBuildElement("C"), 4);
	
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
	H2O->AddElement(nist->FindOrBuildElement("H"), 2);
	H2O->AddElement(nist->FindOrBuildElement("O"), 1);
	
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 0.1*perCent);
	
	//define variables of volumes 
	G4double diamondX = 4.5*mm;
	G4double diamondY = 4.5*mm;
	G4double diamondZ = 0.5*mm;
	
	G4double innerRadius = 0*cm;
	G4double outerRadius = 15*cm;
	G4double hz = 15*cm;
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;
	
	G4double boxSize = 0.5*m;
	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexWorld[2] = {1.0, 1.0};
	G4double rindexDiamond[2] = {2.4168, 2.4168};
	G4double rindexCF4[2] = {1.00045, 1.00045};
	G4double rindexAerogel[2] = {1.1, 1.1};
	
	//define material property tables 
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	G4MaterialPropertiesTable *mptDiamond = new G4MaterialPropertiesTable();
	mptDiamond->AddProperty("RINDEX", energy, rindexDiamond, 2);
	diamond->SetMaterialPropertiesTable(mptDiamond);
	
	G4MaterialPropertiesTable *mptCF4 = new G4MaterialPropertiesTable();
	mptCF4->AddProperty("RINDEX", energy, rindexCF4, 2);
	CF4->SetMaterialPropertiesTable(mptCF4);
	
	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
	Aerogel->SetMaterialPropertiesTable(mptAerogel);
	
	//define volumes
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	G4Box *solidDiamond = new G4Box("solidDiamond", diamondX, diamondY, diamondZ);
	G4LogicalVolume *logicDiamond = new G4LogicalVolume(solidDiamond, diamond, "logicDiamond");
	G4VPhysicalVolume *physDiamond = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.*m), logicDiamond, "physDiamond", logicWorld, false, 0, true);
	
	G4Tubs* solidITub = new G4Tubs("solidITub", innerRadius, outerRadius, hz, startAngle, spanningAngle);      
	G4LogicalVolume* logicITub = new G4LogicalVolume(solidITub, CF4, "logicITub");
	G4VPhysicalVolume* physITub = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.25*m), logicITub, "physITub", logicWorld, false, 0);
	
	//G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);
	//logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
	//G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.49*m), logicDetector, "physDetector", logicWorld, false, 0, false);
	
	G4Box *solidDetector = new G4Box("solidDetector", 0.05*m, 0.05*m, 0.01*m);
	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
	for(G4int i = 0; i < 10; i++)
	{
		for(G4int j = 0; j < 10; j++)
		{
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/10, -0.5*m+(j+0.5)*m/10, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*10, false);
		}
	}
	
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	logicDetector->SetSensitiveDetector(sensDet);
}
