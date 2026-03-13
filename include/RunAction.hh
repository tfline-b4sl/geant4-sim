#ifndef RUNACTION_h
#include <G4UserRunAction.hh>
#include "../include/config.hh"
class RunAction : public G4UserRunAction
{
    public:
    RunAction(G4int **ids, std::string fName);
    virtual ~RunAction();
    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);
    private:
    G4int *nIDs;
    SystemConfig *sConf;
};

#endif