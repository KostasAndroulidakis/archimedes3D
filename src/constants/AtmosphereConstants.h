#pragma once

namespace Archimedes {
namespace Constants {
namespace Environment {

/**
 * Atmospheric layer properties and structure
 */
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

} // namespace Environment
} // namespace Constants
} // namespace Archimedes