#include "../include/timepix.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include <G4Allocator.hh>
#include <G4Types.hh>
#include "G4AnalysisManager.hh"

Timepix::Timepix(G4String name, G4int id): G4VSensitiveDetector(name)
{
	collectionName.insert("CaloriHits");
    nID = id;
}

Timepix::~Timepix()
{}

G4bool Timepix::ProcessHits(G4Step *step, G4TouchableHistory *thc)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    auto pos = step->GetPostStepPoint()->GetPosition();
    man->FillNtupleIColumn(nID, 0,step->GetTrack()->GetTrackID());
    man->FillNtupleIColumn(nID, 1,step->GetTrack()->GetParentID());
    man->FillNtupleDColumn(nID, 2,step->GetPreStepPoint()->GetTotalEnergy());
    man->FillNtupleDColumn(nID, 3,step->GetTotalEnergyDeposit());
    man->FillNtupleDColumn(nID, 4, pos.x());
    man->FillNtupleDColumn(nID, 5, pos.y());
    man->FillNtupleDColumn(nID, 6, pos.z());
    man->FillNtupleDColumn(nID, 7,step->GetPreStepPoint()->GetGlobalTime());
    return true;
}