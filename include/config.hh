#ifndef CONFIG_h
#define CONFIG_h

#include<fstream>
#include<string>
#include<cstring>
#include<map>

#include "G4String.hh"

enum DetectorKind {
    ECAL,
    CHERENKOV,
    MAGNET,
    SCINTILLATOR,
    TARGET,
    TIMEPIX,
};

typedef struct {
    double      PosX;
    double      PosY;
    double      PosZ;
    double      SizeX;
    double      SizeY;
    double      SizeZ;
    G4String    Name;
    int         ID;
    char        Kind;
} DetectorConfig;

class SystemConfig {
public:
    SystemConfig(std::string fName);
    virtual ~SystemConfig();
    double WorldX;
    double WorldY;
    double WorldZ;
    double FieldX;
    double FieldY;
    double FieldZ;
    DetectorConfig *Detectors;
    std::string Material;
    int DetectorN;
};

#endif