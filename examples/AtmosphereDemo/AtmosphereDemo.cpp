#include "../../src/core/Engine.h"
#include "../../src/physics/PhysicsObject.h"
#include "../../src/environment/LayeredMedium.h" // This already includes AtmosphereLayer.h
#include "../../src/environment/Atmosphere.h"
#include "../../src/managers/ObjectManager.h"
#include "../../src/managers/MediumManager.h"
#include <iostream>
#include <memory>
#include <iomanip>

using namespace Archimedes;

void printAtmosphereProperties(std::shared_ptr<LayeredMedium> atmosphere) {
    std::cout << "=== Atmosphere Model ===" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    // Print properties at different heights
    std::cout << std::left << std::setw(10) << "Height (m)" 
              << std::setw(15) << "Density (kg/m³)" 
              << std::setw(15) << "Pressure (Pa)" 
              << std::setw(15) << "Temp (K)" 
              << "Layer" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    float heights[] = {0, 1000, 5000, 10000, 20000, 30000, 50000, 80000, 100000};
    
    for (float height : heights) {
        auto layer = atmosphere->getLayerAtHeight(height);
        std::string layerName = layer ? layer->getName() : "Unknown";
        
        std::cout << std::setw(10) << height 
                  << std::setw(15) << atmosphere->getDensityAtHeight(height) 
                  << std::setw(15) << atmosphere->getPressureAtHeight(height) 
                  << std::setw(15) << atmosphere->getTemperatureAtHeight(height) 
                  << layerName << std::endl;
    }
    std::cout << std::endl;
}

void simulateBalloonAscent(Engine& engine, std::shared_ptr<LayeredMedium> atmosphere) {
    std::cout << "=== Balloon Ascent Simulation ===" << std::endl;
    
    // Create a helium balloon (typical helium density is 0.1786 kg/m³)
    // Let's make a large balloon with 100m³ volume and total mass of 10kg (including payload)
    // This gives a density of 0.1 kg/m³, which is less than air (1.225 kg/m³)
    const float balloonVolume = 100.0f;
    const float balloonMass = 10.0f;
    
    std::cout << "Balloon properties:" << std::endl;
    std::cout << "  Volume: " << balloonVolume << " m³" << std::endl;
    std::cout << "  Total mass: " << balloonMass << " kg" << std::endl;
    std::cout << "  Density: " << (balloonMass / balloonVolume) << " kg/m³" << std::endl;
    std::cout << "  Air density at sea level: " << atmosphere->getDensityAtHeight(0.0f) << " kg/m³" << std::endl;
    std::cout << "  Buoyancy factor: " << (atmosphere->getDensityAtHeight(0.0f) / (balloonMass / balloonVolume)) << std::endl;
    std::cout << std::endl;
    
    auto balloon = std::make_shared<PhysicsObject>(balloonMass, balloonVolume, Vector2(0.0f, 0.1f));
    engine.getWorld()->getObjectManager()->addObject(balloon);
    
    std::cout << std::left << std::setw(10) << "Time (s)" 
              << std::setw(15) << "Height (m)" 
              << std::setw(15) << "Velocity (m/s)" 
              << std::setw(15) << "Density (kg/m³)"
              << "Layer" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    const float timeStep = 10.0f; // 10 second steps
    const float simulationTime = 300.0f; // 5 minutes total
    
    for (float time = 0; time <= simulationTime; time += timeStep) {
        Vector2 position = balloon->getPosition();
        Vector2 velocity = balloon->getVelocity();
        float airDensity = atmosphere->getDensityAtHeight(position.y);
        auto layer = atmosphere->getLayerAtHeight(position.y);
        std::string layerName = layer ? layer->getName() : "Unknown";
        
        std::cout << std::setw(10) << time 
                  << std::setw(15) << position.y 
                  << std::setw(15) << velocity.y 
                  << std::setw(15) << airDensity
                  << layerName << std::endl;
        
        // Simulate with smaller steps for accuracy
        for (int i = 0; i < 10; i++) {
            engine.step(timeStep / 10.0f);
        }
    }
    std::cout << std::endl;
}

// Demonstrate objects at different atmospheric heights
int main() {
    // Initialize engine
    Engine engine;
    engine.initialize();
    
    // Create atmosphere model
    auto atmosphere = Atmosphere::createStandardModel();
    
    // Set the world to use the layered medium
    engine.getWorld()->getMediumManager()->setLayeredMedium(atmosphere);
    
    // Print atmosphere properties
    printAtmosphereProperties(atmosphere);
    
    // Simulate balloon ascent
    simulateBalloonAscent(engine, atmosphere);
    
    return 0;
}
