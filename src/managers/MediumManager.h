#pragma once

#include <memory>
#include "../environment/Medium.h"
#include "../environment/LayeredMedium.h"
#include "../math/Vector2.h"

namespace Archimedes {

class MediumManager {
public:
    MediumManager();
    
    // Set a uniform medium
    void setMedium(const Medium& medium);
    
    // Set a layered medium (atmosphere)
    void setLayeredMedium(std::shared_ptr<LayeredMedium> medium);
    
    // Get current medium (for simple environments)
    const Medium& getMedium() const { return m_uniformMedium; }
    
    // Get medium properties at a specific position
    float getDensityAtPosition(const Vector2& position) const;
    float getViscosityAtPosition(const Vector2& position) const;
    float getPressureAtPosition(const Vector2& position) const;
    float getTemperatureAtPosition(const Vector2& position) const;

private:
    Medium m_uniformMedium;  // Basic medium for simple simulations
    std::shared_ptr<LayeredMedium> m_layeredMedium; // Advanced layered medium
    bool m_usingLayeredMedium;
};

} // namespace Archimedes