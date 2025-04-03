cmake_minimum_required(VERSION 3.10)
project(Archimedes3D VERSION 0.1.0 LANGUAGES CXX)

# Use C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(src)

# Define source files explicitly instead of using GLOB
# Core sources
set(CORE_SOURCES
    src/core/Engine.cpp
    src/core/World.cpp
)

# Physics sources
set(PHYSICS_SOURCES
    src/physics/PhysicsObject.cpp
    src/physics/ChargedObject.cpp
    src/physics/CompressibleObject.cpp
    src/physics/ContainmentVessel.cpp
    src/physics/ElectromagneticField.cpp
    src/physics/PlasmaField.cpp
    src/physics/Pressure.cpp
    src/physics/Ionosphere.cpp
    # BuoyancyCalculator.h and ObjectFactory.h are header-only files, no .cpp needed
)

# Environment sources
set(ENVIRONMENT_SOURCES
    src/environment/Atmosphere.cpp
    src/environment/AtmosphereLayer.cpp
    src/environment/Electromagnetism.cpp
    src/environment/LayeredMedium.cpp
)

# Math sources
set(MATH_SOURCES
    src/math/Vector2.cpp
)

# Manager sources
set(MANAGER_SOURCES
    src/managers/ObjectManager.cpp
    src/managers/MediumManager.cpp
    src/managers/FieldManager.cpp
    src/managers/IonosphereManager.cpp
)

# Create library
add_library(archimedes STATIC
    ${CORE_SOURCES}
    ${PHYSICS_SOURCES}
    ${ENVIRONMENT_SOURCES}
    ${MATH_SOURCES}
    ${MANAGER_SOURCES}
)

# Set include directories for the library
target_include_directories(archimedes PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Examples
add_executable(BuoyancyDemo examples/BuoyancyDemo/BuoyancyDemo.cpp)
target_link_libraries(BuoyancyDemo PRIVATE archimedes)

add_executable(AtmosphereDemo examples/AtmosphereDemo/AtmosphereDemo.cpp)
target_link_libraries(AtmosphereDemo PRIVATE archimedes)

add_executable(PressureSystemDemo examples/PressureSystemDemo/PressureSystemDemo.cpp)
target_link_libraries(PressureSystemDemo PRIVATE archimedes)

add_executable(ElectromagneticDemo examples/ElectromagneticDemo/ElectromagneticDemo.cpp)
target_link_libraries(ElectromagneticDemo PRIVATE archimedes)

add_executable(BalloonTest examples/BalloonTest/BalloonTest.cpp)
target_link_libraries(BalloonTest PRIVATE archimedes)

# Installation
install(TARGETS archimedes
    EXPORT archimedes-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install header files
install(DIRECTORY src/
    DESTINATION include/archimedes
    FILES_MATCHING PATTERN "*.h"
)

# Export targets
install(EXPORT archimedes-targets
    FILE archimedes-targets.cmake
    NAMESPACE Archimedes::
    DESTINATION lib/cmake/archimedes
)

# Create and install package configuration file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/archimedes-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/archimedes-config.cmake
    INSTALL_DESTINATION lib/cmake/archimedes
)

# Install package configuration
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/archimedes-config.cmake
    DESTINATION lib/cmake/archimedes
)

# Enable testing
option(BUILD_TESTING "Build the testing tree" OFF)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
