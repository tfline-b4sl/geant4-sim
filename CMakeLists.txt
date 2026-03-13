cmake_minimum_required(VERSION 3.16)
project(geez)

# Find Geant4
find_package(Geant4 REQUIRED ui_all vis_all)

# This is crucial - sets up include paths
include(${Geant4_USE_FILE})


# Your source files
file(GLOB SOURCES "src/*.cc")

# Executable
add_executable(geez ${SOURCES})

# Include directories 
target_include_directories(geez PRIVATE
include
    ${Geant4_INCLUDE_DIRS}      # Geant4 headers
    include  # Your headers
    /home/cheri/dark/include/
        /home/cheri/dark/include/G4DarkBreM

)



# Link libraries
target_link_libraries(geez ${Geant4_LIBRARIES})

# C++ standard
set_target_properties(geez PROPERTIES CXX_STANDARD 17)
