#include "World.h"
#include "../physics/PhysicsObject.h"
#include "../physics/ElectromagneticField.h"
#include "../physics/PlasmaField.h"
#include "../environment/Medium.h"
#include "../environment/LayeredMedium.h"
#include "../managers/ObjectManager.h"
#include "../managers/MediumManager.h"
#include "../managers/FieldManager.h"
#include "../managers/IonosphereManager.h"
#include <random>

namespace Archimedes {

World::World() {
    // Initialize managers
    m_objectManager = std::make_shared<ObjectManager>();
    m_mediumManager = std::make_shared<MediumManager>();
    m_fieldManager = std::make_shared<FieldManager>();
    m_ionosphereManager = std::make_shared<IonosphereManager>();
}

// Object management delegated to ObjectManager
void World::addObject(std::shared_ptr<PhysicsObject> object) {
    m_objectManager->addObject(object);
}

const std::vector<std::shared_ptr<PhysicsObject>>& World::getObjects() const {
    return m_objectManager->getObjects();
}

// Medium management delegated to MediumManager
void World::setMedium(const Medium& medium) {
    m_mediumManager->setMedium(medium);
}

void World::setLayeredMedium(std::shared_ptr<LayeredMedium> medium) {
    m_mediumManager->setLayeredMedium(medium);
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

// Field management delegated to FieldManager
void World::setElectromagneticField(std::shared_ptr<ElectromagneticField> field) {
    m_fieldManager->setElectromagneticField(field);
}

void World::setPlasmaField(std::shared_ptr<PlasmaField> field) {
    m_fieldManager->setPlasmaField(field);
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

// Ionosphere management delegated to IonosphereManager
void World::setIonosphere(std::shared_ptr<Ionosphere> ionosphere) {
    m_ionosphereManager->setIonosphere(ionosphere);
}

float World::getIonizationAt(const Vector2& position) const {
    return m_ionosphereManager->getIonizationAt(position);
}

void World::generateLightningStrike(const Vector2& position) {
    m_ionosphereManager->generateLightningStrike(position);
}

void World::update(float deltaTime) {
    // First update all specialized systems
    m_ionosphereManager->update(deltaTime);
    
    // Apply electromagnetic forces to objects
    for (const auto& object : m_objectManager->getObjects()) {
        m_fieldManager->applyElectromagneticForces(object);
    }
    
    // Now update physics for each object using the current medium
    for (const auto& object : m_objectManager->getObjects()) {
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