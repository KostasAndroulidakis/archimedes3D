#include "../../src/core/Engine.h"
#include "../../src/physics/PhysicsObject.h"
#include "../../src/environment/Medium.h"
#include "../../src/utils/Constants.h"
#include <iostream>
#include <memory>
#include <string>
#include <iomanip>

using namespace Archimedes;

// Calculate densities from the mass and volume constants
namespace TestObjects {
    constexpr float STONE_DENSITY = Constants::Materials::TestObjects::STONE_MASS / Constants::Materials::TestObjects::STONE_VOLUME; // kg/m³
    constexpr float WOOD_DENSITY = Constants::Materials::TestObjects::WOOD_MASS / Constants::Materials::TestObjects::WOOD_VOLUME; // kg/m³
    constexpr float BALLOON_DENSITY = Constants::Materials::TestObjects::BALLOON_MASS / Constants::Materials::TestObjects::BALLOON_VOLUME; // kg/m³
}

// Simulation parameters
constexpr float TIME_STEP = Constants::Simulation::DEMO_TIME_STEP;  // seconds
constexpr int SIMULATION_STEPS = Constants::Simulation::DEFAULT_SIMULATION_STEPS;  // number of steps

// Utility function for formatted output
void printObjectState(const std::string& name, float density, const std::shared_ptr<PhysicsObject>& object) {
    std::cout << "  " << std::left << std::setw(Constants::Simulation::OBJECT_NAME_WIDTH) << name + " (" + std::to_string(static_cast<int>(density + Constants::Simulation::DENSITY_ROUNDING_OFFSET)) + " kg/m³):";
    std::cout << "y=" << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION_BUOYANCY) << object->getPosition().y;
    std::cout << ", vel=" << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION_BUOYANCY) << object->getVelocity().y << std::endl;
}

// Simple console-based demo of buoyancy physics
int main() {
    // Initialize engine
    Engine engine;
    engine.initialize();
    
    // Create different media using constants
    Medium air(Constants::Environment::Standard::AIR_DENSITY);
    Medium water(Constants::Environment::Standard::WATER_DENSITY);
    
    // Create objects with different densities using constants
    auto stone = std::make_shared<PhysicsObject>(
        Constants::Materials::TestObjects::STONE_MASS, 
        Constants::Materials::TestObjects::STONE_VOLUME, 
        Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT1, Constants::Simulation::INITIAL_Y_POSITION));
        
    auto wood = std::make_shared<PhysicsObject>(
        Constants::Materials::TestObjects::WOOD_MASS, 
        Constants::Materials::TestObjects::WOOD_VOLUME, 
        Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT2, Constants::Simulation::INITIAL_Y_POSITION));
        
    auto balloon = std::make_shared<PhysicsObject>(
        Constants::Materials::TestObjects::BALLOON_MASS, 
        Constants::Materials::TestObjects::BALLOON_VOLUME, 
        Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT3, Constants::Simulation::INITIAL_Y_POSITION));
    
    // Add objects to world
    engine.getWorld()->addObject(stone);
    engine.getWorld()->addObject(wood);
    engine.getWorld()->addObject(balloon);
    
    // Demo in air
    std::cout << "Simulating in air (density: " << Constants::Environment::Standard::AIR_DENSITY << " kg/m³):" << std::endl;
    engine.getWorld()->setMedium(air);
    
    for (int i = 0; i < SIMULATION_STEPS; ++i) {
        engine.step(TIME_STEP);
        
        std::cout << "Time: " << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION_TIME) << (i + 1) * TIME_STEP << "s" << std::endl;
        printObjectState("Stone", TestObjects::STONE_DENSITY, stone);
        printObjectState("Wood", TestObjects::WOOD_DENSITY, wood);
        printObjectState("Balloon", TestObjects::BALLOON_DENSITY, balloon);
        std::cout << std::endl;
    }
    
    // Reset positions
    stone = std::make_shared<PhysicsObject>(
        Constants::Materials::TestObjects::STONE_MASS, 
        Constants::Materials::TestObjects::STONE_VOLUME, 
        Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT1, Constants::Simulation::INITIAL_Y_POSITION));
        
    wood = std::make_shared<PhysicsObject>(
        Constants::Materials::TestObjects::WOOD_MASS, 
        Constants::Materials::TestObjects::WOOD_VOLUME, 
        Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT2, Constants::Simulation::INITIAL_Y_POSITION));
        
    balloon = std::make_shared<PhysicsObject>(
        Constants::Materials::TestObjects::BALLOON_MASS, 
        Constants::Materials::TestObjects::BALLOON_VOLUME, 
        Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT3, Constants::Simulation::INITIAL_Y_POSITION));
    
    // Clear world and add reset objects
    engine.initialize();
    engine.getWorld()->addObject(stone);
    engine.getWorld()->addObject(wood);
    engine.getWorld()->addObject(balloon);
    
    // Demo in water
    std::cout << "Simulating in water (density: " << Constants::Environment::Standard::WATER_DENSITY << " kg/m³):" << std::endl;
    engine.getWorld()->setMedium(water);
    
    for (int i = 0; i < SIMULATION_STEPS; ++i) {
        engine.step(TIME_STEP);
        
        std::cout << "Time: " << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION_TIME) << (i + 1) * TIME_STEP << "s" << std::endl;
        printObjectState("Stone", TestObjects::STONE_DENSITY, stone);
        printObjectState("Wood", TestObjects::WOOD_DENSITY, wood);
        printObjectState("Balloon", TestObjects::BALLOON_DENSITY, balloon);
        std::cout << std::endl;
    }
    
    return 0;
}
