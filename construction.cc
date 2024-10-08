#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	fMessenger = new G4GenericMessenger(this, "/Sdetector/", "SDetector Construction");
	fMessenger->DeclareProperty("nCols", nCols, "Number of columns in SD");
	fMessenger->DeclareProperty("nRows", nRows, "Number of rows in SD");
	nCols = 10; 
	nRows = 10; 
	
	DDPosition = 40.;
	gMessenger = new G4GenericMessenger(this, "/DDPos/", "DD position in z (cm)");
	gMessenger->DeclareProperty("DDPosition", DDPosition, "Position of DD in z (cm)");
	
	DDSize = 2.25;
	hMessenger = new G4GenericMessenger(this, "/DDSize/", "DD size in x and y(mm)");
	hMessenger->DeclareProperty("DDSize", DDSize, "Size of DD in x and y(mm)");
	
	SD = 0, ID = 1, DD = 1;
	iMessenger = new G4GenericMessenger(this, "/DetectorsOnOrOff/", "Detector status");
	iMessenger->DeclareProperty("SD", SD, "SD on = 1, off = 0"); 
	iMessenger->DeclareProperty("ID", ID, "ID on = 1, off = 0"); 
	iMessenger->DeclareProperty("DD", DD, "DD on = 1, off = 0"); 
	
	
	DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
	//material properties defined here, placed here to avoid redeclaration if geometry is changed
	G4NistManager *nist = G4NistManager::Instance();
	
	G4double z, a;
	G4double density = 1.e-25*g/cm3, pressure = 1.e-5*pascal, temperature = 2.73 * kelvin;
	vacuum = new G4Material("Vacuum", z=1., a=1.008 * g/mole, density, kStateGas, temperature, pressure);
	C  = new G4Element("Carbon","C" , 6., 12.00*g/mole);
	F  = new G4Element("Flourine","F" , 9., 38.00*g/mole);
	diamond = new G4Material("diamond", 3.515*g/cm3, 1);
	diamond->AddElement(C, 100.0*perCent);
	CF4 = new G4Material("CF4", 88*g/mole, 2);
	CF4->AddElement(C, 13.65*perCent);
	CF4->AddElement(F, 86.35*perCent);
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	//detector sizes and positions defined here, note, G4 draws a 0.5m box as 1m3
	G4double xWorld = 0.5*m, yWorld = 0.5*m, zWorld = 1.*m;
	G4double innerRadius = 0*cm, outerRadius = 40*cm, hz = 10*cm, startAngle = 0.*deg, spanningAngle = 360.*deg;
	
	DDPositionz = DDPosition*cm;
	
	DDSizexy = DDSize*mm;
	//G4double diamondSize = 10.0*mm;
	
	
	G4double diamondZ = 0.25*mm;
	G4ThreeVector DDposition(0., 0., DDPositionz);
	G4ThreeVector IDposition(0., 0., 85.*cm); //ID hz = 10cm
	G4double physSDz = 0.99*m;
	
	//volumes defined here
	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
	logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.*cm), logicWorld, "physWorld", 0, false, 0, true);
	
	solidDD = new G4Box("solidDD", DDSizexy, DDSizexy, diamondZ);
	logicDD = new G4LogicalVolume(solidDD, diamond, "logicDD");
	G4VisAttributes* visAttributesDD = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // Green color
	visAttributesDD->SetVisibility(true);
	visAttributesDD->SetForceSolid(true);
	logicDD->SetVisAttributes(visAttributesDD);
	physDD = new G4PVPlacement(0, DDposition, logicDD, "physDD", logicWorld, false, 0, true);
	
	solidID = new G4Tubs("solidID", innerRadius, outerRadius, hz, startAngle, spanningAngle);      
	logicID = new G4LogicalVolume(solidID, CF4, "logicID");
	G4VisAttributes* visAttributesID = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Red color
	visAttributesID->SetVisibility(true);
	visAttributesID->SetForceSolid(true);
	logicID->SetVisAttributes(visAttributesID);
	physID = new G4PVPlacement(0, IDposition, logicID, "physID", logicWorld, false, 0);
	
	solidSD = new G4Box("solidSD", xWorld/nRows, yWorld/nCols, 0.01*m);
	logicSD = new G4LogicalVolume(solidSD, vacuum, "logicSD");
	G4VisAttributes* visAttributesSD = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0)); // Blue color
	visAttributesSD->SetVisibility(true);
	visAttributesSD->SetForceSolid(true);
	logicSD->SetVisAttributes(visAttributesSD);
	for(G4int i = 0; i < nRows; i++) {
		for(G4int j = 0; j < nCols; j++) {
			physSD = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/nRows, -0.5*m+(j+0.5)*m/nCols, physSDz), logicSD, "physSD", logicWorld, false, j+i*nCols, false);
		}
	}
		
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	//varying detector usage here, detectors are turned on and off via the variable definitions SD, ID and DD	
	//G4cout << SD << G4endl;
	//G4cout << ID << G4endl;
	//G4cout << DD << G4endl;
	
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
