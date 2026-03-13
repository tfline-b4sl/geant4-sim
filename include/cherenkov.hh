#ifndef CHERENKOV_h
#define CHERENKOV_H


#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"
#include <G4String.hh>
#include <G4Types.hh>

class Cherenkov : public G4VSensitiveDetector {
public:
    Cherenkov(G4String name, G4int ids);
    virtual ~Cherenkov();
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
private:
    G4int nID;
};

#endif