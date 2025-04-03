#pragma once

#include "../src/core/Engine.h"
#include "../src/physics/PhysicsObject.h"
#include "../src/environment/Medium.h"
#include "../src/constants/SimulationConstants.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>

namespace Archimedes {
namespace Demo {

/**
 * Print a formatted header for demo output tables
 */
inline void printTableHeader(const std::string& header, int width = Constants::Simulation::OUTPUT_TABLE_WIDTH) {
    std::cout << "=== " << header << " ===" << std::endl;
    std::cout << std::string(width, '-') << std::endl;
}

/**
 * Print a separator line for tables
 */
inline void printTableSeparator(int width = Constants::Simulation::OUTPUT_TABLE_WIDTH) {
    std::cout << std::string(width, '-') << std::endl;
}

/**
 * Print formatted information about the current medium
 */
inline void printMediumInfo(const Medium& medium) {
    std::cout << "Medium properties:" << std::endl;
    std::cout << "  Density: " << medium.getDensity() << " kg/m³" << std::endl;
    std::cout << "  Viscosity: " << medium.getViscosity() << " Pa·s" << std::endl;
    std::cout << std::endl;
}

/**
 * Print object state in a standardized format
 */
inline void printObjectState(
    const std::string& name, 
    float density, 
    const std::shared_ptr<PhysicsObject>& object,
    int precision = Constants::Simulation::OUTPUT_PRECISION_BUOYANCY
) {
    std::cout << "  " << std::left << std::setw(Constants::Simulation::OBJECT_NAME_WIDTH) 
              << name + " (" + std::to_string(static_cast<int>(density + Constants::Simulation::DENSITY_ROUNDING_OFFSET)) + " kg/m³):";
    std::cout << "y=" << std::fixed << std::setprecision(precision) << object->getPosition().y;
    std::cout << ", vel=" << std::fixed << std::setprecision(precision) << object->getVelocity().y << std::endl;
}

/**
 * Run a simulation for a specified number of steps
 */
inline void runSimulation(
    Engine& engine, 
    float timeStep,
    int steps,
    const std::vector<std::shared_ptr<PhysicsObject>>& objects,
    const std::vector<std::string>& names,
    const std::vector<float>& densities,
    int timePrecision = Constants::Simulation::OUTPUT_PRECISION_TIME
) {
    for (int i = 0; i < steps; ++i) {
        engine.step(timeStep);
        
        std::cout << "Time: " << std::fixed << std::setprecision(timePrecision) << (i + 1) * timeStep << "s" << std::endl;
        
        for (size_t j = 0; j < objects.size(); ++j) {
            printObjectState(names[j], densities[j], objects[j]);
        }
        
        std::cout << std::endl;
    }
}

} // namespace Demo
} // namespace Archimedes