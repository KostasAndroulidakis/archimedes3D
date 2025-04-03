#pragma once

namespace Archimedes {
namespace Constants {

/**
 * Physics-related constants for simulations
 */
namespace Physics {
    // Buoyancy constants
    constexpr float BUOYANCY_COEFFICIENT = 1.0f; // Coefficient for buoyancy force calculation
    constexpr float DENSITY_DIFFERENTIAL_FACTOR = 1.0f; // Factor for converting density differential to force
    
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

} // namespace Constants
} // namespace Archimedes