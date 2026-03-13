#include "../include/calorimeter.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include <G4Allocator.hh>
#include <G4Types.hh>
#include "G4AnalysisManager.hh"

Calorimeter::Calorimeter(G4String name, G4int id): G4VSensitiveDetector(name)
{
	collectionName.insert("CaloriHits");
    nID = id;
}

Calorimeter::~Calorimeter()
{}

G4bool Calorimeter::ProcessHits(G4Step *step, G4TouchableHistory *thc)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(nID, 0,step->GetTrack()->GetTrackID());
    man->FillNtupleIColumn(nID, 1,step->GetTrack()->GetParentID());
    man->FillNtupleDColumn(nID, 2,step->GetPreStepPoint()->GetTotalEnergy());
    man->FillNtupleDColumn(nID, 3,step->GetTotalEnergyDeposit());
    man->FillNtupleSColumn(nID, 4,step->GetTrack()->GetDefinition()->GetParticleName());
    man->FillNtupleDColumn(nID, 5,step->GetPreStepPoint()->GetGlobalTime());
    man->AddNtupleRow(nID);
    step->GetTrack()->SetTrackStatus(fStopAndKill);
    return true;
}