#include "FieldManager.h"
#include "../physics/PhysicsObject.h"
#include "../physics/ChargedObject.h"
#include "../physics/ElectromagneticField.h"
#include "../physics/PlasmaField.h"

namespace Archimedes {

FieldManager::FieldManager()
    : m_usingElectromagnetism(false),
      m_usingPlasma(false) {
}

void FieldManager::addField(std::shared_ptr<ElectromagneticField> field) {
    m_electricFields.push_back(field);
    m_usingElectromagnetism = true;
}

Vector2 FieldManager::getElectricFieldAt(const Vector2& position) const {
    return getNetFieldVector(position, FieldType::Electric);
}

Vector2 FieldManager::getMagneticFieldAt(const Vector2& position) const {
    return getNetFieldVector(position, FieldType::Magnetic);
}

Vector2 FieldManager::getPlasmaFieldAt(const Vector2& position) const {
    if (m_usingPlasma && m_plasmaField) {
        return m_plasmaField->getFieldVector(position);
    }
    return Vector2(0.0f, 0.0f);
}

Vector2 FieldManager::getNetFieldVector(const Vector2& position, FieldType type) const {
    Vector2 netField(0.0f, 0.0f);
    
    // Sum contributions from all electromagnetic fields
    if (m_usingElectromagnetism) {
        for (const auto& field : m_electricFields) {
            switch (type) {
                case FieldType::Electric:
                    netField += field->getElectricFieldAt(position);
                    break;
                case FieldType::Magnetic:
                    netField += field->getMagneticFieldAt(position);
                    break;
                default:
                    break;
            }
        }
    }
    
    return netField;
}

void FieldManager::applyElectromagneticForces(std::shared_ptr<PhysicsObject> object) {
    if (!m_usingElectromagnetism) {
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
    m_electricFields.clear();
    m_electricFields.push_back(field);
    m_usingElectromagnetism = true;
}

void FieldManager::setPlasmaField(std::shared_ptr<PlasmaField> field) {
    m_plasmaField = field;
    m_usingPlasma = true;
}

void FieldManager::update(float deltaTime) {
    // Update all electromagnetic fields
    if (m_usingElectromagnetism) {
        for (auto& field : m_electricFields) {
            field->update(deltaTime);
        }
    }
    
    // Update plasma field
    if (m_usingPlasma && m_plasmaField) {
        m_plasmaField->update(deltaTime);
    }
}

void FieldManager::copyFrom(const FieldManager& other) {
    // Copy electromagnetic fields
    m_electricFields.clear();
    for (const auto& field : other.m_electricFields) {
        m_electricFields.push_back(field);
    }
    
    // Copy plasma field
    m_plasmaField = other.m_plasmaField;
    
    // Copy flags
    m_usingElectromagnetism = other.m_usingElectromagnetism;
    m_usingPlasma = other.m_usingPlasma;
}

} // namespace Archimedes