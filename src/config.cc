#include "../include/config.hh"

std::map<std::string, int> DetectorAlias = {
    {"ecal", ECAL},
    {"cherenkov", CHERENKOV},
    {"magnet", MAGNET},
    {"scintillator", SCINTILLATOR},
    {"target", TARGET},
    {"timepix", TIMEPIX},
};

SystemConfig::SystemConfig(std::string fName) 
{
    std::ifstream fConfig(fName);
    std::string fLine;
    int detectorCount = 0;
    int id_counter[6] = {0,0,0,0,0,0};

    while(getline(fConfig, fLine)) {
        if(fLine == "@world") {
            getline(fConfig, fLine);
            DetectorN = stoi(fLine);
            getline(fConfig, fLine);
            WorldX = stod(fLine);
            getline(fConfig, fLine);
            WorldY = stod(fLine);
            getline(fConfig, fLine);
            WorldZ = stod(fLine);
            Detectors = new DetectorConfig[DetectorN];
        } else if(fLine == "@new") {
            getline(fConfig, fLine);
            Detectors[detectorCount].Kind   = DetectorAlias[fLine];
            Detectors[detectorCount].ID     = id_counter[Detectors[detectorCount].Kind]++;
            Detectors[detectorCount].Name   = G4String(fLine + std::to_string(Detectors[detectorCount].ID)); // this is cursed af
            getline(fConfig, fLine);
            Detectors[detectorCount].PosX = stod(fLine);
            getline(fConfig, fLine);
            Detectors[detectorCount].PosY = stod(fLine);
            getline(fConfig, fLine);
            Detectors[detectorCount].PosZ = stod(fLine);
            getline(fConfig, fLine);
            Detectors[detectorCount].SizeX = stod(fLine);
            getline(fConfig, fLine);
            Detectors[detectorCount].SizeY = stod(fLine);
            getline(fConfig, fLine);
            Detectors[detectorCount].SizeZ = stod(fLine);
            if(++detectorCount > DetectorN)
                break;
        } else if(fLine == "@material") {
            getline(fConfig, Material);
        } else if(fLine == "@field") {
            getline(fConfig, fLine);
            FieldX = stod(fLine);
            getline(fConfig, fLine);
            FieldY = stod(fLine);
            getline(fConfig, fLine);
            FieldZ = stod(fLine);            
        }
    }
}

SystemConfig::~SystemConfig() 
{
    delete[] Detectors;
}