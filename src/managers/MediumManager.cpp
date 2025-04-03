#include "MediumManager.h"

namespace Archimedes {

MediumManager::MediumManager() 
    : m_uniformMedium(Constants::Environment::Standard::AIR_DENSITY),
      m_usingLayeredMedium(false) {
}

void MediumManager::setMedium(const Medium& medium) {
    m_uniformMedium = medium;
    m_usingLayeredMedium = false;
}

void MediumManager::setLayeredMedium(std::shared_ptr<LayeredMedium> medium) {
    m_layeredMedium = medium;
    m_usingLayeredMedium = true;
}

float MediumManager::getDensityAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getDensityAtPosition(position);
    }
    return m_uniformMedium.getDensity();
}

float MediumManager::getViscosityAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getViscosityAtPosition(position);
    }
    return m_uniformMedium.getViscosity();
}

float MediumManager::getPressureAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getPressureAtPosition(position);
    }
    return Constants::Environment::Standard::ATMOSPHERIC_PRESSURE; // Default value
}

float MediumManager::getTemperatureAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getTemperatureAtPosition(position);
    }
    return Constants::Environment::Standard::STANDARD_TEMPERATURE; // Default value
}

} // namespace Archimedes