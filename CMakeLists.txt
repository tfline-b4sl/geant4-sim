cmake_minimum_required(VERSION 3.16)
project(TFLine)

# Find Geant4
find_package(Geant4 REQUIRED ui_all vis_all)

# This is crucial - sets up include paths
include(${Geant4_USE_FILE})


# Your source files
file(GLOB SOURCES "src/*.cc")

# Executable
add_executable(TFLine ${SOURCES})

# Include directories 
target_include_directories(TFLine PRIVATE
include
    ${Geant4_INCLUDE_DIRS}      # Geant4 headers
)



# Link libraries
target_link_libraries(TFLine ${Geant4_LIBRARIES})

# C++ standard
set_target_properties(TFLine PROPERTIES CXX_STANDARD 17)
