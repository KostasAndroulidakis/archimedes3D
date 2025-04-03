#include "World.h"
#include "../physics/PhysicsObject.h"
#include "../environment/Medium.h"
#include "../managers/ObjectManager.h"
#include "../managers/MediumManager.h"
#include "../managers/FieldManager.h"
#include "../managers/IonosphereManager.h"

namespace Archimedes {

World::World() {
    // Initialize managers
    m_objectManager = std::make_unique<ObjectManager>();
    m_mediumManager = std::make_unique<MediumManager>();
    m_fieldManager = std::make_unique<FieldManager>();
    m_ionosphereManager = std::make_unique<IonosphereManager>();
}

World::~World() = default;

// Manager accessors
ObjectManager* World::getObjectManager() const {
    return m_objectManager.get();
}

MediumManager* World::getMediumManager() const {
    return m_mediumManager.get();
}

FieldManager* World::getFieldManager() const {
    return m_fieldManager.get();
}

IonosphereManager* World::getIonosphereManager() const {
    return m_ionosphereManager.get();
}

float World::getDensityAtPosition(const Vector2& position) const {
    return m_mediumManager->getDensityAtPosition(position);
}

float World::getViscosityAtPosition(const Vector2& position) const {
    return m_mediumManager->getViscosityAtPosition(position);
}

float World::getPressureAtPosition(const Vector2& position) const {
    return m_mediumManager->getPressureAtPosition(position);
}

float World::getTemperatureAtPosition(const Vector2& position) const {
    return m_mediumManager->getTemperatureAtPosition(position);
}



Vector2 World::getElectricFieldAt(const Vector2& position) const {
    return m_fieldManager->getElectricFieldAt(position);
}

Vector2 World::getMagneticFieldAt(const Vector2& position) const {
    return m_fieldManager->getMagneticFieldAt(position);
}

Vector2 World::getPlasmaFieldAt(const Vector2& position) const {
    return m_fieldManager->getPlasmaFieldAt(position);
}

float World::getIonizationAt(const Vector2& position) const {
    return m_ionosphereManager->getIonizationAt(position);
}

void World::update(float deltaTime) {
    // Update all field systems first
    m_fieldManager->update(deltaTime);
    m_ionosphereManager->update(deltaTime);
    
    // Apply electromagnetic forces to objects
    const auto& objects = m_objectManager->getObjects();
    for (const auto& object : objects) {
        m_fieldManager->applyElectromagneticForces(object);
    }
    
    // Create a medium for each object based on its position and update
    for (const auto& object : objects) {
        Vector2 position = object->getPosition();
        
        // Create a local medium with properties from the object's position
        Medium localMedium(
            m_mediumManager->getDensityAtPosition(position),
            m_mediumManager->getViscosityAtPosition(position)
        );
        
        // Update the object with the local medium
        object->update(deltaTime, localMedium);
    }
}

} // namespace Archimedes