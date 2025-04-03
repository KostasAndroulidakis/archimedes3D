#include "World.h"
#include "../physics/ChargedObject.h"
#include "../environment/Electromagnetism.h"
#include "../utils/Constants.h"
#include <random>

namespace Archimedes {

World::World() 
    : m_uniformMedium(Constants::Environment::Standard::AIR_DENSITY),  // Default medium is air
      m_usingLayeredMedium(false),
      m_usingElectromagnetism(false),
      m_usingIonosphere(false) {
}

void World::addObject(std::shared_ptr<PhysicsObject> object) {
    m_objects.push_back(object);
}

void World::setMedium(const Medium& medium) {
    m_uniformMedium = medium;
    m_usingLayeredMedium = false;
}

void World::setLayeredMedium(std::shared_ptr<LayeredMedium> medium) {
    m_layeredMedium = medium;
    m_usingLayeredMedium = true;
}

void World::setFieldManager(std::shared_ptr<FieldManager> fieldManager) {
    m_fieldManager = fieldManager;
    m_usingElectromagnetism = true;
}

void World::setIonosphere(std::shared_ptr<Ionosphere> ionosphere) {
    m_ionosphere = ionosphere;
    m_usingIonosphere = true;
}

float World::getDensityAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getDensityAtHeight(position.y);
    }
    return m_uniformMedium.getDensity();
}

float World::getViscosityAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getViscosityAtHeight(position.y);
    }
    return m_uniformMedium.getViscosity();
}

float World::getPressureAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getPressureAtHeight(position.y);
    }
    return Constants::Environment::Standard::ATMOSPHERIC_PRESSURE;
}

float World::getTemperatureAtPosition(const Vector2& position) const {
    if (m_usingLayeredMedium && m_layeredMedium) {
        return m_layeredMedium->getTemperatureAtHeight(position.y);
    }
    return Constants::Environment::Standard::STANDARD_TEMPERATURE;
}

Vector2 World::getElectricFieldAt(const Vector2& position) const {
    if (m_usingElectromagnetism && m_fieldManager) {
        return m_fieldManager->getNetFieldVector(position, FieldType::Electric);
    }
    return Vector2(0.0f, 0.0f);
}

Vector2 World::getMagneticFieldAt(const Vector2& position) const {
    if (m_usingElectromagnetism && m_fieldManager) {
        return m_fieldManager->getNetFieldVector(position, FieldType::Magnetic);
    }
    return Vector2(0.0f, 0.0f);
}

Vector2 World::getPlasmaFieldAt(const Vector2& position) const {
    if (m_usingElectromagnetism && m_fieldManager) {
        return m_fieldManager->getNetFieldVector(position, FieldType::Plasma);
    }
    return Vector2(0.0f, 0.0f);
}

float World::getIonizationAt(const Vector2& position) const {
    if (m_usingIonosphere && m_ionosphere) {
        return m_ionosphere->getIonizationAt(position);
    }
    return 0.0f;
}

void World::generateLightningStrike(const Vector2& position) {
    if (m_usingElectromagnetism && m_fieldManager) {
        // Generate lightning strike
        auto lightning = Electromagnetism::createLightningStrike(position);
        m_fieldManager->addField(lightning);
    }
}

void World::updateObjectElectromagnetism(std::shared_ptr<PhysicsObject> object) {
    auto charged = std::dynamic_pointer_cast<ChargedObject>(object);
    if (!charged) {
        return;
    }
    
    Vector2 position = charged->getPosition();
    
    // Get field vectors at object position
    Vector2 electricField = getElectricFieldAt(position);
    Vector2 magneticField = getMagneticFieldAt(position);
    
    // Apply fields to charged object
    charged->applyElectromagneticForce(electricField, magneticField);
    
    // Apply plasma effects (if ionosphere present)
    if (m_usingIonosphere && m_ionosphere) {
        if (m_ionosphere->containsPosition(position)) {
            Vector2 plasmaField = getPlasmaFieldAt(position);
            float ionization = getIonizationAt(position);
            
            // Add plasma field effects (simple additional force)
            charged->applyElectromagneticForce(plasmaField * ionization, Vector2(0.0f, 0.0f));
        }
    }
}

void World::update(float deltaTime) {
    // Update electromagnetic fields
    if (m_usingElectromagnetism && m_fieldManager) {
        m_fieldManager->update(deltaTime);
    }
    
    // Update ionosphere
    if (m_usingIonosphere && m_ionosphere) {
        m_ionosphere->update(deltaTime);
    }
    
    // Apply electromagnetic forces first
    if (m_usingElectromagnetism) {
        for (auto& object : m_objects) {
            updateObjectElectromagnetism(object);
        }
    }
    
    // Update all physics objects with medium forces
    for (auto& object : m_objects) {
        Vector2 position = object->getPosition();
        
        if (m_usingLayeredMedium && m_layeredMedium) {
            // Create a local medium with properties from the object's position
            Medium localMedium(
                getDensityAtPosition(position),
                getViscosityAtPosition(position)
            );
            object->update(deltaTime, localMedium);
        } else {
            object->update(deltaTime, m_uniformMedium);
        }
    }
    
    // Random lightning generation
    if (m_usingElectromagnetism && m_usingIonosphere) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> chance(0.0f, 1.0f);
        std::uniform_real_distribution<float> posX(
            Constants::Environment::Lightning::MIN_POSITION_X,
            Constants::Environment::Lightning::MAX_POSITION_X
        );
        
        if (chance(gen) < Constants::Environment::Lightning::GENERATION_PROBABILITY) {
            Vector2 strikePos(posX(gen), 0.0f);  // Random X, at ground level
            generateLightningStrike(strikePos);
        }
    }
}

} // namespace Archimedes