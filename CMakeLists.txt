cmake_minimum_required(VERSION 3.16...3.17)
project(diamondDetector)

#build with ui and vis drivers on
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
	find_package(Geant4 REQUIRED ui_all vis_all)
else()
	find_package(Geant4 REQUIRED)
endif()

#include directories and comile definitions from Geant4
include(${Geant4_USE_FILE})

#locate sources and headers for the project
include_directories(${PROJECT_SOURCE_DIR}/include
			${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#copy all macros to build directory
file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

#add the executable and link it to the Geant4 libraries
add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

#intall the executable in the bin directory under CMAKE_INSTALL_PREFIX
install(TARGETS sim DESTINATION bin)
