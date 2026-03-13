#include <iostream>
#include <fstream>
#include <string>

#include <CLHEP/Random/RandomEngine.h>
#include <CLHEP/Random/RanecuEngine.h>
#include <Randomize.hh>
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "../include/DetectorConstruction.hh"
#include "../include/PhysicsList.hh"
#include "../include/PrimaryGenerator.hh"
#include "../include/RunAction.hh"

int main(int argc, char *argv[]) {
  if(argc != 3) {
    G4cout << "Requires exactly 2 arguments" << G4endl;
    return -1;
  }

  G4int *nIDs = NULL;
  G4Random::setTheEngine(new CLHEP::RanecuEngine());
  G4RunManager* manager = new G4RunManager();

  manager->SetUserInitialization(new PhysicsList());
  
  manager->SetUserAction(new RunAction(&nIDs, argv[1]));
  manager->SetUserInitialization(new DetectorConstruction(nIDs, argv[1]));

  manager->SetUserAction(new PrimaryGenerator());
  manager->Initialize();

  std::string macLine;
  std::ifstream macFile(argv[2]);
  auto *UIptr = G4UImanager::GetUIpointer();
  while(std::getline(macFile, macLine))
    UIptr->ApplyCommand(macLine);
  macFile.close();

  delete manager;
  return 0;
}
