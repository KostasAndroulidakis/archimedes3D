#pragma once

#include "Medium.h"
#include "AtmosphereLayer.h"
#include <vector>
#include <memory>

namespace Archimedes {

class LayeredMedium : public Medium {
public:
    // Create an empty layered medium
    LayeredMedium();
    
    // Add a layer to the medium
    void addLayer(std::shared_ptr<AtmosphereLayer> layer);
    
    // Get properties at a specific height
    float getDensityAtHeight(float height) const;
    float getPressureAtHeight(float height) const;
    float getTemperatureAtHeight(float height) const;
    float getViscosityAtHeight(float height) const;
    
    // Get the layer at a specific height
    std::shared_ptr<AtmosphereLayer> getLayerAtHeight(float height) const;
    
    // Override base class methods
    float getDensity() const override { return getDensityAtHeight(0.0f); }
    float getViscosity() const override { return getViscosityAtHeight(0.0f); }
    
    // Get all layers
    const std::vector<std::shared_ptr<AtmosphereLayer>>& getLayers() const { return m_layers; }

private:
    std::vector<std::shared_ptr<AtmosphereLayer>> m_layers;
};

} // namespace Archimedes