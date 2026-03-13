#ifndef CALORIMETER_h
#define CALORIMETER_h

#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"
#include <G4String.hh>
#include <G4Types.hh>
class Calorimeter: public G4VSensitiveDetector {
public:
Calorimeter(G4String name, G4int ids);
virtual ~Calorimeter();
virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
private:
    G4int nID;
};

#endif
