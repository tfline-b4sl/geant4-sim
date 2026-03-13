#include "../include/cherenkov.hh"
#include "G4OpticalPhoton.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include <G4AnalysisManager.hh>

Cherenkov::Cherenkov(G4String name, G4int id) : G4VSensitiveDetector(name) 
{
    nID = id;
}

Cherenkov::~Cherenkov()
{}

G4bool Cherenkov::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    G4Track* track = step->GetTrack();
    man->FillNtupleIColumn(nID, 0,track->GetTrackID());
    man->FillNtupleIColumn(nID, 1,step->GetTrack()->GetParentID());
    man->FillNtupleDColumn(nID, 2,step->GetPreStepPoint()->GetTotalEnergy());
    man->FillNtupleDColumn(nID, 3,step->GetTotalEnergyDeposit());
    man->FillNtupleSColumn(nID, 4,track->GetDefinition()->GetParticleName());
    man->FillNtupleDColumn(nID, 5,step->GetPreStepPoint()->GetGlobalTime());
    man->AddNtupleRow(nID);
    return true;
}
