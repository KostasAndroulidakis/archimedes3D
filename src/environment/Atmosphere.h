#pragma once

#include "LayeredMedium.h"
#include <string>

namespace Archimedes {

// Factory class for creating a standard atmosphere model
class Atmosphere {
public:
    // Create a standard atmosphere with all layers
    static std::shared_ptr<LayeredMedium> createStandardModel();
    
    // Create specific atmospheric regions
    static std::shared_ptr<AtmosphereLayer> createTroposphere();
    static std::shared_ptr<AtmosphereLayer> createStratosphere();
    static std::shared_ptr<AtmosphereLayer> createMesosphere();
    static std::shared_ptr<AtmosphereLayer> createThermosphere();
    static std::shared_ptr<AtmosphereLayer> createExosphere();
    
    // Create an electrified layer (ionosphere)
    static std::shared_ptr<AtmosphereLayer> createIonosphere();
    
    // Create a dome layer (firmament)
    static std::shared_ptr<AtmosphereLayer> createFirmament();
    
    // Generic method to create atmospheric layer from constants namespace
    template<typename T>
    static std::shared_ptr<AtmosphereLayer> createLayerFromConstants(const std::string& name) {
        return std::make_shared<AtmosphereLayer>(
            name,
            T::DENSITY,
            T::TEMPERATURE,
            T::LOWER_BOUNDARY,
            T::UPPER_BOUNDARY,
            T::PRESSURE
        );
    }
};

} // namespace Archimedes