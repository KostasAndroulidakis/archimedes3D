#include "MediumManager.h"
#include "../utils/Constants.h"

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
        return m_layeredMedium->getDensityAtHeight(position.y);
    }
    return m_uniformMedium.getDensity();
}

float MediumManager::getViscosityAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getViscosityAtHeight(position.y);
    }
    return m_uniformMedium.getViscosity();
}

float MediumManager::getPressureAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getPressureAtHeight(position.y);
    }
    return Constants::Environment::Standard::ATMOSPHERIC_PRESSURE; // Default value
}

float MediumManager::getTemperatureAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getTemperatureAtHeight(position.y);
    }
    return Constants::Environment::Standard::STANDARD_TEMPERATURE; // Default value
}

} // namespace Archimedes