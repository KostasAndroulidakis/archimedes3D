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
    
    // Ground level (y-coordinate)
    constexpr float GROUND_LEVEL = 0.0f; // m
    
    // Volume to cross-sectional area conversion factor
    constexpr float VOLUME_TO_AREA_EXPONENT = 2.0f/3.0f; // dimensionless
    
    // Epsilon value for floating point comparisons
    constexpr float EPSILON = 0.0001f; // small value for floating point comparisons
    
    // Initial values for objects
    constexpr float INITIAL_VELOCITY_X = 0.0f; // m/s
    constexpr float INITIAL_VELOCITY_Y = 0.0f; // m/s
    constexpr float INITIAL_FORCE_X = 0.0f; // N
    constexpr float INITIAL_FORCE_Y = 0.0f; // N
    constexpr float FORCE_DIRECTION_INVERSION = -1.0f; // dimensionless
}

// Environment constants
namespace Environment {
    // Atmosphere constants
    constexpr float AIR_SCALE_HEIGHT = 8000.0f;  // m - height at which density is reduced by factor e
    constexpr float INITIAL_HEIGHT = 0.0f;       // m - reference height for atmosphere calculations
    constexpr float DYNAMIC_MEDIUM_INITIAL_HEIGHT = 0.0f; // m - initial height for dynamic medium
    
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
    
    // Test object properties
    namespace TestObjects {
        // Stone properties
        constexpr float STONE_MASS = 5.0f;      // kg
        constexpr float STONE_VOLUME = 0.001f;  // m³
        
        // Wood properties
        constexpr float WOOD_MASS = 0.5f;      // kg
        constexpr float WOOD_VOLUME = 0.001f;  // m³
        
        // Balloon properties
        constexpr float BALLOON_MASS = 0.001f;     // kg
        constexpr float BALLOON_VOLUME = 0.001f;   // m³
        
        // Large balloon properties for balloon test
        constexpr float LARGE_BALLOON_VOLUME = 100.0f;     // m³
        constexpr float LARGE_BALLOON_MASS = 10.0f;        // kg
    }
}

// Simulation constants
namespace Simulation {
    constexpr float DEFAULT_TIME_STEP = 0.01f; // seconds
    constexpr float DEMO_TIME_STEP = 0.1f; // seconds for demos
    constexpr int DEFAULT_SIMULATION_STEPS = 5; // number of steps for demos
    constexpr float OUTPUT_INTERVAL = 2.0f;      // s - interval between outputs
    constexpr float MAX_SIMULATION_TIME = 60.0f; // s - maximum simulation time
    constexpr float MAX_ALTITUDE = 10000.0f;     // m - maximum altitude for simulations
    constexpr float INITIAL_TIME = 0.0f;         // s - initial simulation time
    constexpr float INITIAL_OUTPUT_TIME = 0.0f;  // s - initial output time
    constexpr int OUTPUT_PRECISION = 2;          // decimal places for output
    constexpr int OUTPUT_PRECISION_BUOYANCY = 6; // decimal places for buoyancy demo output
    constexpr int OUTPUT_PRECISION_TIME = 1;     // decimal places for time output
    constexpr int KILOMETERS_CONVERSION = 1000;  // conversion factor from m to km
    constexpr int TIME_COLUMN_WIDTH = 10;        // characters for time column width
    constexpr int POSITION_COLUMN_WIDTH = 15;    // characters for position column width
    constexpr int VELOCITY_COLUMN_WIDTH = 15;    // characters for velocity column width
    constexpr int DENSITY_COLUMN_WIDTH = 15;     // characters for density column width
    constexpr int OUTPUT_TABLE_WIDTH = 65;       // characters for table width
    constexpr int OBJECT_NAME_WIDTH = 15;       // width for object name in output
    constexpr float DENSITY_ROUNDING_OFFSET = 0.5f; // offset for rounding density values
    
    // Initial positions for demo objects
    constexpr float INITIAL_X_POSITION_OBJECT1 = 0.0f; // m
    constexpr float INITIAL_X_POSITION_OBJECT2 = 1.0f; // m
    constexpr float INITIAL_X_POSITION_OBJECT3 = 2.0f; // m
    constexpr float INITIAL_Y_POSITION = 0.0f; // m
    constexpr float BALLOON_INITIAL_Y_POSITION = 0.5f; // m - starting height for balloon
    
    // Drag force calculation constants
    constexpr float DRAG_COEFFICIENT_FACTOR = 0.5f; // Factor for drag force calculation
}

// Math constants
namespace Math {
    // Vector constants
    constexpr float VECTOR_DEFAULT_X = 0.0f;
    constexpr float VECTOR_DEFAULT_Y = 0.0f;
}

} // namespace Constants
} // namespace Archimedes