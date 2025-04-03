#include "CompressibleObject.h"
#include "Pressure.h"
#include "../environment/Medium.h"
// Physics constants accessed through Medium and Pressure includes
#include <algorithm>

namespace Archimedes {

CompressibleObject::CompressibleObject(float mass, float volume, float compressibility, const Vector2& position)
    : PhysicsObject(mass, volume, position),
      m_compressibility(compressibility),
      m_referenceVolume(volume),
      m_currentPressure(Pressure::STANDARD_ATMOSPHERIC_PRESSURE) {
}

void CompressibleObject::applyPressure(float pressure) {
    if (m_compressibility <= 0.0f) {
        // Object is incompressible
        return;
    }
    
    // Store previous volume for mass conservation
    float oldVolume = m_volume;
    
    // Calculate volume change using Boyle's Law (P₁V₁ = P₂V₂)
    // Combined with linear compressibility factor
    float volumeRatio = m_currentPressure / pressure;
    float newVolume = m_referenceVolume * std::pow(volumeRatio, m_compressibility);
    
    // Ensure volume doesn't go below minimum (10% of reference)
    newVolume = std::max(newVolume, m_referenceVolume * 0.1f);
    
    // Update the volume
    setVolume(newVolume);
    
    // Store current pressure
    m_currentPressure = pressure;
}

void CompressibleObject::update(float deltaTime, const Medium& medium) {
    // Get ambient pressure based on depth/height
    float depth = -getPosition().y; // Positive y is up, so depth is -y
    float ambientPressure = Pressure::STANDARD_ATMOSPHERIC_PRESSURE;
    
    if (depth > 0) {
        // Object is underwater, add hydrostatic pressure
        ambientPressure += Pressure::calculateHydrostaticPressure(depth, medium.getDensity());
    } else if (depth < 0) {
        // Object is at height, decrease pressure based on atmosphere
        float height = -depth;
        // Simple atmospheric pressure model (decreases with height)
        ambientPressure *= std::exp(-height / 8000.0f); // 8000m is approximate scale height
    }
    
    // Apply pressure to change object volume
    applyPressure(ambientPressure);
    
    // Normal physics update
    PhysicsObject::update(deltaTime, medium);
}

} // namespace Archimedes