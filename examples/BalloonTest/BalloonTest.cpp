#include "../../src/core/Engine.h"
#include "../../src/physics/PhysicsObject.h"
#include "../../src/environment/Medium.h"
#include "../../src/utils/Constants.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>

using namespace Archimedes;

// Atmosphere constants for balloon test
namespace BalloonTestConstants {
    constexpr float AIR_SCALE_HEIGHT = 8000.0f;  // m - height at which density is reduced by factor e
    constexpr float BALLOON_VOLUME = 100.0f;     // m³
    constexpr float BALLOON_MASS = 10.0f;        // kg
    constexpr float TIME_STEP = 0.01f;           // s
    constexpr float OUTPUT_INTERVAL = 2.0f;      // s
    constexpr float MAX_SIMULATION_TIME = 60.0f; // s
    constexpr float MAX_ALTITUDE = 10000.0f;     // m
}

// Simple atmosphere with exponential density profile
class SimpleAtmosphere : public Medium {
public:
    SimpleAtmosphere() : Medium(Constants::Environment::Standard::AIR_DENSITY) {}
    
    float getDensityAtHeight(float height) const {
        return Constants::Environment::Standard::AIR_DENSITY * 
               std::exp(-height / BalloonTestConstants::AIR_SCALE_HEIGHT);
    }
    
    float getDensity() const override {
        return getDensityAtHeight(0.0f);
    }
    
    float getViscosity() const override {
        return Constants::Environment::Standard::AIR_VISCOSITY;
    }
};

class DynamicMedium : public Medium {
public:
    DynamicMedium(SimpleAtmosphere& atm) 
        : Medium(atm.getDensity()), m_atmosphere(atm), m_height(0) {}
    
    void updateForHeight(float height) {
        m_height = height;
    }
    
    float getDensity() const override {
        return m_atmosphere.getDensityAtHeight(m_height);
    }
    
private:
    SimpleAtmosphere& m_atmosphere;
    float m_height;
};

int main() {
    // Initialize engine
    Engine engine;
    engine.initialize();
    
    // Create atmosphere
    SimpleAtmosphere atmosphere;
    DynamicMedium medium(atmosphere);
    
    // Create balloon (lighter than air)
    auto balloon = std::make_shared<PhysicsObject>(
        BalloonTestConstants::BALLOON_MASS, 
        BalloonTestConstants::BALLOON_VOLUME, 
        Vector2(0.0f, 0.5f)
    );
    
    // Add to world
    engine.getWorld()->addObject(balloon);
    
    // Output setup
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Time (s)  Height (m)     Velocity (m/s)  Air Density (kg/m³)" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    
    float time = 0.0f;
    float nextOutput = 0.0f;
    
    while (time <= BalloonTestConstants::MAX_SIMULATION_TIME) {
        // Update medium density based on current height
        medium.updateForHeight(balloon->getPosition().y);
        engine.getWorld()->setMedium(medium);
        
        // Run physics step
        engine.step(BalloonTestConstants::TIME_STEP);
        
        // Output
        if (time >= nextOutput) {
            Vector2 position = balloon->getPosition();
            Vector2 velocity = balloon->getVelocity();
            float airDensity = atmosphere.getDensityAtHeight(position.y);
            
            std::cout << std::setw(10) << time 
                     << std::setw(15) << position.y 
                     << std::setw(15) << velocity.y 
                     << std::setw(15) << airDensity << std::endl;
            
            nextOutput += BalloonTestConstants::OUTPUT_INTERVAL;
        }
        
        time += BalloonTestConstants::TIME_STEP;
        
        // Early exit if high enough
        if (balloon->getPosition().y > BalloonTestConstants::MAX_ALTITUDE) {
            std::cout << "Balloon reached " << BalloonTestConstants::MAX_ALTITUDE / 1000.0f << "km altitude." << std::endl;
            break;
        }
    }
    
    return 0;
}
