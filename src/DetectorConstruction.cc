#include "../include/DetectorConstruction.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4Box.hh>
#include <G4EventManager.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4SDManager.hh>
#include <G4ThreeVector.hh>
#include <G4VUserDetectorConstruction.hh>
#include "G4LogicalVolume.hh"

DetectorConstruction::DetectorConstruction(G4int *id, std::string fName):G4VUserDetectorConstruction()
{
    nID = id;
    sConf = new SystemConfig(fName);
}

DetectorConstruction::~DetectorConstruction()
{
    delete[] detectors;
    delete[] logs;
    delete[] phys;
    
    delete sConf;
    
    
}
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    auto* nist = G4NistManager::Instance();
    G4Box* world = new G4Box("world",sConf->WorldX*m,sConf->WorldY*m, sConf->WorldZ*m);
    wLog = new G4LogicalVolume(world, nist->FindOrBuildMaterial("G4_Galactic"), "world");
    wPhys = new G4PVPlacement(nullptr,G4ThreeVector(),wLog,"world",nullptr,false,0);
    detectors = new G4Box*[sConf->DetectorN];
    logs = new G4LogicalVolume*[sConf->DetectorN];
    phys = new G4VPhysicalVolume*[sConf->DetectorN];
    for(int i = 0; i < sConf->DetectorN; ++i) {
        detectors[i] = new G4Box(sConf->Detectors[i].Name, sConf->Detectors[i].SizeX*cm, sConf->Detectors[i].SizeY*cm, sConf->Detectors[i].SizeZ*cm);
        switch(sConf->Detectors[i].Kind) {
            case ECAL:
                logs[i] = new G4LogicalVolume(detectors[i], nist->FindOrBuildMaterial("G4_PbWO4"), sConf->Detectors[i].Name);
                break;
            case CHERENKOV:
                logs[i] = new G4LogicalVolume(detectors[i],nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE"), sConf->Detectors[i].Name);
                break;
            case MAGNET:
                logs[i] = new G4LogicalVolume(detectors[i], nist->FindOrBuildMaterial("G4_Galactic"), sConf->Detectors[i].Name);
                break;
            case SCINTILLATOR:
                logs[i] = new G4LogicalVolume(detectors[i],Scintillator::GetMaterial(), sConf->Detectors[i].Name);
                G4cout << std::to_string(sizeof(G4PVPlacement)) << G4endl;
                break;
            case TARGET: {
                G4String matName = sConf->Material; 
                G4Material* targetMat = nullptr;

                if (matName == "G4_Fe") {
                    targetMat = nist->BuildMaterialWithNewDensity("Ozel_Fe", "G4_Fe", 7.874 * g/cm3);
                } 
                else if (matName == "G4_W") {
                    targetMat = nist->BuildMaterialWithNewDensity("Ozel_W", "G4_W", 19.3 * g/cm3);
                } 
                else if (matName == "G4_Pb") {
                    targetMat = nist->BuildMaterialWithNewDensity("Ozel_Pb", "G4_Pb", 11.34 * g/cm3);
                } 
                else if (matName == "G4_Cu") {
                    targetMat = nist->BuildMaterialWithNewDensity("Ozel_Cu", "G4_Cu", 8.93 * g/cm3);
                } 
                else {
                    targetMat = nist->FindOrBuildMaterial(matName); 
                }

                logs[i] = new G4LogicalVolume(detectors[i], targetMat, sConf->Detectors[i].Name);
                break;
            }
            
             
            case TIMEPIX:
                logs[i] = new G4LogicalVolume(detectors[i],nist->FindOrBuildMaterial("G4_Si"), sConf->Detectors[i].Name);
                break;
        }
        new G4PVPlacement(0,G4ThreeVector(sConf->Detectors[i].PosX*cm,sConf->Detectors[i].PosY*cm,sConf->Detectors[i].PosZ*cm), logs[i], sConf->Detectors[i].Name, wLog, false, 0);
    }
    return wPhys;
}

void DetectorConstruction::ConstructSDandField()
{

    G4SDManager* sdMan = G4SDManager::GetSDMpointer();
    Calorimeter* dummyCal;
    Cherenkov* dummyCher;
    Scintillator* dummyScint;
    Timepix* dummyTime;

    magField = NULL;
    localFieldManager = NULL;

    for(int i = 0; i < sConf->DetectorN; i++) {
        switch(sConf->Detectors[i].Kind) {
            case ECAL:
                dummyCal = new Calorimeter(sConf->Detectors[i].Name, nID[i]);
                sdMan->AddNewDetector(dummyCal);
                SetSensitiveDetector(sConf->Detectors[i].Name, dummyCal);
                ecals.push_back(dummyCal);
                break;
            case CHERENKOV:
                dummyCher = new Cherenkov(sConf->Detectors[i].Name, nID[i]);
                sdMan->AddNewDetector(dummyCher);
                SetSensitiveDetector(sConf->Detectors[i].Name, dummyCher);
                chers.push_back(dummyCher);
                break;
            case MAGNET:
                magField = new G4UniformMagField(G4ThreeVector(sConf->FieldX*tesla, sConf->FieldY*tesla, sConf->FieldZ*tesla));
                localFieldManager = new G4FieldManager();
                localFieldManager->SetDetectorField(magField);
	            localFieldManager->CreateChordFinder(magField);
	            logs[i]->SetFieldManager(localFieldManager, true);
                break;
            case SCINTILLATOR:
                dummyScint = new Scintillator(sConf->Detectors[i].Name, nID[i]);
                sdMan->AddNewDetector(dummyScint);
                SetSensitiveDetector(sConf->Detectors[i].Name, dummyScint);
                scints.push_back(dummyScint);
                break;
            case TIMEPIX:
                dummyTime = new Timepix(sConf->Detectors[i].Name, nID[i]);
                sdMan->AddNewDetector(dummyTime);
                SetSensitiveDetector(sConf->Detectors[i].Name, dummyTime);
                times.push_back(dummyTime);
                break;
        }
    }
}