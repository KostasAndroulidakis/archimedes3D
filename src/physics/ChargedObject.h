#pragma once

#include "PhysicsObject.h"

// Forward declarations for constants
namespace Archimedes {
namespace Constants {
namespace Physics {
// Forward declarations if needed
}
}
}

namespace Archimedes {

class ChargedObject : public PhysicsObject {
public:
    ChargedObject(float mass, float volume, float charge, const Vector2& position);
    
    // Get/set charge properties
    float getCharge() const { return m_charge; }
    void setCharge(float charge) { m_charge = charge; }
    
    // Check charge sign
    bool isPositivelyCharged() const { return m_charge > 0.0f; }
    bool isNegativelyCharged() const { return m_charge < 0.0f; }
    bool isNeutral() const { return m_charge == 0.0f; }
    
    // Get/set magnetic susceptibility (response to magnetic fields)
    float getMagneticSusceptibility() const { return m_magneticSusceptibility; }
    void setMagneticSusceptibility(float susceptibility) { m_magneticSusceptibility = susceptibility; }
    
    // Get/set plasma interaction factor
    float getPlasmaInteractionFactor() const { return m_plasmaInteractionFactor; }
    void setPlasmaInteractionFactor(float factor) { m_plasmaInteractionFactor = factor; }
    
    // Update physics with electromagnetic forces
    void update(float deltaTime, const Medium& medium) override;
    
    // Apply electromagnetic field effects
    void applyElectromagneticForce(const Vector2& electricField, const Vector2& magneticField);
    
    // Calculate Lorentz force (F = q(E + v × B))
    Vector2 calculateLorentzForce(const Vector2& electricField, const Vector2& magneticField) const;
    
private:
    float m_charge;     // Electric charge in Coulombs
    float m_magneticSusceptibility; // How strongly object responds to magnetic fields
    float m_plasmaInteractionFactor; // How strongly object interacts with plasma
};

} // namespace Archimedes