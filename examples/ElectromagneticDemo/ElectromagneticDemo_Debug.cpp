#include "../../src/core/Engine.h"
#include "../../src/physics/ChargedObject.h"
#include "../../src/managers/ObjectManager.h"
#include <iostream>
#include <fstream>
#include <memory>

using namespace Archimedes;

// Simple debug test to write to a file
int main() {
    std::cerr << "Starting debug test..." << std::endl;
    
    try {
        std::ofstream outFile("debug_output/electromagnetic_debug.txt");
        if (!outFile.is_open()) {
            std::cerr << "ERROR: Could not open output file" << std::endl;
            return 1;
        }
        
        outFile << "ElectromagneticDemo Debug Test" << std::endl;
        outFile << "=============================" << std::endl;
        std::cerr << "Opened output file" << std::endl;
        
        // Initialize engine
        Engine engine;
        bool initResult = engine.initialize();
        outFile << "Engine initialized: " << (initResult ? "Success" : "Failed") << std::endl;
        std::cerr << "Engine initialized: " << (initResult ? "Success" : "Failed") << std::endl;
        
        // Get world
        auto world = engine.getWorld();
        outFile << "World pointer valid: " << (world ? "Yes" : "No") << std::endl;
        std::cerr << "World pointer valid: " << (world ? "Yes" : "No") << std::endl;
        
        // Create a charged object
        auto object = std::make_shared<ChargedObject>(1.0f, 0.1f, 1.0f, Vector2(0.0f, 0.0f));
        outFile << "Created charged object" << std::endl;
        std::cerr << "Created charged object" << std::endl;
        
        // Try to add it to the world
        if (world && world->getObjectManager()) {
            world->getObjectManager()->addObject(object);
            outFile << "Added object to world" << std::endl;
            std::cerr << "Added object to world" << std::endl;
        } else {
            outFile << "Failed to add object to world - getObjectManager() returned null" << std::endl;
            std::cerr << "Failed to add object to world - getObjectManager() returned null" << std::endl;
        }
        
        // Try to run some simulation steps
        for (int i = 0; i < 5; i++) {
            engine.step(0.1f);
            outFile << "Simulation step " << i << ": Position = (" 
                    << object->getPosition().x << ", " << object->getPosition().y << ")" << std::endl;
            std::cerr << "Simulation step " << i << ": Position = (" 
                    << object->getPosition().x << ", " << object->getPosition().y << ")" << std::endl;
        }
        
        outFile << "Test complete" << std::endl;
        outFile.close();
        
        std::cout << "Debug test completed - check debug_output/electromagnetic_debug.txt for results" << std::endl;
        std::cerr << "Test completed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "UNKNOWN EXCEPTION occurred" << std::endl;
        return 1;
    }
    
    return 0;
}
