#include "IonosphereManager.h"
#include "../physics/Ionosphere.h"

namespace Archimedes {

IonosphereManager::IonosphereManager()
    : m_usingIonosphere(false) {
}

void IonosphereManager::setIonosphere(std::shared_ptr<Ionosphere> ionosphere) {
    m_ionosphere = ionosphere;
    m_usingIonosphere = true;
}

float IonosphereManager::getIonizationAt(const Vector2& position) const {
    if (m_usingIonosphere && m_ionosphere) {
        // Use height to get ionization level
        return m_ionosphere->getIonizationLevel(position.y);
    }
    return 0.0f; // No ionization by default
}

void IonosphereManager::generateLightningStrike(const Vector2& position) {
    // This would need to be implemented in a real system
    // For now, we just check if the ionosphere exists
    if (m_usingIonosphere && m_ionosphere) {
        // In a full implementation, we would generate a lightning strike here
    }
}

void IonosphereManager::update(float deltaTime) {
    if (m_usingIonosphere && m_ionosphere) {
        m_ionosphere->update(deltaTime);
    }
}

} // namespace Archimedes