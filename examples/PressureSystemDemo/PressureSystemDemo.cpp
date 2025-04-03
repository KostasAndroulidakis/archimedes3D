#include "../../src/core/Engine.h"
#include "../../src/physics/CompressibleObject.h"
#include "../../src/physics/ContainmentVessel.h"
#include "../../src/physics/Pressure.h"
#include "../../src/environment/Medium.h"
// Use LayeredMedium.h which includes AtmosphereLayer.h
#include "../../src/environment/Atmosphere.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace Archimedes;

// Demo 1: Compressible objects at different depths
void runCompressibleObjectsDemo() {
    std::cout << "\n=== Compressible Objects Demo ===\n" << std::endl;
    
    Engine engine;
    engine.initialize();
    
    // Create water medium
    Medium water(1000.0f, 1.0f); // 1000 kg/m³
    engine.getWorld()->setMedium(water);
    
    // Create objects with different compressibility
    auto incompressible = std::make_shared<CompressibleObject>(1.0f, 0.001f, 0.0f, Vector2(0.0f, -1.0f));
    auto moderate = std::make_shared<CompressibleObject>(1.0f, 0.001f, 0.5f, Vector2(1.0f, -1.0f));
    auto highlyCompressible = std::make_shared<CompressibleObject>(1.0f, 0.001f, 0.9f, Vector2(2.0f, -1.0f));
    
    // Add objects to world
    engine.getWorld()->addObject(incompressible);
    engine.getWorld()->addObject(moderate);
    engine.getWorld()->addObject(highlyCompressible);
    
    // Output header
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::left << std::setw(10) << "Depth (m)"
              << std::setw(15) << "Pressure (Pa)"
              << std::setw(15) << "Incomp. Vol."
              << std::setw(15) << "Moderate Vol."
              << std::setw(15) << "High Comp. Vol."
              << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    // Simulate at different depths
    std::vector<float> depths = {0, 10, 20, 50, 100, 500, 1000};
    
    for (float depth : depths) {
        // Set positions
        incompressible->setPosition(Vector2(0.0f, -depth));
        moderate->setPosition(Vector2(1.0f, -depth));
        highlyCompressible->setPosition(Vector2(2.0f, -depth));
        
        // Update once to calculate pressure effects
        engine.step(0.1f);
        
        // Calculate pressure at this depth
        float pressure = Pressure::STANDARD_ATMOSPHERIC_PRESSURE +
                         Pressure::calculateHydrostaticPressure(depth, water.getDensity());
        
        // Output results
        std::cout << std::setw(10) << depth
                  << std::setw(15) << pressure
                  << std::setw(15) << incompressible->getVolume()
                  << std::setw(15) << moderate->getVolume()
                  << std::setw(15) << highlyCompressible->getVolume()
                  << std::endl;
    }
}

// Demo 2: Containment vessels with different internal pressures
void runContainmentVesselDemo() {
    std::cout << "\n=== Containment Vessel Demo ===\n" << std::endl;
    
    Engine engine;
    engine.initialize();
    
    // Set up atmosphere
    auto atmosphere = Atmosphere::createStandardModel();
    engine.getWorld()->setLayeredMedium(atmosphere);
    
    // Create vessels with different internal pressures
    auto lowPressure = std::make_shared<ContainmentVessel>(
        5.0f, 0.5f, 0.02f, 500000.0f, Vector2(0.0f, 0.0f)
    );
    
    auto normalPressure = std::make_shared<ContainmentVessel>(
        5.0f, 0.5f, 0.02f, 500000.0f, Vector2(1.0f, 0.0f)
    );
    
    auto highPressure = std::make_shared<ContainmentVessel>(
        5.0f, 0.5f, 0.02f, 500000.0f, Vector2(2.0f, 0.0f)
    );
    
    // Set internal pressures
    lowPressure->setInternalPressure(50000.0f); // 50% atmospheric pressure (partial vacuum)
    normalPressure->setInternalPressure(Pressure::STANDARD_ATMOSPHERIC_PRESSURE);
    highPressure->setInternalPressure(200000.0f); // 2x atmospheric pressure
    
    // Create compressible objects inside each vessel
    auto balloonLow = std::make_shared<CompressibleObject>(0.01f, 0.01f, 0.8f, Vector2(0.0f, 0.0f));
    auto balloonNormal = std::make_shared<CompressibleObject>(0.01f, 0.01f, 0.8f, Vector2(1.0f, 0.0f));
    auto balloonHigh = std::make_shared<CompressibleObject>(0.01f, 0.01f, 0.8f, Vector2(2.0f, 0.0f));
    
    // Add objects to vessels
    lowPressure->addObject(balloonLow);
    normalPressure->addObject(balloonNormal);
    highPressure->addObject(balloonHigh);
    
    // Add vessels to world
    engine.getWorld()->addObject(lowPressure);
    engine.getWorld()->addObject(normalPressure);
    engine.getWorld()->addObject(highPressure);
    
    // Output header
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::left << std::setw(10) << "Height (m)"
              << std::setw(15) << "Ext. Pressure"
              << std::setw(15) << "Low Pres. Bal."
              << std::setw(15) << "Norm Pres. Bal."
              << std::setw(15) << "High Pres. Bal."
              << std::setw(15) << "Low Ruptured"
              << std::setw(15) << "High Ruptured"
              << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    // Simulate at different heights
    std::vector<float> heights = {0, 1000, 5000, 10000, 20000, 30000};
    
    for (float height : heights) {
        // Set positions
        lowPressure->setPosition(Vector2(0.0f, height));
        normalPressure->setPosition(Vector2(1.0f, height));
        highPressure->setPosition(Vector2(2.0f, height));
        
        // Update objects
        engine.step(0.1f);
        
        // Get external pressure at this height
        float externalPressure = atmosphere->getPressureAtHeight(height);
        
        // Output results
        std::cout << std::setw(10) << height
                  << std::setw(15) << externalPressure
                  << std::setw(15) << balloonLow->getVolume()
                  << std::setw(15) << balloonNormal->getVolume()
                  << std::setw(15) << balloonHigh->getVolume()
                  << std::setw(15) << (lowPressure->isRuptured() ? "Yes" : "No")
                  << std::setw(15) << (highPressure->isRuptured() ? "Yes" : "No")
                  << std::endl;
    }
}

// Demo 3: Pressure-resistant deep-sea object
void runDeepSeaDemo() {
    std::cout << "\n=== Deep Sea Pressure Demo ===\n" << std::endl;
    
    Engine engine;
    engine.initialize();
    
    // Create ocean medium (saltwater)
    Medium ocean(1025.0f, 1.0f); // 1025 kg/m³
    engine.getWorld()->setMedium(ocean);
    
    // Create a submersible vessel with high pressure resistance
    auto submarine = std::make_shared<ContainmentVessel>(
        100.0f, 2.0f, 0.1f, 10000000.0f, Vector2(0.0f, 0.0f)
    );
    
    // Create standard vessel with moderate pressure resistance
    auto standardVessel = std::make_shared<ContainmentVessel>(
        10.0f, 0.5f, 0.02f, 500000.0f, Vector2(1.0f, 0.0f)
    );
    
    // Add vessels to world
    engine.getWorld()->addObject(submarine);
    engine.getWorld()->addObject(standardVessel);
    
    // Output header
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::left << std::setw(10) << "Depth (m)"
              << std::setw(15) << "Pressure (Pa)"
              << std::setw(15) << "Sub. Volume"
              << std::setw(15) << "Std. Volume"
              << std::setw(15) << "Sub. Ruptured"
              << std::setw(15) << "Std. Ruptured"
              << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    // Simulate at increasing depths
    std::vector<float> depths = {0, 10, 50, 100, 500, 1000, 5000, 10000};
    
    for (float depth : depths) {
        // Set positions
        submarine->setPosition(Vector2(0.0f, -depth));
        standardVessel->setPosition(Vector2(1.0f, -depth));
        
        // Update objects
        engine.step(0.1f);
        
        // Calculate pressure at this depth
        float pressure = Pressure::STANDARD_ATMOSPHERIC_PRESSURE +
                         Pressure::calculateHydrostaticPressure(depth, ocean.getDensity());
        
        // Output results
        std::cout << std::setw(10) << depth
                  << std::setw(15) << pressure
                  << std::setw(15) << submarine->getVolume()
                  << std::setw(15) << standardVessel->getVolume()
                  << std::setw(15) << (submarine->isRuptured() ? "Yes" : "No")
                  << std::setw(15) << (standardVessel->isRuptured() ? "Yes" : "No")
                  << std::endl;
    }
}

int main() {
    // Run all demos
    runCompressibleObjectsDemo();
    runContainmentVesselDemo();
    runDeepSeaDemo();
    
    return 0;
}
