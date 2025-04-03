#pragma once

#include <memory>
#include "../math/Vector2.h"
#include "../physics/ElectromagneticField.h"
#include "../physics/PlasmaField.h"

namespace Archimedes {

class FieldManager {
public:
    FieldManager();
    
    // Get electromagnetic field vectors at position
    Vector2 getElectricFieldAt(const Vector2& position) const;
    Vector2 getMagneticFieldAt(const Vector2& position) const;
    Vector2 getPlasmaFieldAt(const Vector2& position) const;
    
    // Apply electromagnetic forces to an object
    void applyElectromagneticForces(std::shared_ptr<PhysicsObject> object);
    
    // Set fields
    void setElectromagneticField(std::shared_ptr<ElectromagneticField> field);
    void setPlasmaField(std::shared_ptr<PlasmaField> field);
    
private:
    std::shared_ptr<ElectromagneticField> m_electromagneticField;
    std::shared_ptr<PlasmaField> m_plasmaField;
    bool m_usingElectromagnetism;
    bool m_usingPlasma;
};

} // namespace Archimedes