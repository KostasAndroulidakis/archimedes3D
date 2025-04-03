#pragma once

#include "PhysicsObject.h"
#include "../environment/Medium.h"
#include <memory>
#include <vector>

namespace Archimedes {

class ContainmentVessel : public PhysicsObject {
public:
    ContainmentVessel(float mass, float volume, float wallThickness, 
                     float maxPressure, const Vector2& position);
    
    // Get vessel properties
    float getWallThickness() const { return m_wallThickness; }
    float getInternalVolume() const { return m_volume - m_wallVolume; }
    float getMaxPressure() const { return m_maxPressure; }
    float getInternalPressure() const { return m_internalPressure; }
    Medium getInternalMedium() const { return m_internalMedium; }
    
    // Check if vessel is ruptured
    bool isRuptured() const { return m_isRuptured; }
    
    // Set internal medium
    void setInternalMedium(const Medium& medium);
    
    // Add object to the vessel
    void addObject(std::shared_ptr<PhysicsObject> object);
    
    // Remove object from the vessel
    void removeObject(std::shared_ptr<PhysicsObject> object);
    
    // Check if an object is inside the vessel
    bool containsObject(std::shared_ptr<PhysicsObject> object) const;
    
    // Update physics for vessel and contained objects
    void update(float deltaTime, const Medium& externalMedium) override;
    
    // Set internal pressure directly
    void setInternalPressure(float pressure);
    
private:
    float m_wallThickness;       // Thickness of vessel walls (m)
    float m_wallVolume;          // Volume of vessel walls (m³)
    float m_maxPressure;         // Max pressure before rupture (Pa)
    float m_internalPressure;    // Current internal pressure (Pa)
    bool m_isRuptured;           // Whether vessel has ruptured
    Medium m_internalMedium;     // Medium inside the vessel
    
    std::vector<std::shared_ptr<PhysicsObject>> m_containedObjects;
    
    // Calculate pressure effects on vessel
    void calculatePressureEffects(const Medium& externalMedium);
    
    // Update contained objects with internal medium
    void updateContainedObjects(float deltaTime);
};

} // namespace Archimedes