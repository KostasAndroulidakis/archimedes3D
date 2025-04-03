#pragma once
#include "../utils/Constants.h"

namespace Archimedes {

class Medium {
public:
    Medium(float density, float viscosity = Constants::Environment::Standard::AIR_VISCOSITY)
        : m_density(density), m_viscosity(viscosity) {}
    
    // Get medium density (kg/m³)
    virtual float getDensity() const { return m_density; }
    
    // Get medium viscosity (resistance to flow)
    virtual float getViscosity() const { return m_viscosity; }
    
    // Virtual destructor for proper inheritance
    virtual ~Medium() = default;
    
private:
    float m_density;    // Density of the medium (kg/m³)
    float m_viscosity;  // Viscosity of the medium
};

} // namespace Archimedes