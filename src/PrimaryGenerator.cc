#include "../include/PrimaryGenerator.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include "G4ParticleTable.hh"

PrimaryGenerator::PrimaryGenerator(): G4VUserPrimaryGeneratorAction(), Gun(nullptr), Name("e-"),Energy(100 * CLHEP::MeV), Direction(0.0,0.0,1.0),Position(-10* CLHEP::cm,0,0)
{
    Gun = new G4ParticleGun(1);
    G4ParticleTable* table = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = table->FindParticle(Name);
    if(particle)
        Gun->SetParticleDefinition(particle);
}

PrimaryGenerator::~PrimaryGenerator()
{
    delete Gun;
}
void PrimaryGenerator::GeneratePrimaries(G4Event* event)
{
    Gun->GeneratePrimaryVertex(event);
}