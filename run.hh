#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4GenericMessenger.hh"

#include "globals.hh"

class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction();
	~MyRunAction();
	
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
	
private:
	G4double DDPositionz, DDPosition;
	G4GenericMessenger *gMessenger2;
	
	G4double DDSize, DDSizexy, DDSizePH;
	G4GenericMessenger *hMessenger2;
	
	G4int SD, ID, DD;
	G4GenericMessenger *iMessenger2;
};
#endif
