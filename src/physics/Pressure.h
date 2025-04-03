#pragma once

#include "../constants/EnvironmentConstants.h"

namespace Archimedes {

class Pressure {
public:
    // Constants
    static constexpr float STANDARD_ATMOSPHERIC_PRESSURE = Constants::Environment::Standard::ATMOSPHERIC_PRESSURE; // Pa at sea level
    
    // Calculate hydrostatic pressure at depth in fluid
    static float calculateHydrostaticPressure(float depth, float fluidDensity);
    
    // Calculate pressure difference between two points
    static float calculatePressureDifference(float pressure1, float pressure2);
    
    // Calculate force on area due to pressure
    static float calculateForce(float pressure, float area);
    
    // Calculate volume change under pressure (for ideal gas)
    static float calculateVolumeChange(float initialVolume, float initialPressure, 
                                     float finalPressure, float temperature);
};

} // namespace Archimedes