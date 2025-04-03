#include "LayeredMedium.h"
// stdexcept is not directly used
#include <algorithm>

namespace Archimedes {

LayeredMedium::LayeredMedium() 
    : Medium(1.2f) { // Default to standard air density
}

void LayeredMedium::addLayer(std::shared_ptr<AtmosphereLayer> layer) {
    // Insert the layer in sorted order by lower boundary
    auto pos = std::lower_bound(m_layers.begin(), m_layers.end(), layer,
        [](const std::shared_ptr<AtmosphereLayer>& a, const std::shared_ptr<AtmosphereLayer>& b) {
            return a->getLowerBoundary() < b->getLowerBoundary();
        });
    
    m_layers.insert(pos, layer);
}

std::shared_ptr<AtmosphereLayer> LayeredMedium::getLayerAtHeight(float height) const {
    if (m_layers.empty()) {
        return nullptr;
    }
    
    // Find the layer containing the height
    for (const auto& layer : m_layers) {
        if (layer->containsHeight(height)) {
            return layer;
        }
    }
    
    // If height is above the highest layer, return the top layer
    if (height >= m_layers.back()->getUpperBoundary()) {
        return m_layers.back();
    }
    
    // If height is below the lowest layer, return the bottom layer
    if (height < m_layers.front()->getLowerBoundary()) {
        return m_layers.front();
    }
    
    return nullptr;
}

float LayeredMedium::getDensityAtHeight(float height) const {
    auto layer = getLayerAtHeight(height);
    if (layer) {
        return layer->getDensityAtHeight(height);
    }
    return Medium::getDensity(); // Fallback to base density
}

float LayeredMedium::getPressureAtHeight(float height) const {
    auto layer = getLayerAtHeight(height);
    if (layer) {
        return layer->getPressureAtHeight(height);
    }
    return 101325.0f; // Standard atmospheric pressure as fallback
}

float LayeredMedium::getTemperatureAtHeight(float height) const {
    auto layer = getLayerAtHeight(height);
    if (layer) {
        return layer->getTemperatureAtHeight(height);
    }
    return 288.15f; // 15°C in Kelvin as fallback
}

float LayeredMedium::getViscosityAtHeight(float height) const {
    auto layer = getLayerAtHeight(height);
    if (layer) {
        return layer->getViscosityAtHeight(height);
    }
    return Medium::getViscosity(); // Fallback to base viscosity
}

} // namespace Archimedes