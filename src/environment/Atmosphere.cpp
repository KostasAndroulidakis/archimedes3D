#include "Atmosphere.h"
#include "../utils/Constants.h"

namespace Archimedes {

std::shared_ptr<LayeredMedium> Atmosphere::createStandardModel() {
    auto atmosphere = std::make_shared<LayeredMedium>();
    
    // Add all layers from bottom to top
    atmosphere->addLayer(createTroposphere());
    atmosphere->addLayer(createStratosphere());
    atmosphere->addLayer(createMesosphere());
    atmosphere->addLayer(createThermosphere());
    atmosphere->addLayer(createExosphere());
    atmosphere->addLayer(createFirmament());
    
    return atmosphere;
}

std::shared_ptr<AtmosphereLayer> Atmosphere::createTroposphere() {
    // Troposphere: 0-12km, where weather occurs
    return std::make_shared<AtmosphereLayer>(
        "Troposphere",
        Constants::Environment::Atmosphere::Troposphere::DENSITY,
        Constants::Environment::Atmosphere::Troposphere::TEMPERATURE,
        Constants::Environment::Atmosphere::Troposphere::LOWER_BOUNDARY,
        Constants::Environment::Atmosphere::Troposphere::UPPER_BOUNDARY,
        Constants::Environment::Atmosphere::Troposphere::PRESSURE
    );
}

std::shared_ptr<AtmosphereLayer> Atmosphere::createStratosphere() {
    // Stratosphere: 12-50km, contains ozone layer
    return std::make_shared<AtmosphereLayer>(
        "Stratosphere",
        Constants::Environment::Atmosphere::Stratosphere::DENSITY,
        Constants::Environment::Atmosphere::Stratosphere::TEMPERATURE,
        Constants::Environment::Atmosphere::Stratosphere::LOWER_BOUNDARY,
        Constants::Environment::Atmosphere::Stratosphere::UPPER_BOUNDARY,
        Constants::Environment::Atmosphere::Stratosphere::PRESSURE
    );
}

std::shared_ptr<AtmosphereLayer> Atmosphere::createMesosphere() {
    // Mesosphere: 50-85km, where meteors burn up
    return std::make_shared<AtmosphereLayer>(
        "Mesosphere",
        Constants::Environment::Atmosphere::Mesosphere::DENSITY,
        Constants::Environment::Atmosphere::Mesosphere::TEMPERATURE,
        Constants::Environment::Atmosphere::Mesosphere::LOWER_BOUNDARY,
        Constants::Environment::Atmosphere::Mesosphere::UPPER_BOUNDARY,
        Constants::Environment::Atmosphere::Mesosphere::PRESSURE
    );
}

std::shared_ptr<AtmosphereLayer> Atmosphere::createThermosphere() {
    // Thermosphere: 85-600km, where aurora occurs
    return std::make_shared<AtmosphereLayer>(
        "Thermosphere",
        Constants::Environment::Atmosphere::Thermosphere::DENSITY,
        Constants::Environment::Atmosphere::Thermosphere::TEMPERATURE,
        Constants::Environment::Atmosphere::Thermosphere::LOWER_BOUNDARY,
        Constants::Environment::Atmosphere::Thermosphere::UPPER_BOUNDARY,
        Constants::Environment::Atmosphere::Thermosphere::PRESSURE
    );
}

std::shared_ptr<AtmosphereLayer> Atmosphere::createExosphere() {
    // Exosphere: 600-10,000km, transitioning to vacuum
    return std::make_shared<AtmosphereLayer>(
        "Exosphere",
        Constants::Environment::Atmosphere::Exosphere::DENSITY,
        Constants::Environment::Atmosphere::Exosphere::TEMPERATURE,
        Constants::Environment::Atmosphere::Exosphere::LOWER_BOUNDARY,
        Constants::Environment::Atmosphere::Exosphere::UPPER_BOUNDARY,
        Constants::Environment::Atmosphere::Exosphere::PRESSURE
    );
}

std::shared_ptr<AtmosphereLayer> Atmosphere::createIonosphere() {
    // Ionosphere: 60-1000km, electrically charged layer (overlaps other layers)
    return std::make_shared<AtmosphereLayer>(
        "Ionosphere",
        Constants::Environment::Atmosphere::Ionosphere::DENSITY,
        Constants::Environment::Atmosphere::Ionosphere::TEMPERATURE,
        Constants::Environment::Atmosphere::Ionosphere::LOWER_BOUNDARY,
        Constants::Environment::Atmosphere::Ionosphere::UPPER_BOUNDARY,
        Constants::Environment::Atmosphere::Ionosphere::PRESSURE
    );
}

std::shared_ptr<AtmosphereLayer> Atmosphere::createFirmament() {
    // Firmament: The dome above
    return std::make_shared<AtmosphereLayer>(
        "Firmament",
        Constants::Environment::Atmosphere::Firmament::DENSITY,
        Constants::Environment::Atmosphere::Firmament::TEMPERATURE,
        Constants::Environment::Atmosphere::Firmament::LOWER_BOUNDARY,
        Constants::Environment::Atmosphere::Firmament::UPPER_BOUNDARY,
        Constants::Environment::Atmosphere::Firmament::PRESSURE
    );
}

} // namespace Archimedes