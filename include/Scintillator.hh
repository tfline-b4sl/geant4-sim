#ifndef SCINTILLATOR_h
#define SCINTILLATOR_h

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Element.hh>
#include <G4MaterialPropertiesTable.hh>
#include <G4String.hh>
#include <G4Types.hh>
#include <G4VSensitiveDetector.hh>
#include "G4THitsCollection.hh"
#include "G4SDManager.hh"

class Scintillator : public G4VSensitiveDetector{
    public:
    Scintillator(G4String name, G4int ids);
    virtual ~Scintillator();
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    private:
        G4int nID;
public:
        static G4Material* GetMaterial(){
            return CreatePVT();
        }
        static G4Material* CreatePVT() {
            G4double density = 1.032 * g/cm3;
            G4Material* pvt = new G4Material("PVT_Scintillator", density,2);
            G4NistManager* nist = G4NistManager::Instance();
            G4Element* C = nist->FindOrBuildElement("C");
            G4Element* H = nist->FindOrBuildElement("H");
            pvt->AddElement(C,9);
            pvt->AddElement(H,10);
            AddProperties(pvt);
            return pvt;
        }
        static void AddProperties(G4Material* pvt){
            G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
            const G4int nEntries = 9;
            G4double photonEnergy[nEntries] = {
                        2.95*eV,  // 420 nm
                        2.98*eV,  // 416 nm
                        3.01*eV,  // 412 nm
                        3.04*eV,  // 408 nm
                        3.07*eV,  // 404 nm
                        3.10*eV,  // 400 nm
                        3.13*eV,  // 396 nm
                        3.16*eV,  // 392 nm
                        3.19*eV   // 389 nm
            };
            G4double scintillation[nEntries] = {
                        1.00,
                        0.95,
                        0.85,
                        0.70,
                        0.50,
                        0.30,
                        0.15,
                        0.07,
                        0.03
            };
            mpt->AddProperty("FASTCOMPONENT",photonEnergy,scintillation,nEntries,true);
            mpt->AddConstProperty("SCINTILLATIONYIELD", 10000./CLHEP::MeV);
            mpt->AddConstProperty("RESOLUTONSCALE",1.0,true);
            mpt->AddConstProperty("FASTTIMECONSTANT",2.5*ns,true);
            mpt->AddConstProperty("YIELDRATIO", 1.0,true);
            G4double refractiveIndex[nEntries];
            G4double absorptionLength[nEntries];
            for (int i = 0; i < nEntries; i++){
              refractiveIndex[i] = 1.58;
              absorptionLength[i] = 50.*cm;
            }
            mpt->AddProperty("RINDEX",photonEnergy,refractiveIndex,nEntries);
            mpt->AddProperty("ABSLENGTH", photonEnergy,absorptionLength,nEntries);
            pvt->SetMaterialPropertiesTable(mpt);
      }
};


#endif