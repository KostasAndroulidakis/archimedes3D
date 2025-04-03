#pragma once

#include <string>

namespace Archimedes {

class AtmosphereLayer {
public:
    AtmosphereLayer(
        const std::string& name,
        float baseDensity,
        float baseTemperature,
        float lowerBoundary,
        float upperBoundary,
        float pressureAtLowerBoundary
    );

    // Core properties
    const std::string& getName() const { return m_name; }
    float getBaseDensity() const { return m_baseDensity; }
    float getBaseTemperature() const { return m_baseTemperature; }
    float getLowerBoundary() const { return m_lowerBoundary; }
    float getUpperBoundary() const { return m_upperBoundary; }
    float getThickness() const { return m_upperBoundary - m_lowerBoundary; }
    float getPressureAtLowerBoundary() const { return m_pressureAtLowerBoundary; }
    
    // Position-dependent properties
    float getDensityAtHeight(float height) const;
    float getPressureAtHeight(float height) const;
    float getTemperatureAtHeight(float height) const;
    float getViscosityAtHeight(float height) const;
    
    // Check if a height is within this layer
    bool containsHeight(float height) const;

private:
    std::string m_name;
    float m_baseDensity;            // kg/m³
    float m_baseTemperature;        // Kelvin
    float m_lowerBoundary;          // Height in meters
    float m_upperBoundary;          // Height in meters
    float m_pressureAtLowerBoundary; // Pressure at layer start (Pa)
    
    // Calculation constants
    static constexpr float LAPSE_RATE = 0.0065f;  // K/m, temperature change with height
    static constexpr float GAS_CONSTANT = 287.05f; // J/(kg·K), specific gas constant for dry air
};

} // namespace Archimedes