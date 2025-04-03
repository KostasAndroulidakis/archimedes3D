#pragma once

namespace Archimedes {
namespace Constants {

/**
 * Constants related to simulation parameters and output formatting
 */
namespace Simulation {
    // Timing constants
    constexpr float DEFAULT_TIME_STEP = 0.01f; // seconds
    constexpr float DEMO_TIME_STEP = 0.1f; // seconds for demos
    constexpr int DEFAULT_SIMULATION_STEPS = 5; // number of steps for demos
    constexpr float OUTPUT_INTERVAL = 2.0f;      // s - interval between outputs
    constexpr float MAX_SIMULATION_TIME = 60.0f; // s - maximum simulation time
    constexpr float MAX_ALTITUDE = 10000.0f;     // m - maximum altitude for simulations
    constexpr float INITIAL_TIME = 0.0f;         // s - initial simulation time
    constexpr float INITIAL_OUTPUT_TIME = 0.0f;  // s - initial output time
    
    // Output formatting constants
    constexpr int OUTPUT_PRECISION = 2;          // decimal places for output
    constexpr int OUTPUT_PRECISION_BUOYANCY = 6; // decimal places for buoyancy demo output
    constexpr int OUTPUT_PRECISION_TIME = 1;     // decimal places for time output
    constexpr int KILOMETERS_CONVERSION = 1000;  // conversion factor from m to km
    constexpr int TIME_COLUMN_WIDTH = 10;        // characters for time column width
    constexpr int POSITION_COLUMN_WIDTH = 15;    // characters for position column width
    constexpr int VELOCITY_COLUMN_WIDTH = 15;    // characters for velocity column width
    constexpr int DENSITY_COLUMN_WIDTH = 15;     // characters for density column width
    constexpr int OUTPUT_TABLE_WIDTH = 65;       // characters for table width
    constexpr int OBJECT_NAME_WIDTH = 15;        // width for object name in output
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

} // namespace Constants
} // namespace Archimedes