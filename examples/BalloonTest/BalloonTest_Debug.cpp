#include "../../src/core/Engine.h"
#include "../../src/physics/PhysicsObject.h"
#include "../../src/environment/Medium.h"
#include "../../src/constants/Constants.h"
#include "../../src/managers/ObjectManager.h"
#include "../../src/managers/MediumManager.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace Archimedes;

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
    // Debug output
    std::ofstream debugFile("balloon_debug.txt");
    debugFile << "BalloonTest Debug Output" << std::endl;
    debugFile << "======================" << std::endl;
    
    std::cerr << "Starting BalloonTest with debug output..." << std::endl;
    
    try {
        // Initialize engine
        Engine engine;
        bool initialized = engine.initialize();
        debugFile << "Engine initialized: " << (initialized ? "Yes" : "No") << std::endl;
        std::cerr << "Engine initialized: " << (initialized ? "Yes" : "No") << std::endl;
        
        // Create atmosphere
        SimpleAtmosphere atmosphere;
        DynamicMedium medium(atmosphere);
        debugFile << "Created atmosphere and medium" << std::endl;
        
        // Create balloon (lighter than air)
        auto balloon = std::make_shared<PhysicsObject>(
            Constants::Materials::TestObjects::LARGE_BALLOON_MASS, 
            Constants::Materials::TestObjects::LARGE_BALLOON_VOLUME, 
            Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT1, Constants::Simulation::BALLOON_INITIAL_Y_POSITION)
        );
        debugFile << "Created balloon with mass: " << Constants::Materials::TestObjects::LARGE_BALLOON_MASS
                 << ", volume: " << Constants::Materials::TestObjects::LARGE_BALLOON_VOLUME << std::endl;
        
        // Add to world
        engine.getWorld()->getObjectManager()->addObject(balloon);
        debugFile << "Added balloon to world" << std::endl;
        
        // Output setup to both console and debug file
        const char* header = "Time (s)  Height (m)     Velocity (m/s)  Air Density (kg/m³)";
        std::cout << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION);
        std::cout << header << std::endl;
        std::cout << std::string(Constants::Simulation::OUTPUT_TABLE_WIDTH, '-') << std::endl;
        
        debugFile << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION);
        debugFile << header << std::endl;
        debugFile << std::string(Constants::Simulation::OUTPUT_TABLE_WIDTH, '-') << std::endl;
        
        // Flush the output buffers
        std::cout.flush();
        
        float time = Constants::Simulation::INITIAL_TIME;
        float nextOutput = Constants::Simulation::INITIAL_OUTPUT_TIME;
        
        debugFile << "Starting simulation loop" << std::endl;
        
        // Force immediate output
        std::cout << "Simulation starting at time: " << time << " seconds" << std::endl;
        std::cout.flush();
        
        int stepCount = 0;
        
        while (time <= Constants::Simulation::MAX_SIMULATION_TIME) {
            // Update medium density based on current height
            medium.updateForHeight(balloon->getPosition().y);
            engine.getWorld()->getMediumManager()->setMedium(medium);
            
            // Run physics step
            engine.step(Constants::Simulation::DEFAULT_TIME_STEP);
            stepCount++;
            
            // Output
            if (time >= nextOutput) {
                Vector2 position = balloon->getPosition();
                Vector2 velocity = balloon->getVelocity();
                float airDensity = atmosphere.getDensityAtHeight(position.y);
                
                // Create the output line
                std::stringstream outputLine;
                outputLine << std::fixed << std::setprecision(Constants::Simulation::OUTPUT_PRECISION)
                          << std::setw(Constants::Simulation::TIME_COLUMN_WIDTH) << time 
                          << std::setw(Constants::Simulation::POSITION_COLUMN_WIDTH) << position.y 
                          << std::setw(Constants::Simulation::VELOCITY_COLUMN_WIDTH) << velocity.y 
                          << std::setw(Constants::Simulation::DENSITY_COLUMN_WIDTH) << airDensity;
                
                // Output to both console and debug file
                std::cout << outputLine.str() << std::endl;
                debugFile << outputLine.str() << std::endl;
                
                // Force immediate output
                std::cout.flush();
                
                nextOutput += Constants::Simulation::OUTPUT_INTERVAL;
            }
            
            time += Constants::Simulation::DEFAULT_TIME_STEP;
            
            // Early exit if high enough
            if (balloon->getPosition().y > Constants::Simulation::MAX_ALTITUDE) {
                std::string exitMsg = "Balloon reached " + 
                                     std::to_string(Constants::Simulation::MAX_ALTITUDE / 
                                                  Constants::Simulation::KILOMETERS_CONVERSION) + 
                                     "km altitude.";
                std::cout << exitMsg << std::endl;
                debugFile << exitMsg << std::endl;
                break;
            }
        }
        
        debugFile << "Simulation completed after " << stepCount << " steps" << std::endl;
        std::cout << "Simulation completed after " << stepCount << " steps" << std::endl;
        
    } catch (const std::exception& e) {
        debugFile << "EXCEPTION: " << e.what() << std::endl;
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    } catch (...) {
        debugFile << "UNKNOWN EXCEPTION" << std::endl;
        std::cerr << "UNKNOWN EXCEPTION" << std::endl;
    }
    
    debugFile.close();
    std::cerr << "BalloonTest completed - check balloon_debug.txt for detailed output" << std::endl;
    
    return 0;
}
