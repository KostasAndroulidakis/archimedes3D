#include "../../src/core/Engine.h"
#include "../../src/physics/PhysicsObject.h"
#include "../../src/environment/Medium.h"
// Not actually using AtmosphereLayer directly in this file
//#include "../../src/environment/AtmosphereLayer.h"
#include "../../src/constants/Constants.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>

using namespace Archimedes;

// Using constants from the Constants namespace

// Simple atmosphere with exponential density profile
class SimpleAtmosphere : public Medium {
public:
    SimpleAtmosphere() : Medium(Constants::Environment::Standard::AIR_DENSITY) {}
    
    float getDensityAtHeight(float height) const {
        return Constants::Environment::Standard::AIR_DENSITY * 
               std::exp(-height / Constants::Environment::AIR_SCALE_HEIGHT);
    }
    
    float getDensity() const override {
        return getDensityAtHeight(Constants::Environment::INITIAL_HEIGHT);
    }
    
    float getViscosity() const override {
        return Constants::Environment::Standard::AIR_VISCOSITY;
    }
};

class DynamicMedium : public Medium {
public:
    DynamicMedium(SimpleAtmosphere& atm) 
        : Medium(atm.getDensity()), m_atmosphere(atm), m_height(Constants::Environment::DYNAMIC_MEDIUM_INITIAL_HEIGHT) {}
    
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
        Constants::Materials::TestObjects::LARGE_BALLOON_MASS, 
        Constants::Materials::TestObjects::LARGE_BALLOON_VOLUME, 
        Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT1, Constants::Simulation::BALLOON_INITIAL_Y_POSITION)
    );
    
    // Add to world
    engine.getWorld()->getObjectManager()->addObject(balloon);
    
    // Output setup
    std::cout << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION);
    std::cout << "Time (s)  Height (m)     Velocity (m/s)  Air Density (kg/m³)" << std::endl;
    std::cout << std::string(Constants::Simulation::OUTPUT_TABLE_WIDTH, '-') << std::endl;
    
    float time = Constants::Simulation::INITIAL_TIME;
    float nextOutput = Constants::Simulation::INITIAL_OUTPUT_TIME;
    
    while (time <= Constants::Simulation::MAX_SIMULATION_TIME) {
        // Update medium density based on current height
        medium.updateForHeight(balloon->getPosition().y);
        engine.getWorld()->getMediumManager()->setMedium(medium);
        
        // Run physics step
        engine.step(Constants::Simulation::DEFAULT_TIME_STEP);
        
        // Output
        if (time >= nextOutput) {
            Vector2 position = balloon->getPosition();
            Vector2 velocity = balloon->getVelocity();
            float airDensity = atmosphere.getDensityAtHeight(position.y);
            
            std::cout << std::setw(Constants::Simulation::TIME_COLUMN_WIDTH) << time 
                     << std::setw(Constants::Simulation::POSITION_COLUMN_WIDTH) << position.y 
                     << std::setw(Constants::Simulation::VELOCITY_COLUMN_WIDTH) << velocity.y 
                     << std::setw(Constants::Simulation::DENSITY_COLUMN_WIDTH) << airDensity << std::endl;
            
            nextOutput += Constants::Simulation::OUTPUT_INTERVAL;
        }
        
        time += Constants::Simulation::DEFAULT_TIME_STEP;
        
        // Early exit if high enough
        if (balloon->getPosition().y > Constants::Simulation::MAX_ALTITUDE) {
            std::cout << "Balloon reached " << Constants::Simulation::MAX_ALTITUDE / Constants::Simulation::KILOMETERS_CONVERSION << "km altitude." << std::endl;
            break;
        }
    }
    
    return 0;
}
