#include "ChargedObject.h"
#include "../environment/Medium.h"
// Using physics constants through Vector2 and Medium includes

namespace Archimedes {

ChargedObject::ChargedObject(float mass, float volume, float charge, const Vector2& position)
    : PhysicsObject(mass, volume, position),
      m_charge(charge),
      m_magneticSusceptibility(1.0f),
      m_plasmaInteractionFactor(0.5f) {
}

void ChargedObject::update(float deltaTime, const Medium& medium) {
    // Base physics update (buoyancy, etc.)
    PhysicsObject::update(deltaTime, medium);
}

void ChargedObject::applyElectromagneticForce(const Vector2& electricField, const Vector2& magneticField) {
    // Calculate Lorentz force
    Vector2 lorentzForce = calculateLorentzForce(electricField, magneticField);
    
    // Scale force for better visibility in simulation
    lorentzForce = lorentzForce * 50.0f;
    
    // Apply the force
    applyForce(lorentzForce);
}

Vector2 ChargedObject::calculateLorentzForce(const Vector2& electricField, const Vector2& magneticField) const {
    if (m_charge == 0.0f) {
        return Vector2(0.0f, 0.0f);
    }
    
    // Electric force component (F = qE)
    Vector2 electricForce = electricField * m_charge;
    
    // Magnetic force component (F = q(v × B))
    // In 2D, v × B = |v||B|sin(θ) perpendicular to plane
    float magneticCrossMagnitude = m_velocity.x * magneticField.y - m_velocity.y * magneticField.x;
    
    // Direction perpendicular to velocity
    Vector2 magneticDirection(-m_velocity.y, m_velocity.x);
    
    // Force magnitude with charge for direction
    float magneticForceMagnitude = m_charge * magneticCrossMagnitude;
    
    // Normalize and scale if non-zero
    float magneticDirLength = magneticDirection.magnitude();
    if (magneticDirLength > 0.0001f) {
        magneticDirection = magneticDirection * (1.0f / magneticDirLength);
        Vector2 magneticForce = magneticDirection * magneticForceMagnitude * m_magneticSusceptibility;
        return electricForce + magneticForce;
    }
    
    return electricForce;
}

} // namespace Archimedes