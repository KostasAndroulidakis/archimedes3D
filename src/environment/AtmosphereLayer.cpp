#include "AtmosphereLayer.h"
#include <cmath>
#include <algorithm>

namespace Archimedes {

AtmosphereLayer::AtmosphereLayer(
    const std::string& name,
    float baseDensity,
    float baseTemperature,
    float lowerBoundary,
    float upperBoundary,
    float pressureAtLowerBoundary
) : m_name(name),
    m_baseDensity(baseDensity),
    m_baseTemperature(baseTemperature),
    m_lowerBoundary(lowerBoundary),
    m_upperBoundary(upperBoundary),
    m_pressureAtLowerBoundary(pressureAtLowerBoundary) {
}

bool AtmosphereLayer::containsHeight(float height) const {
    return height >= m_lowerBoundary && height < m_upperBoundary;
}

float AtmosphereLayer::getTemperatureAtHeight(float height) const {
    // Temperature calculation with protection against non-physical values
    float relativeHeight = height - m_lowerBoundary;
    float temp = m_baseTemperature - LAPSE_RATE * relativeHeight;
    
    // Ensure temperature doesn't go below 2K (physical minimum)
    return std::max(temp, 2.0f);
}

float AtmosphereLayer::getPressureAtHeight(float height) const {
    // Ensure height is within reasonable bounds to prevent extreme calculations
    float clampedHeight = std::min(height, m_upperBoundary - 1.0f);
    clampedHeight = std::max(clampedHeight, m_lowerBoundary);
    
    float relativeHeight = clampedHeight - m_lowerBoundary;
    float temperature = getTemperatureAtHeight(clampedHeight);
    
    // Handle different temperature profiles
    if (std::abs(LAPSE_RATE) < 0.0001f) {
        // Isothermal case
        float scale = 9.8f / (GAS_CONSTANT * m_baseTemperature);
        float pressure = m_pressureAtLowerBoundary * std::exp(-scale * relativeHeight);
        return std::max(pressure, 0.0f);
    } else {
        // Non-isothermal case
        float exponent = 9.8f / (GAS_CONSTANT * LAPSE_RATE);
        float ratio = temperature / m_baseTemperature;
        if (ratio <= 0) return 0.0f; // Handle negative temperatures gracefully
        
        float pressure = m_pressureAtLowerBoundary * std::pow(ratio, exponent);
        return std::max(pressure, 0.0f);
    }
}

float AtmosphereLayer::getDensityAtHeight(float height) const {
    // Calculate density safely from ideal gas law: ρ = P/(RT)
    float pressure = getPressureAtHeight(height);
    float temperature = getTemperatureAtHeight(height);
    
    // Prevent division by zero or near-zero
    if (temperature < 0.1f) return 0.0f;
    
    float density = pressure / (GAS_CONSTANT * temperature);
    return std::max(density, 0.0f);
}

float AtmosphereLayer::getViscosityAtHeight(float height) const {
    // Sutherland's formula with safeguards
    float temperature = getTemperatureAtHeight(height);
    const float S = 110.4f; // Sutherland constant for air, K
    const float refTemp = 273.15f; // Reference temperature, K
    const float refViscosity = 1.715e-5f; // Reference viscosity, kg/(m·s)
    
    // Prevent non-physical temperature values
    if (temperature < 0.1f) return refViscosity * 0.01f;
    
    return refViscosity * std::pow(temperature / refTemp, 1.5f) * 
           (refTemp + S) / (temperature + S);
}

} // namespace Archimedes