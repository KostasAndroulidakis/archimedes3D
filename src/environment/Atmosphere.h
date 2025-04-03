#pragma once

#include "LayeredMedium.h"

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
};

} // namespace Archimedes