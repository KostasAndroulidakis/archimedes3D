#pragma once

#include <memory>
#include "../math/Vector2.h"
#include "../physics/Ionosphere.h"

namespace Archimedes {

// Ionosphere class already included

class IonosphereManager {
public:
    IonosphereManager();
    
    // Set ionosphere
    void setIonosphere(std::shared_ptr<Ionosphere> ionosphere);
    
    // Get ionization level at position
    float getIonizationAt(const Vector2& position) const;
    
    // Generate lightning strike at position
    void generateLightningStrike(const Vector2& position);
    
    // Update the ionosphere state
    void update(float deltaTime);
    
private:
    std::shared_ptr<Ionosphere> m_ionosphere;
    bool m_usingIonosphere;
};

} // namespace Archimedes