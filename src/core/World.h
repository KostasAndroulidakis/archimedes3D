#pragma once

#include <memory>
#include "../math/Vector2.h"
#include "../managers/ObjectManager.h"
#include "../managers/MediumManager.h"
#include "../managers/FieldManager.h"
#include "../managers/IonosphereManager.h"

namespace Archimedes {

// Forward declarations
class PhysicsObject;
class Medium;
class LayeredMedium;
class Ionosphere;
class ElectromagneticField;
class PlasmaField;

class World {
public:
    World();
    
    // Object management
    void addObject(std::shared_ptr<PhysicsObject> object);
    const std::vector<std::shared_ptr<PhysicsObject>>& getObjects() const;
    
    // Medium management
    void setMedium(const Medium& medium);
    void setLayeredMedium(std::shared_ptr<LayeredMedium> medium);
    float getDensityAtPosition(const Vector2& position) const;
    float getViscosityAtPosition(const Vector2& position) const;
    float getPressureAtPosition(const Vector2& position) const;
    float getTemperatureAtPosition(const Vector2& position) const;
    
    // Field management
    void setElectromagneticField(std::shared_ptr<ElectromagneticField> field);
    void setPlasmaField(std::shared_ptr<PlasmaField> field);
    Vector2 getElectricFieldAt(const Vector2& position) const;
    Vector2 getMagneticFieldAt(const Vector2& position) const;
    Vector2 getPlasmaFieldAt(const Vector2& position) const;
    
    // Ionosphere management
    void setIonosphere(std::shared_ptr<Ionosphere> ionosphere);
    float getIonizationAt(const Vector2& position) const;
    void generateLightningStrike(const Vector2& position);
    
    // Update physics simulation
    void update(float deltaTime);
    
private:
    std::shared_ptr<ObjectManager> m_objectManager;
    std::shared_ptr<MediumManager> m_mediumManager;
    std::shared_ptr<FieldManager> m_fieldManager;
    std::shared_ptr<IonosphereManager> m_ionosphereManager;
};

} // namespace Archimedes