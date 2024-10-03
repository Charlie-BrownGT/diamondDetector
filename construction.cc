#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4double boxSize = 0.5*m; 
	
	//detector sizes and positions defined here
	G4double innerRadius = 0*cm, outerRadius = 15*cm, hz = 15*cm, startAngle = 0.*deg, spanningAngle = 360.*deg;
	G4ThreeVector DDposition(0., 0., -30*cm);
	G4double diamondX = 4.5*mm, diamondY = 4.5*mm, diamondZ = 0.5*mm;
	G4ThreeVector IDposition(0, 0, 0.25*m);
	
	//material properties defined here
	G4NistManager *nist = G4NistManager::Instance();
	G4double z, a;
	G4double density = 1.e-25*g/cm3, pressure = 1.e-5*pascal, temperature = 2.73 * kelvin;
	G4Material *vacuum = new G4Material("Vacuum", z=1., a=1.008 * g/mole, density, kStateGas, temperature, pressure);
	G4Element* C  = new G4Element("Carbon","C" , 6., 12.00*g/mole);
	G4Element* F  = new G4Element("Flourine","F" , 9., 38.00*g/mole);
	G4Material *diamond = new G4Material("diamond", 3.515*g/cm3, 1);
	diamond->AddElement(C, 100.0*perCent);
	G4Material *CF4 = new G4Material("CF4", 88*g/mole, 2);
	CF4->AddElement(C, 13.65*perCent);
	CF4->AddElement(F, 86.35*perCent);
	
	//volumes defined here
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	G4Box *solidDD = new G4Box("solidDD", diamondX, diamondY, diamondZ);
	logicDD = new G4LogicalVolume(solidDD, diamond, "logicDD");
	G4VPhysicalVolume *physDD = new G4PVPlacement(0, DDposition, logicDD, "physDD", logicWorld, false, 0, true);
	
	G4Tubs *solidID = new G4Tubs("solidID", innerRadius, outerRadius, hz, startAngle, spanningAngle);      
	logicID = new G4LogicalVolume(solidID, CF4, "logicID");
	G4VPhysicalVolume *physID = new G4PVPlacement(0, IDposition, logicID, "physID", logicWorld, false, 0);
	
	G4Box *solidSD = new G4Box("solidSD", 0.05*m, 0.05*m, 0.01*m);
	logicSD = new G4LogicalVolume(solidSD, vacuum, "logicSD");
	for(G4int i = 0; i < 10; i++)
	{
		for(G4int j = 0; j < 10; j++)
		{
			G4VPhysicalVolume *physSD = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/10, -0.5*m+(j+0.5)*m/10, 0.49*m), logicSD, "physSD", logicWorld, false, j+i*10, false);
		}
	}
		
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	//varying detector usage here, detectors are turned on and off via the variable definitions SD, ID and DD	
	
	double SD, ID, DD;
	SD = 1;
	ID = 1;
	DD = 1;
	
	if(SD == 1){
		MySensitiveDetector *sensSD = new MySensitiveDetector("SD");
		logicSD->SetSensitiveDetector(sensSD);
	}
	if(ID == 1){
		MySensitiveDetector *sensID = new MySensitiveDetector("ID");
		logicID->SetSensitiveDetector(sensID);
	}
	if(DD == 1){
		MySensitiveDetector *sensDD = new MySensitiveDetector("DD");
		logicDD->SetSensitiveDetector(sensDD);
	}
}
