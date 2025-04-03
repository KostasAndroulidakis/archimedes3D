#pragma once

namespace Archimedes {
namespace Constants {

/**
 * Constants for environmental properties and conditions
 */
namespace Environment {
    // Atmosphere constants
    constexpr float AIR_SCALE_HEIGHT = 8000.0f;  // m - height at which density is reduced by factor e
    constexpr float INITIAL_HEIGHT = 0.0f;       // m - reference height for atmosphere calculations
    constexpr float DYNAMIC_MEDIUM_INITIAL_HEIGHT = 0.0f; // m - initial height for dynamic medium
    
    /**
     * Standard atmosphere properties at sea level
     */
    namespace Standard {
        constexpr float AIR_DENSITY = 1.2f; // kg/m³
        constexpr float AIR_VISCOSITY = 1.81e-5f; // Pa·s
        constexpr float WATER_DENSITY = 1000.0f; // kg/m³
        constexpr float WATER_VISCOSITY = 1.0e-3f; // Pa·s
        
        constexpr float ATMOSPHERIC_PRESSURE = 101325.0f; // Pa (N/m²)
        constexpr float STANDARD_TEMPERATURE = 288.15f; // K (15°C)
    }
    
    /**
     * Lightning generation parameters
     */
    namespace Lightning {
        constexpr float GENERATION_PROBABILITY = 0.002f; // chance per update
        constexpr float MIN_POSITION_X = -10000.0f; // m
        constexpr float MAX_POSITION_X = 10000.0f; // m
    }
}

} // namespace Constants
} // namespace Archimedes