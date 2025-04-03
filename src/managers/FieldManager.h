#pragma once

#include <memory>
#include <vector>
#include "../math/Vector2.h"
#include "../physics/FieldTypes.h"

namespace Archimedes {

// Forward declarations
class PhysicsObject;
class ElectromagneticField;
class PlasmaField;

class FieldManager {
public:
    FieldManager();
    
    // Add a field to the manager
    void addField(std::shared_ptr<ElectromagneticField> field);
    
    // Get electromagnetic field vectors at position
    Vector2 getElectricFieldAt(const Vector2& position) const;
    Vector2 getMagneticFieldAt(const Vector2& position) const;
    Vector2 getPlasmaFieldAt(const Vector2& position) const;
    
    // Get net field vector at position (for any field type)
    Vector2 getNetFieldVector(const Vector2& position, FieldType type) const;
    
    // Apply electromagnetic forces to an object
    void applyElectromagneticForces(std::shared_ptr<PhysicsObject> object);
    
    // Set fields explicitly
    void setElectromagneticField(std::shared_ptr<ElectromagneticField> field);
    void setPlasmaField(std::shared_ptr<PlasmaField> field);
    
    // Update fields
    void update(float deltaTime);
    
private:
    std::vector<std::shared_ptr<ElectromagneticField>> m_electricFields;
    std::shared_ptr<PlasmaField> m_plasmaField;
    bool m_usingElectromagnetism;
    bool m_usingPlasma;
};

} // namespace Archimedes