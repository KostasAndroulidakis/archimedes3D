#pragma once

#include "PhysicsObject.h"
#include "../environment/Medium.h"
namespace Archimedes {
// Forward declaration
class Pressure;
}

namespace Archimedes {

class CompressibleObject : public PhysicsObject {
public:
    CompressibleObject(float mass, float volume, float compressibility, const Vector2& position);
    
    // Get/set compressibility factor (0 = incompressible, 1 = fully compressible)
    float getCompressibility() const { return m_compressibility; }
    void setCompressibility(float compressibility) { m_compressibility = compressibility; }
    
    // Get reference (uncompressed) volume
    float getReferenceVolume() const { return m_referenceVolume; }
    
    // Apply pressure to object, changing its volume
    void applyPressure(float pressure);
    
    // Override update to handle pressure from medium
    void update(float deltaTime, const Medium& medium) override;
    
private:
    float m_compressibility;   // Compressibility factor between 0 and 1
    float m_referenceVolume;   // Original volume at standard pressure
    float m_currentPressure;   // Current pressure applied to the object (Pa)
};

} // namespace Archimedes