#include "../../src/core/Engine.h"
#include "../../src/physics/PhysicsObject.h"
#include "../../src/physics/ObjectFactory.h"
#include "../../src/environment/Medium.h"
#include "../../src/constants/MaterialConstants.h"
#include "../../src/constants/SimulationConstants.h"
#include "../../src/constants/EnvironmentConstants.h"
#include "../../src/managers/MediumManager.h"
#include "../DemoUtils.h"
#include <iostream>
#include <memory>
#include <string>
// <iomanip> now included through DemoUtils.h
#include <vector>

using namespace Archimedes;
using namespace Archimedes::Demo;

// Calculate densities from the mass and volume constants
namespace TestObjects {
    constexpr float STONE_DENSITY = Constants::Materials::TestObjects::STONE_MASS / Constants::Materials::TestObjects::STONE_VOLUME; // kg/m³
    constexpr float WOOD_DENSITY = Constants::Materials::TestObjects::WOOD_MASS / Constants::Materials::TestObjects::WOOD_VOLUME; // kg/m³
    constexpr float BALLOON_DENSITY = Constants::Materials::TestObjects::BALLOON_MASS / Constants::Materials::TestObjects::BALLOON_VOLUME; // kg/m³
}

// Simulation parameters
constexpr float TIME_STEP = Constants::Simulation::DEMO_TIME_STEP;  // seconds
constexpr int SIMULATION_STEPS = Constants::Simulation::DEFAULT_SIMULATION_STEPS;  // number of steps

// Simple console-based demo of buoyancy physics
int main() {
    // Initialize engine
    Engine engine;
    engine.initialize();
    
    // Create different media using constants
    Medium air(Constants::Environment::Standard::AIR_DENSITY);
    Medium water(Constants::Environment::Standard::WATER_DENSITY);
    
    // Create objects with different densities using factory
    auto objects = ObjectFactory::createStandardTestSet(engine.getWorld());    
    auto& stone = objects[0];
    auto& wood = objects[1];
    auto& balloon = objects[2];
    
    // Demo in air
    printTableHeader("Simulation in Air");
    std::cout << "Medium density: " << Constants::Environment::Standard::AIR_DENSITY << " kg/m³" << std::endl << std::endl;
    engine.getWorld()->getMediumManager()->setMedium(air);
    
    // Define object names and densities vectors for the demo utility
    std::vector<std::string> names = {"Stone", "Wood", "Balloon"};
    std::vector<float> densities = {TestObjects::STONE_DENSITY, TestObjects::WOOD_DENSITY, TestObjects::BALLOON_DENSITY};
    
    // Run simulation with the demo utility
    runSimulation(engine, TIME_STEP, SIMULATION_STEPS, objects, names, densities);
    
    // Reset positions and recreate objects
    engine.initialize();
    objects = ObjectFactory::createStandardTestSet(engine.getWorld());
    
    // Get references to the newly created objects
    stone = objects[0];
    wood = objects[1];
    balloon = objects[2];
    
    // Demo in water
    printTableHeader("Simulation in Water");
    std::cout << "Medium density: " << Constants::Environment::Standard::WATER_DENSITY << " kg/m³" << std::endl << std::endl;
    engine.getWorld()->getMediumManager()->setMedium(water);
    
    // Run simulation with same parameters
    runSimulation(engine, TIME_STEP, SIMULATION_STEPS, objects, names, densities);
    
    return 0;
}
