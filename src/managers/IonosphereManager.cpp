#include "IonosphereManager.h"
#include "../physics/PlasmaField.h" // Contains Ionosphere class

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
        return m_ionosphere->getIonizationAt(position);
    }
    return 0.0f; // No ionization by default
}

void IonosphereManager::generateLightningStrike(const Vector2& position) {
    if (m_usingIonosphere && m_ionosphere) {
        m_ionosphere->generateLightningStrike(position);
    }
}

void IonosphereManager::update(float deltaTime) {
    if (m_usingIonosphere && m_ionosphere) {
        m_ionosphere->update(deltaTime);
    }
}

} // namespace Archimedes