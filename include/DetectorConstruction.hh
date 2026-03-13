#ifndef DETECTORCONSTRUCTION_h
#define DETECTORCONSTRUCTION_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include <G4Box.hh>
#include "../include/config.hh"
#include "../include/Scintillator.hh"
#include "../include/cherenkov.hh"
#include "../include/timepix.hh"
#include "../include/calorimeter.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include <vector>

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction(G4int*, std::string fName);
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    G4LogicalVolume* GetWorldLog() const {return wLog;}

private:
    SystemConfig *sConf;

    std::vector<Scintillator*> scints;
    std::vector<Cherenkov*> chers;
    std::vector<Calorimeter*> ecals;
    std::vector<Timepix*> times;

    G4Box** detectors;
    G4VPhysicalVolume** phys;
    G4LogicalVolume** logs;

    G4Box* world;
    G4VPhysicalVolume* wPhys;
    G4LogicalVolume* wLog;

    struct Position {
        G4double x, y, z;
        Position(G4double a, G4double b, G4double c) : x(a), y(b), z(c) {}
        G4ThreeVector vec() const { return G4ThreeVector(x*cm, y*cm, z*cm); }
    };
    G4int* nID;

    G4FieldManager* localFieldManager;
    G4UniformMagField *magField;
};

#endif