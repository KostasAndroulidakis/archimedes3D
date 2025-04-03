#include "../../src/core/Engine.h"
#include "../../src/physics/ChargedObject.h"
#include "../../src/physics/ElectromagneticField.h"
// PlasmaField.h is included through Electromagnetism.h
// #include "../../src/physics/PlasmaField.h"
#include "../../src/environment/Electromagnetism.h"
// Use LayeredMedium.h which includes AtmosphereLayer.h
#include "../../src/environment/Atmosphere.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <cmath>

using namespace Archimedes;

// Field visualization via ASCII art
void visualizeField(const FieldManager& fieldManager, FieldType fieldType, 
                   float xMin, float xMax, float yMin, float yMax, int width, int height) {
    std::cout << "=== " << (fieldType == FieldType::Electric ? "Electric" : 
                          fieldType == FieldType::Magnetic ? "Magnetic" : "Plasma")
              << " Field Visualization ===" << std::endl;
    
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));
    
    // Sample field points and find max magnitude
    std::vector<std::vector<Vector2>> fieldVectors(height, std::vector<Vector2>(width));
    float maxMagnitude = 0.000001f; // Prevent division by zero
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float worldX = xMin + (xMax - xMin) * x / (width - 1);
            float worldY = yMin + (yMax - yMin) * (height - 1 - y) / (height - 1);
            
            Vector2 fieldVector = fieldManager.getNetFieldVector(Vector2(worldX, worldY), fieldType);
            fieldVectors[y][x] = fieldVector;
            
            float magnitude = fieldVector.magnitude();
            if (magnitude > maxMagnitude) {
                maxMagnitude = magnitude;
            }
        }
    }
    
    // Use a logarithmic scale for better visualization
    maxMagnitude = std::log(maxMagnitude + 1.0f);
    
    // Normalize and determine characters
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vector2 fieldVector = fieldVectors[y][x];
            float magnitude = fieldVector.magnitude();
            
            // Convert to log scale
            float logMagnitude = std::log(magnitude + 1.0f);
            float normalizedMagnitude = logMagnitude / maxMagnitude;
            
            if (normalizedMagnitude < 0.1f) {
                grid[y][x] = ' '; // Very weak/no field
                continue;
            } else if (normalizedMagnitude < 0.3f) {
                grid[y][x] = '.'; // Weak field
                continue;
            }
            
            // Normalize for direction
            if (magnitude > 0.0001f) {
                fieldVector = fieldVector * (1.0f / magnitude);
            } else {
                grid[y][x] = '.';
                continue;
            }
            
            // Determine character based on direction
            float angle = std::atan2(fieldVector.y, fieldVector.x);
            
            // Convert angle to character
            if (angle >= -0.392699f && angle < 0.392699f) {
                grid[y][x] = '>'; // Right
            } else if (angle >= 0.392699f && angle < 1.1781f) {
                grid[y][x] = '/'; // Up-right
            } else if (angle >= 1.1781f && angle < 1.9635f) {
                grid[y][x] = '^'; // Up
            } else if (angle >= 1.9635f && angle < 2.7489f) {
                grid[y][x] = '\\'; // Up-left
            } else if ((angle >= 2.7489f && angle <= 3.14159f) || (angle >= -3.14159f && angle < -2.7489f)) {
                grid[y][x] = '<'; // Left
            } else if (angle >= -2.7489f && angle < -1.9635f) {
                grid[y][x] = '/'; // Down-left
            } else if (angle >= -1.9635f && angle < -1.1781f) {
                grid[y][x] = 'v'; // Down
            } else {
                grid[y][x] = '\\'; // Down-right
            }
            
            // Scale intensity by using different characters
            if (normalizedMagnitude > 0.7f) {
                if (grid[y][x] == '>')  grid[y][x] = '>'; // Using simpler char
                if (grid[y][x] == '<')  grid[y][x] = '<'; // Using simpler char
                if (grid[y][x] == '^')  grid[y][x] = '^'; // Using simpler char
                if (grid[y][x] == 'v')  grid[y][x] = 'v'; // Using simpler char
                if (grid[y][x] == '/')  grid[y][x] = '/'; // Using simpler char
                if (grid[y][x] == '\\') grid[y][x] = '\\'; // Using simpler char
            }
        }
    }
    
    // Print grid
    for (const auto& row : grid) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Demo 1: Charged objects in electromagnetic field
void runChargedObjectsDemo() {
    std::cout << "\n=== Charged Objects Demo ===\n" << std::endl;
    
    Engine engine;
    engine.initialize();
    
    // Create electromagnetic environment
    auto fieldManager = std::make_shared<FieldManager>();
    
    // Add a point electric field for more visible field variability
    auto electricField = std::make_shared<PointSourceField>(
        FieldType::Electric, 
        5000.0f, 
        Vector2(0.0f, 50.0f)
    );
    fieldManager->addField(electricField);
    
    // The World now requires a unique_ptr instead of shared_ptr, extract it
    FieldManager* fieldManagerPtr = fieldManager.get();
    engine.getWorld()->getFieldManager()->copyFrom(*fieldManagerPtr);
    
    // Create charged objects with opposing charges - starting from same X position with velocity
    auto positiveCharge = std::make_shared<ChargedObject>(0.05f, 0.01f, 5.0f, Vector2(-40.0f, 50.0f));
    auto negativeCharge = std::make_shared<ChargedObject>(0.05f, 0.01f, -5.0f, Vector2(40.0f, 50.0f));
    auto neutralObject = std::make_shared<ChargedObject>(0.1f, 0.01f, 0.0f, Vector2(0.0f, 20.0f));
    
    // Set initial velocities toward the field center
    positiveCharge->setVelocity(Vector2(10.0f, 0.0f));
    negativeCharge->setVelocity(Vector2(-10.0f, 0.0f));
    
    // Set magnetic properties
    positiveCharge->setMagneticSusceptibility(0.8f);
    negativeCharge->setMagneticSusceptibility(0.8f);
    
    // Add objects to world
    engine.getWorld()->getObjectManager()->addObject(positiveCharge);
    engine.getWorld()->getObjectManager()->addObject(negativeCharge);
    engine.getWorld()->getObjectManager()->addObject(neutralObject);
    
    // Visualize initial field
    visualizeField(*fieldManager, FieldType::Electric, -50.0f, 50.0f, -20.0f, 80.0f, 40, 25);
    
    // Output header
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(10) << "Time (s)"
              << std::setw(20) << "Positive Charge Pos"
              << std::setw(20) << "Negative Charge Pos"
              << std::setw(20) << "Neutral Object Pos"
              << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    // Run simulation for several seconds
    float timeStep = 0.1f;
    float maxTime = 2.0f;
    
    for (float time = 0; time <= maxTime; time += timeStep) {
        engine.step(timeStep);
        
        // Output positions
        std::cout << std::setw(10) << time
                  << std::setw(20) << ("(" + std::to_string(positiveCharge->getPosition().x) + ", " + 
                                       std::to_string(positiveCharge->getPosition().y) + ")")
                  << std::setw(20) << ("(" + std::to_string(negativeCharge->getPosition().x) + ", " + 
                                       std::to_string(negativeCharge->getPosition().y) + ")")
                  << std::setw(20) << ("(" + std::to_string(neutralObject->getPosition().x) + ", " + 
                                       std::to_string(neutralObject->getPosition().y) + ")")
                  << std::endl;
    }
}

// Demo 2: Lightning and plasma effects
void runPlasmaDemo() {
    std::cout << "\n=== Plasma and Lightning Demo ===\n" << std::endl;
    
    Engine engine;
    engine.initialize();
    
    // Create atmospheric model with electromagnetic fields
    auto atmosphere = Atmosphere::createStandardModel();
    engine.getWorld()->getMediumManager()->setLayeredMedium(atmosphere);
    
    auto fieldManager = Electromagnetism::createStandardModel();
    FieldManager* fieldManagerPtr = fieldManager.get();
    engine.getWorld()->getFieldManager()->copyFrom(*fieldManagerPtr);
    
    auto ionosphere = Electromagnetism::createIonosphere();
    engine.getWorld()->getIonosphereManager()->setIonosphere(ionosphere);
    
    // Create aurora plasma field
    auto aurora = Electromagnetism::createAuroraField();
    engine.getWorld()->getFieldManager()->setPlasmaField(aurora);
    
    // Create charged objects at different altitudes
    auto groundObject = std::make_shared<ChargedObject>(1.0f, 0.1f, 0.5f, Vector2(0.0f, 0.0f));
    auto atmosphereObject = std::make_shared<ChargedObject>(0.5f, 0.1f, 1.0f, Vector2(0.0f, 10000.0f));
    auto ionosphereObject = std::make_shared<ChargedObject>(0.1f, 0.1f, 2.0f, Vector2(0.0f, 100000.0f));
    
    // Set plasma interaction
    groundObject->setPlasmaInteractionFactor(0.2f);
    atmosphereObject->setPlasmaInteractionFactor(0.5f);
    ionosphereObject->setPlasmaInteractionFactor(0.9f);
    
    // Add objects to world
    engine.getWorld()->getObjectManager()->addObject(groundObject);
    engine.getWorld()->getObjectManager()->addObject(atmosphereObject);
    engine.getWorld()->getObjectManager()->addObject(ionosphereObject);
    
    // Create lightning strikes
    std::cout << "Generating lightning strikes..." << std::endl;
    auto lightning1 = Electromagnetism::createLightningStrike(Vector2(-5000.0f, 0.0f));
    auto lightning2 = Electromagnetism::createLightningStrike(Vector2(5000.0f, 0.0f));
    
    fieldManager->addField(lightning1);
    fieldManager->addField(lightning2);
    
    // Output header
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(10) << "Time (s)"
              << std::setw(20) << "Ground Object"
              << std::setw(20) << "Atmosphere Object"
              << std::setw(20) << "Ionosphere Object"
              << std::setw(15) << "Lightning 1"
              << std::setw(15) << "Lightning 2"
              << std::endl;
    std::cout << std::string(90, '-') << std::endl;
    
    // Run simulation
    float timeStep = 0.1f;
    float maxTime = 2.0f;
    
    for (float time = 0; time <= maxTime; time += timeStep) {
        // Update the world
        engine.step(timeStep);
        
        // Check lightning status
        bool lightning1Active = lightning1->isActive();
        bool lightning2Active = lightning2->isActive();
        
        // Output
        std::cout << std::setw(10) << time
                  << std::setw(20) << ("(" + std::to_string(groundObject->getPosition().x) + ", " + 
                                       std::to_string(groundObject->getPosition().y) + ")")
                  << std::setw(20) << ("(" + std::to_string(atmosphereObject->getPosition().x) + ", " + 
                                       std::to_string(atmosphereObject->getPosition().y) + ")")
                  << std::setw(20) << ("(" + std::to_string(ionosphereObject->getPosition().x) + ", " + 
                                       std::to_string(ionosphereObject->getPosition().y) + ")")
                  << std::setw(15) << (lightning1Active ? "Active" : "Inactive")
                  << std::setw(15) << (lightning2Active ? "Active" : "Inactive")
                  << std::endl;
    }
}

// Demo 3: Firmament barrier
void runFirmamentBarrierDemo() {
    std::cout << "\n=== Firmament Barrier Demo ===\n" << std::endl;
    
    Engine engine;
    engine.initialize();
    
    // Set up electromagnetic fields - only firmament barrier
    auto fieldManager = std::make_shared<FieldManager>();
    auto firmament = Electromagnetism::createFirmamentBarrier();
    fieldManager->addField(firmament);
    FieldManager* fieldManagerPtr = fieldManager.get();
    engine.getWorld()->getFieldManager()->copyFrom(*fieldManagerPtr);
    
    // Visualize the firmament field
    visualizeField(*fieldManager, FieldType::Electric, -50.0f, 50.0f, 9989800.0f, 9990200.0f, 40, 20);
    
    // Create objects with different charges approaching the firmament
    auto neutralBalloon = std::make_shared<PhysicsObject>(0.2f, 1.0f, Vector2(-20.0f, 9989500.0f));
    auto positiveCharge = std::make_shared<ChargedObject>(0.1f, 0.5f, 5.0f, Vector2(0.0f, 9989500.0f));
    auto negativeCharge = std::make_shared<ChargedObject>(0.1f, 0.5f, -5.0f, Vector2(20.0f, 9989500.0f));
    
    // Add strong upward velocity to all objects
    neutralBalloon->setVelocity(Vector2(0.0f, 100.0f));
    positiveCharge->setVelocity(Vector2(0.0f, 100.0f));
    negativeCharge->setVelocity(Vector2(0.0f, 100.0f));
    
    // Add objects to world
    engine.getWorld()->getObjectManager()->addObject(neutralBalloon);
    engine.getWorld()->getObjectManager()->addObject(positiveCharge);
    engine.getWorld()->getObjectManager()->addObject(negativeCharge);
    
    // Output header
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(10) << "Time (s)"
              << std::setw(20) << "Neutral Balloon"
              << std::setw(20) << "Positive Charge"
              << std::setw(20) << "Negative Charge"
              << std::setw(20) << "Vel (neutral)"
              << std::setw(20) << "Vel (positive)"
              << std::setw(20) << "Vel (negative)"
              << std::endl;
    std::cout << std::string(120, '-') << std::endl;
    
    // Run simulation
    float timeStep = 0.1f;
    float maxTime = 2.0f;
    
    for (float time = 0; time <= maxTime; time += timeStep) {
        // Update the world
        engine.step(timeStep);
        
        // Output heights and velocities
        std::cout << std::setw(10) << time
                  << std::setw(20) << neutralBalloon->getPosition().y
                  << std::setw(20) << positiveCharge->getPosition().y
                  << std::setw(20) << negativeCharge->getPosition().y
                  << std::setw(20) << neutralBalloon->getVelocity().y
                  << std::setw(20) << positiveCharge->getVelocity().y
                  << std::setw(20) << negativeCharge->getVelocity().y
                  << std::endl;
    }
}

int main() {
    // Run all demos
    runChargedObjectsDemo();
    runPlasmaDemo();
    runFirmamentBarrierDemo();
    
    return 0;
}
