#include "FieldManager.h"
#include "../physics/PhysicsObject.h"
#include "../physics/ChargedObject.h"

namespace Archimedes {

FieldManager::FieldManager()
    : m_usingElectromagnetism(false),
      m_usingPlasma(false) {
}

Vector2 FieldManager::getElectricFieldAt(const Vector2& position) const {
    if (m_usingElectromagnetism && m_electromagneticField) {
        return m_electromagneticField->getElectricFieldAt(position);
    }
    return Vector2(0.0f, 0.0f);
}

Vector2 FieldManager::getMagneticFieldAt(const Vector2& position) const {
    if (m_usingElectromagnetism && m_electromagneticField) {
        return m_electromagneticField->getMagneticFieldAt(position);
    }
    return Vector2(0.0f, 0.0f);
}

Vector2 FieldManager::getPlasmaFieldAt(const Vector2& position) const {
    if (m_usingPlasma && m_plasmaField) {
        return m_plasmaField->getFieldAt(position);
    }
    return Vector2(0.0f, 0.0f);
}

void FieldManager::applyElectromagneticForces(std::shared_ptr<PhysicsObject> object) {
    if (!m_usingElectromagnetism || !m_electromagneticField) {
        return;
    }
    
    // Check if object is charged
    auto chargedObject = std::dynamic_pointer_cast<ChargedObject>(object);
    if (chargedObject) {
        // Get fields at object position
        Vector2 eField = getElectricFieldAt(object->getPosition());
        Vector2 mField = getMagneticFieldAt(object->getPosition());
        
        // Apply Lorentz force: F = q(E + v×B)
        float charge = chargedObject->getCharge();
        Vector2 velocity = object->getVelocity();
        
        // Calculate electric force: F_e = qE
        Vector2 electricForce = eField * charge;
        
        // In 2D, magnetic force is simplified
        // Calculate magnetic force: F_m = q(v×B)
        // For 2D, cross product becomes scalar
        float magneticForce = charge * velocity.x * mField.y - charge * velocity.y * mField.x;
        
        // Apply forces
        object->applyForce(electricForce);
        // Project magnetic force onto perpendicular direction to velocity
        Vector2 perpVelocity(-velocity.y, velocity.x);
        if (perpVelocity.magnitude() > 0) {
            perpVelocity = perpVelocity.normalized();
            object->applyForce(perpVelocity * magneticForce);
        }
    }
}

void FieldManager::setElectromagneticField(std::shared_ptr<ElectromagneticField> field) {
    m_electromagneticField = field;
    m_usingElectromagnetism = true;
}

void FieldManager::setPlasmaField(std::shared_ptr<PlasmaField> field) {
    m_plasmaField = field;
    m_usingPlasma = true;
}

} // namespace Archimedes