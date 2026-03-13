#ifndef PRIMARYGENERATOR_h
#define PRIMARYGENERATOR_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include <G4ThreeVector.hh>
#include <G4Types.hh>
#include "G4ParticleGun.hh"
class G4Event;

class PrimaryGenerator : public G4VUserPrimaryGeneratorAction{
    public:
    PrimaryGenerator();
    virtual ~PrimaryGenerator();
    virtual void GeneratePrimaries(G4Event*);

    void setParticle(const G4String& name){
        Name = name;
    }
    void setEnergy(G4double e) {
        Energy = e;
    }
    void setPosition(const G4ThreeVector& pos) {
        Position = pos;
    }
    void setDirection(const G4ThreeVector& dir) {
        Direction = dir;
    }


    private:
    G4ParticleGun* Gun;
    G4String Name;
    G4double Energy;
    G4ThreeVector Position;
    G4ThreeVector Direction;
};

#endif