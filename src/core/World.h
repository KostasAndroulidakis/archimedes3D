#pragma once

#include <vector>
#include <memory>
#include "../physics/PhysicsObject.h"
#include "../physics/ElectromagneticField.h"
#include "../physics/PlasmaField.h"
#include "../environment/Medium.h"
#include "../environment/LayeredMedium.h"
#include "../math/Vector2.h"

namespace Archimedes {

class World {
public:
    World();
    
    // Add object to the world
    void addObject(std::shared_ptr<PhysicsObject> object);
    
    // Set a uniform medium
    void setMedium(const Medium& medium);
    
    // Set a layered medium (atmosphere)
    void setLayeredMedium(std::shared_ptr<LayeredMedium> medium);
    
    // Set electromagnetic field manager
    void setFieldManager(std::shared_ptr<FieldManager> fieldManager);
    
    // Set ionosphere
    void setIonosphere(std::shared_ptr<Ionosphere> ionosphere);
    
    // Get medium properties at a specific position
    float getDensityAtPosition(const Vector2& position) const;
    float getViscosityAtPosition(const Vector2& position) const;
    float getPressureAtPosition(const Vector2& position) const;
    float getTemperatureAtPosition(const Vector2& position) const;
    
    // Get electromagnetic field vectors at position
    Vector2 getElectricFieldAt(const Vector2& position) const;
    Vector2 getMagneticFieldAt(const Vector2& position) const;
    Vector2 getPlasmaFieldAt(const Vector2& position) const;
    
    // Get ionization level at position
    float getIonizationAt(const Vector2& position) const;
    
    // Generate lightning strike at position
    void generateLightningStrike(const Vector2& position);
    
    // Update physics simulation
    void update(float deltaTime);
    
    // Get all objects
    const std::vector<std::shared_ptr<PhysicsObject>>& getObjects() const { return m_objects; }
    
private:
    std::vector<std::shared_ptr<PhysicsObject>> m_objects;
    Medium m_uniformMedium;  // Basic medium for simple simulations
    std::shared_ptr<LayeredMedium> m_layeredMedium; // Advanced layered medium
    std::shared_ptr<FieldManager> m_fieldManager; // Electromagnetic fields
    std::shared_ptr<Ionosphere> m_ionosphere; // Ionosphere for plasma effects
    
    bool m_usingLayeredMedium;
    bool m_usingElectromagnetism;
    bool m_usingIonosphere;
    
    // Update object with electromagnetic forces
    void updateObjectElectromagnetism(std::shared_ptr<PhysicsObject> object);
};

} // namespace Archimedes