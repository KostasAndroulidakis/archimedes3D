#pragma once

namespace Archimedes {
namespace Constants {

/**
 * Material properties for different substances
 */
namespace Materials {
    constexpr float STONE_DENSITY = 5000.0f; // kg/m³
    constexpr float WOOD_DENSITY = 500.0f; // kg/m³
    constexpr float HELIUM_DENSITY = 0.1786f; // kg/m³
    constexpr float LEAD_DENSITY = 11340.0f; // kg/m³
    constexpr float ALUMINUM_DENSITY = 2700.0f; // kg/m³
    
    /**
     * Properties for test objects used in simulations
     */
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

} // namespace Constants
} // namespace Archimedes