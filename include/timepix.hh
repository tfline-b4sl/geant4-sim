#ifndef TIMEPIX_h
#define TIMEPIX_h

#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"
#include <G4String.hh>
#include <G4Types.hh>

class Timepix: public G4VSensitiveDetector {
public:
Timepix(G4String name, G4int ids);
virtual ~Timepix();
virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
private:
G4int nID;
};

#endif