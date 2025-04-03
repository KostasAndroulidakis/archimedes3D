#pragma once

#include <memory>
#include "../math/Vector2.h"

namespace Archimedes {

// Forward declarations
class PhysicsObject;
class Medium;
class LayeredMedium;
class Ionosphere;
class ElectromagneticField;
class PlasmaField;
class ObjectManager;
class MediumManager;
class FieldManager;
class IonosphereManager;

/**
 * World class manages the simulation world and delegates specific responsibilities
 * to specialized manager classes. It provides a unified interface for interacting
 * with the physics simulation environment.
 */
class World {
public:
    World();
    ~World();
    
    // Manager accessors
    ObjectManager* getObjectManager() const;
    MediumManager* getMediumManager() const;
    FieldManager* getFieldManager() const;
    IonosphereManager* getIonosphereManager() const;
    
    // Convenience methods that delegate to manager classes
    void setMedium(const Medium& medium);
    void setLayeredMedium(std::shared_ptr<LayeredMedium> medium);
    void addObject(std::shared_ptr<PhysicsObject> object);
    
    // Query methods for world properties at a position
    float getDensityAtPosition(const Vector2& position) const;
    float getViscosityAtPosition(const Vector2& position) const;
    float getPressureAtPosition(const Vector2& position) const;
    float getTemperatureAtPosition(const Vector2& position) const;
    Vector2 getElectricFieldAt(const Vector2& position) const;
    Vector2 getMagneticFieldAt(const Vector2& position) const;
    Vector2 getPlasmaFieldAt(const Vector2& position) const;
    float getIonizationAt(const Vector2& position) const;
    
    // Update physics simulation
    void update(float deltaTime);
    
private:
    std::unique_ptr<ObjectManager> m_objectManager;
    std::unique_ptr<MediumManager> m_mediumManager;
    std::unique_ptr<FieldManager> m_fieldManager;
    std::unique_ptr<IonosphereManager> m_ionosphereManager;
};

} // namespace Archimedes