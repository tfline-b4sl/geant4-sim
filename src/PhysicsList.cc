#include "../include/PhysicsList.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4ProcessManager.hh>
#include <G4VModularPhysicsList.hh>
#include <G4VPhysicsConstructor.hh>
#include <G4ios.hh>
#include <G4DecayPhysics.hh>
#include <G4EmStandardPhysics_option4.hh>
#include <G4OpticalPhysics.hh>
#include <memory>

PhysicsList::PhysicsList() :G4VModularPhysicsList(), Em(nullptr),Opt(nullptr),Dec(nullptr)
{
    G4cout << "Constructing Physics List" << G4endl;
    SetVerboseLevel(1);
    SetDefaultCutValue(0.1 * CLHEP::mm);
    Dec = new G4DecayPhysics();
    RegisterPhysics(Dec);
    Em = new G4EmStandardPhysics_option4();
    RegisterPhysics(Em);
    Opt = new G4OpticalPhysics();
    RegisterPhysics(Opt);
    G4cout << "Done" << G4endl;

}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructParticle()
{
    G4cout << "PartConstBegin" << G4endl;
    Dec->ConstructParticle();
    Opt->ConstructParticle();
    Em->ConstructParticle();
    G4cout << "PartConstEnd" << G4endl;
}

void PhysicsList::ConstructProcess()
{
    G4cout << "ProcConstBegin" << G4endl;
    AddTransportation();
    Dec->ConstructProcess();
    Opt->ConstructProcess();
    Em->ConstructProcess();
    G4cout << "ProcConstEnd" << G4endl;
}

void PhysicsList::SetCuts()
{
    SetCutsWithDefault();
}
