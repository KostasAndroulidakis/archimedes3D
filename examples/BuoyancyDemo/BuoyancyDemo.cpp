#include "../../src/core/Engine.h"
#include "../../src/physics/PhysicsObject.h"
#include "../../src/environment/Medium.h"
#include "../../src/utils/Constants.h"
#include <iostream>
#include <memory>
#include <string>
#include <iomanip>

using namespace Archimedes;

// Test object properties
namespace TestObjects {
    // Stone properties
    constexpr float STONE_MASS = 5.0f;      // kg
    constexpr float STONE_VOLUME = 0.001f;  // m³
    constexpr float STONE_DENSITY = STONE_MASS / STONE_VOLUME; // kg/m³
    
    // Wood properties
    constexpr float WOOD_MASS = 0.5f;      // kg
    constexpr float WOOD_VOLUME = 0.001f;  // m³
    constexpr float WOOD_DENSITY = WOOD_MASS / WOOD_VOLUME; // kg/m³
    
    // Balloon properties
    constexpr float BALLOON_MASS = 0.001f;     // kg
    constexpr float BALLOON_VOLUME = 0.001f;   // m³
    constexpr float BALLOON_DENSITY = BALLOON_MASS / BALLOON_VOLUME; // kg/m³
}

// Simulation parameters
constexpr float TIME_STEP = 0.1f;        // seconds
constexpr int SIMULATION_STEPS = 5;      // number of steps

// Utility function for formatted output
void printObjectState(const std::string& name, float density, const std::shared_ptr<PhysicsObject>& object) {
    std::cout << "  " << std::left << std::setw(15) << name + " (" + std::to_string(static_cast<int>(density + 0.5f)) + " kg/m³):";
    std::cout << "y=" << std::fixed << std::setprecision(6) << object->getPosition().y;
    std::cout << ", vel=" << std::fixed << std::setprecision(6) << object->getVelocity().y << std::endl;
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
        TestObjects::STONE_MASS, 
        TestObjects::STONE_VOLUME, 
        Vector2(0.0f, 0.0f));
        
    auto wood = std::make_shared<PhysicsObject>(
        TestObjects::WOOD_MASS, 
        TestObjects::WOOD_VOLUME, 
        Vector2(1.0f, 0.0f));
        
    auto balloon = std::make_shared<PhysicsObject>(
        TestObjects::BALLOON_MASS, 
        TestObjects::BALLOON_VOLUME, 
        Vector2(2.0f, 0.0f));
    
    // Add objects to world
    engine.getWorld()->addObject(stone);
    engine.getWorld()->addObject(wood);
    engine.getWorld()->addObject(balloon);
    
    // Demo in air
    std::cout << "Simulating in air (density: " << Constants::Environment::Standard::AIR_DENSITY << " kg/m³):" << std::endl;
    engine.getWorld()->setMedium(air);
    
    for (int i = 0; i < SIMULATION_STEPS; ++i) {
        engine.step(TIME_STEP);
        
        std::cout << "Time: " << std::fixed << std::setprecision(1) << (i + 1) * TIME_STEP << "s" << std::endl;
        printObjectState("Stone", TestObjects::STONE_DENSITY, stone);
        printObjectState("Wood", TestObjects::WOOD_DENSITY, wood);
        printObjectState("Balloon", TestObjects::BALLOON_DENSITY, balloon);
        std::cout << std::endl;
    }
    
    // Reset positions
    stone = std::make_shared<PhysicsObject>(
        TestObjects::STONE_MASS, 
        TestObjects::STONE_VOLUME, 
        Vector2(0.0f, 0.0f));
        
    wood = std::make_shared<PhysicsObject>(
        TestObjects::WOOD_MASS, 
        TestObjects::WOOD_VOLUME, 
        Vector2(1.0f, 0.0f));
        
    balloon = std::make_shared<PhysicsObject>(
        TestObjects::BALLOON_MASS, 
        TestObjects::BALLOON_VOLUME, 
        Vector2(2.0f, 0.0f));
    
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
        
        std::cout << "Time: " << std::fixed << std::setprecision(1) << (i + 1) * TIME_STEP << "s" << std::endl;
        printObjectState("Stone", TestObjects::STONE_DENSITY, stone);
        printObjectState("Wood", TestObjects::WOOD_DENSITY, wood);
        printObjectState("Balloon", TestObjects::BALLOON_DENSITY, balloon);
        std::cout << std::endl;
    }
    
    return 0;
}
