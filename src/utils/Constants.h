#pragma once

namespace Archimedes {
namespace Constants {

// Physics constants
namespace Physics {
    // Displacement factor (equivalent to Earth gravity acceleration)
    constexpr float DISPLACEMENT_FACTOR = 9.8f; // m/s²
    
    // Standard drag coefficient for regular shapes
    constexpr float STANDARD_DRAG_COEFFICIENT = 0.47f; // dimensionless
    
    // Maximum allowed terminal velocity to prevent numerical issues
    constexpr float MAX_TERMINAL_VELOCITY = 100.0f; // m/s
    
    // Energy loss factor when colliding with ground
    constexpr float GROUND_COLLISION_ENERGY_LOSS = 0.8f; // 80% energy loss, dimensionless
    constexpr float VELOCITY_DAMPENING = 0.2f; // 20% of original velocity retained after collision
    
    // Small value threshold for velocity calculations
    constexpr float VELOCITY_THRESHOLD = 0.001f; // m/s
}

// Environment constants
namespace Environment {
    // Standard atmosphere properties at sea level
    namespace Standard {
        constexpr float AIR_DENSITY = 1.2f; // kg/m³
        constexpr float AIR_VISCOSITY = 1.81e-5f; // Pa·s
        constexpr float WATER_DENSITY = 1000.0f; // kg/m³
        constexpr float WATER_VISCOSITY = 1.0e-3f; // Pa·s
        
        constexpr float ATMOSPHERIC_PRESSURE = 101325.0f; // Pa (N/m²)
        constexpr float STANDARD_TEMPERATURE = 288.15f; // K (15°C)
    }
    
    // Lightning generation parameters
    namespace Lightning {
        constexpr float GENERATION_PROBABILITY = 0.002f; // chance per update
        constexpr float MIN_POSITION_X = -10000.0f; // m
        constexpr float MAX_POSITION_X = 10000.0f; // m
    }
    
    // Atmospheric layer properties
    namespace Atmosphere {
        // Troposphere: 0-12km, where weather occurs
        namespace Troposphere {
            constexpr float DENSITY = 1.225f; // kg/m³
            constexpr float TEMPERATURE = 288.15f; // K
            constexpr float LOWER_BOUNDARY = 0.0f; // m
            constexpr float UPPER_BOUNDARY = 12000.0f; // m
            constexpr float PRESSURE = 101325.0f; // Pa
        }
        
        // Stratosphere: 12-50km, contains ozone layer
        namespace Stratosphere {
            constexpr float DENSITY = 0.36f; // kg/m³
            constexpr float TEMPERATURE = 216.65f; // K
            constexpr float LOWER_BOUNDARY = 12000.0f; // m
            constexpr float UPPER_BOUNDARY = 50000.0f; // m
            constexpr float PRESSURE = 19399.0f; // Pa
        }
        
        // Mesosphere: 50-85km, where meteors burn up
        namespace Mesosphere {
            constexpr float DENSITY = 0.001f; // kg/m³
            constexpr float TEMPERATURE = 270.65f; // K
            constexpr float LOWER_BOUNDARY = 50000.0f; // m
            constexpr float UPPER_BOUNDARY = 85000.0f; // m
            constexpr float PRESSURE = 75.65f; // Pa
        }
        
        // Thermosphere: 85-600km, where aurora occurs
        namespace Thermosphere {
            constexpr float DENSITY = 0.00001f; // kg/m³
            constexpr float TEMPERATURE = 186.87f; // K
            constexpr float LOWER_BOUNDARY = 85000.0f; // m
            constexpr float UPPER_BOUNDARY = 600000.0f; // m
            constexpr float PRESSURE = 0.3734f; // Pa
        }
        
        // Exosphere: 600-10,000km, transitioning to vacuum
        namespace Exosphere {
            constexpr float DENSITY = 0.000000001f; // kg/m³
            constexpr float TEMPERATURE = 1000.0f; // K
            constexpr float LOWER_BOUNDARY = 600000.0f; // m
            constexpr float UPPER_BOUNDARY = 10000000.0f; // m
            constexpr float PRESSURE = 0.0002f; // Pa
        }
        
        // Ionosphere: 60-1000km, electrically charged layer
        namespace Ionosphere {
            constexpr float DENSITY = 0.000001f; // kg/m³
            constexpr float TEMPERATURE = 1500.0f; // K
            constexpr float LOWER_BOUNDARY = 60000.0f; // m
            constexpr float UPPER_BOUNDARY = 1000000.0f; // m
            constexpr float PRESSURE = 0.1f; // Pa
        }
        
        // Firmament: The dome above
        namespace Firmament {
            constexpr float DENSITY = 2.5f; // kg/m³
            constexpr float TEMPERATURE = 4.0f; // K
            constexpr float LOWER_BOUNDARY = 10000000.0f; // m
            constexpr float UPPER_BOUNDARY = 10001000.0f; // m
            constexpr float PRESSURE = 0.0f; // Pa
        }
    }
}

// Material constants - example densities
namespace Materials {
    constexpr float STONE_DENSITY = 5000.0f; // kg/m³
    constexpr float WOOD_DENSITY = 500.0f; // kg/m³
    constexpr float HELIUM_DENSITY = 0.1786f; // kg/m³
    constexpr float LEAD_DENSITY = 11340.0f; // kg/m³
    constexpr float ALUMINUM_DENSITY = 2700.0f; // kg/m³
}

// Simulation constants
namespace Simulation {
    constexpr float DEFAULT_TIME_STEP = 0.01f; // seconds
    
    // Drag force calculation constants
    constexpr float DRAG_COEFFICIENT_FACTOR = 0.5f; // Factor for drag force calculation
}

} // namespace Constants
} // namespace Archimedes