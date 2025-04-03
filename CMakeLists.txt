cmake_minimum_required(VERSION 3.10)
project(Archimedes3D)

set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(src)

# Source files
file(GLOB_RECURSE CORE_SOURCES "src/core/*.cpp")
file(GLOB_RECURSE PHYSICS_SOURCES "src/physics/*.cpp")
file(GLOB_RECURSE ENVIRONMENT_SOURCES "src/environment/*.cpp")
file(GLOB_RECURSE MATH_SOURCES "src/math/*.cpp")
file(GLOB_RECURSE UTILS_SOURCES "src/utils/*.cpp")

# Create library
add_library(archimedes STATIC
    ${CORE_SOURCES}
    ${PHYSICS_SOURCES}
    ${ENVIRONMENT_SOURCES}
    ${MATH_SOURCES}
    ${UTILS_SOURCES}
)

# BuoyancyDemo example
add_executable(BuoyancyDemo examples/BuoyancyDemo/BuoyancyDemo.cpp)
target_link_libraries(BuoyancyDemo archimedes)

# AtmosphereDemo example
add_executable(AtmosphereDemo examples/AtmosphereDemo/AtmosphereDemo.cpp)
target_link_libraries(AtmosphereDemo archimedes)

# PressureSystemDemo example
add_executable(PressureSystemDemo examples/PressureSystemDemo/PressureSystemDemo.cpp)
target_link_libraries(PressureSystemDemo archimedes)

# ElectromagneticDemo example
add_executable(ElectromagneticDemo examples/ElectromagneticDemo/ElectromagneticDemo.cpp)
target_link_libraries(ElectromagneticDemo archimedes)

# BalloonTest example
add_executable(BalloonTest examples/BalloonTest/BalloonTest.cpp)
target_link_libraries(BalloonTest archimedes)
