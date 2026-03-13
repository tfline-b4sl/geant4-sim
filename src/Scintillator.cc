#include <G4AnalysisManager.hh>
#include <G4StepStatus.hh>
#include <G4String.hh>
#include <G4TrackStatus.hh>
#include <G4VSensitiveDetector.hh>
#include "../include/Scintillator.hh"



Scintillator::Scintillator(G4String name, G4int id) : G4VSensitiveDetector(name)
{
    collectionName.insert("ScintHit");
    nID = id;
}

Scintillator::~Scintillator()
{}

G4bool Scintillator::ProcessHits(G4Step *step, G4TouchableHistory *thc)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    G4Track* track = step->GetTrack();
    man->FillNtupleIColumn(nID, 0,track->GetTrackID());
    man->FillNtupleIColumn(nID, 1,step->GetTrack()->GetParentID());
    man->FillNtupleIColumn(nID, 2,track->GetTrackStatus());
    man->FillNtupleDColumn(nID, 3,step->GetPreStepPoint()->GetGlobalTime());
    man->AddNtupleRow(nID);

    return true;
}
