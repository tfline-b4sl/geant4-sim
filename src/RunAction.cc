#include <ctime>
#include <string>

#include "../include/RunAction.hh"
#include "G4Run.hh"
#include <G4AnalysisManager.hh>
#include <G4UserRunAction.hh>
#include <G4ios.hh>

RunAction::RunAction(G4int **ids, std::string fName):G4UserRunAction()
{
    sConf = new SystemConfig(fName);
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    nIDs = new int[sConf->DetectorN];
   	man->OpenFile("./run/result_" + std::to_string(std::time(0)) + ".root");
    man->SetVerboseLevel(1);
    for(int i = 0; i < sConf->DetectorN; i++) {
        if(sConf->Detectors[i].Kind == TARGET || sConf->Detectors[i].Kind == MAGNET) {
            nIDs[i] = -1;
            continue;     
        }
        nIDs[i] = man->CreateNtuple(sConf->Detectors[i].Name,"");
        switch(sConf->Detectors[i].Kind) {
            case ECAL:
                man->CreateNtupleIColumn("ID");
                man->CreateNtupleIColumn("ParentID");
                man->CreateNtupleDColumn("Energy");
                man->CreateNtupleDColumn("EnergyDeposit");
                man->CreateNtupleSColumn("Flavor");
                man->CreateNtupleDColumn("Time");
                break;
            case CHERENKOV:
                man->CreateNtupleIColumn("ID");
                man->CreateNtupleIColumn("ParentID");
                man->CreateNtupleDColumn("Energy");
                man->CreateNtupleDColumn("EnergyDeposit");
                man->CreateNtupleSColumn("Flavor");
                man->CreateNtupleDColumn("Time");
                break;
            case SCINTILLATOR:
                man->CreateNtupleIColumn("ID");
                man->CreateNtupleIColumn("ParentID");
                man->CreateNtupleIColumn("Alive");
                man->CreateNtupleDColumn("Time");
                break;
            case TIMEPIX:
                man->CreateNtupleIColumn("ID");
                man->CreateNtupleIColumn("ParentID");
                man->CreateNtupleDColumn("Energy");
                man->CreateNtupleDColumn("EnergyDeposit");
                man->CreateNtupleDColumn("X");
                man->CreateNtupleDColumn("Y");
                man->CreateNtupleDColumn("Z");
                man->CreateNtupleDColumn("Time");
                break;
        }
        man->FinishNtuple();
    }
    *ids = nIDs;
}

RunAction::~RunAction()
{
    delete sConf;
    delete[] nIDs;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
        G4AnalysisManager* man = G4AnalysisManager::Instance();
        G4cout << "Run : " << run->GetNumberOfEventToBeProcessed() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run*) 
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}
