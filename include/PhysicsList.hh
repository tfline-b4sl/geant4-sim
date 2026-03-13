#ifndef PHYSICSLIST_h
#define PHYSICSLIST_h

#include "G4VModularPhysicsList.hh"
#include <G4VPhysicsConstructor.hh>
class PhysicsList : public G4VModularPhysicsList
{
public:
    PhysicsList();
    virtual ~PhysicsList();

    virtual void ConstructParticle();
    virtual void ConstructProcess();
    virtual void SetCuts();
    private:
    G4VPhysicsConstructor* Em;
    G4VPhysicsConstructor* Opt;
    G4VPhysicsConstructor* Dec;
};

#endif
