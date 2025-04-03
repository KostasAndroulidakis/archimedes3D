#include "ContainmentVessel.h"
#include "Pressure.h"
#include "CompressibleObject.h"
#include <algorithm>

namespace Archimedes {

ContainmentVessel::ContainmentVessel(float mass, float volume, float wallThickness, 
                                   float maxPressure, const Vector2& position)
    : PhysicsObject(mass, volume, position),
      m_wallThickness(wallThickness),
      m_maxPressure(maxPressure),
      m_internalPressure(Pressure::STANDARD_ATMOSPHERIC_PRESSURE),
      m_isRuptured(false),
      m_internalMedium(1.2f) { // Default to air inside
    
    // Calculate wall volume based on thickness
    // For simplicity, assume spherical vessel
    float radius = std::pow((3.0f * volume) / (4.0f * 3.14159f), 1.0f/3.0f);
    float innerRadius = radius - wallThickness;
    float innerVolume = (4.0f/3.0f) * 3.14159f * std::pow(innerRadius, 3.0f);
    m_wallVolume = volume - innerVolume;
}

void ContainmentVessel::setInternalMedium(const Medium& medium) {
    m_internalMedium = medium;
}

void ContainmentVessel::addObject(std::shared_ptr<PhysicsObject> object) {
    if (!containsObject(object)) {
        m_containedObjects.push_back(object);
    }
}

void ContainmentVessel::removeObject(std::shared_ptr<PhysicsObject> object) {
    m_containedObjects.erase(
        std::remove(m_containedObjects.begin(), m_containedObjects.end(), object),
        m_containedObjects.end()
    );
}

bool ContainmentVessel::containsObject(std::shared_ptr<PhysicsObject> object) const {
    return std::find(m_containedObjects.begin(), m_containedObjects.end(), object) != m_containedObjects.end();
}

void ContainmentVessel::setInternalPressure(float pressure) {
    m_internalPressure = pressure;
    
    // Check for rupture
    if (m_internalPressure > m_maxPressure) {
        m_isRuptured = true;
    }
}

void ContainmentVessel::calculatePressureEffects(const Medium& externalMedium) {
    // Get depth/height
    float depth = -getPosition().y;
    
    // Calculate external pressure
    float externalPressure = Pressure::STANDARD_ATMOSPHERIC_PRESSURE;
    if (depth > 0) {
        externalPressure += Pressure::calculateHydrostaticPressure(depth, externalMedium.getDensity());
    } else {
        // Simple atmospheric model
        float height = -depth;
        externalPressure *= std::exp(-height / 8000.0f);
    }
    
    // Calculate pressure difference
    float pressureDiff = m_internalPressure - externalPressure;
    
    // Force from pressure difference
    float surfaceArea = 4.0f * 3.14159f * std::pow(getVolume() * 0.75f / 3.14159f, 2.0f/3.0f);
    Vector2 pressureForce(0.0f, -pressureDiff * surfaceArea);
    
    // Apply force
    applyForce(pressureForce);
    
    // Check for rupture
    if (!m_isRuptured && std::abs(pressureDiff) > m_maxPressure) {
        m_isRuptured = true;
        // When ruptured, internal pressure equalizes with external
        m_internalPressure = externalPressure;
    }
    
    // If not ruptured, compression effects on the vessel itself
    if (!m_isRuptured) {
        // Volume change due to pressure difference
        // Using simplified linear model
        float volumeChangeFactor = 0.05f; // 5% max volume change
        float deformation = volumeChangeFactor * (externalPressure - m_internalPressure) / m_maxPressure;
        float newVolume = m_volume * (1.0f - deformation);
        
        // Ensure minimum volume
        newVolume = std::max(newVolume, m_volume * 0.9f);
        
        setVolume(newVolume);
    }
}

void ContainmentVessel::updateContainedObjects(float deltaTime) {
    if (m_isRuptured) {
        // No longer contains objects when ruptured
        m_containedObjects.clear();
        return;
    }
    
    // Create a local medium with internal pressure properties
    Medium internalEnvironment = m_internalMedium;
    
    // Update contained objects with internal medium and pressure
    for (auto& object : m_containedObjects) {
        // Apply pressure effects to compressible objects
        auto compressible = std::dynamic_pointer_cast<CompressibleObject>(object);
        if (compressible) {
            compressible->applyPressure(m_internalPressure);
        }
        
        // Update the object with the internal environment
        object->update(deltaTime, internalEnvironment);
        
        // Keep objects positioned relative to vessel
        Vector2 relativePos = object->getPosition() - m_position;
        object->setPosition(m_position + relativePos);
    }
}

void ContainmentVessel::update(float deltaTime, const Medium& externalMedium) {
    // Calculate pressure effects
    calculatePressureEffects(externalMedium);
    
    // Update contained objects
    updateContainedObjects(deltaTime);
    
    // Base physics update
    PhysicsObject::update(deltaTime, externalMedium);
}

} // namespace Archimedes