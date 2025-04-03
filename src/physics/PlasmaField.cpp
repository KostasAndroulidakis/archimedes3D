#include "PlasmaField.h"
#include <cmath>
#include <algorithm>
#include <random>

namespace Archimedes {

// PlasmaField implementation
PlasmaField::PlasmaField(float strength, const Vector2& center, float radius)
    : ElectromagneticField(FieldType::Plasma, strength),
      m_center(center),
      m_radius(radius),
      m_temperature(5000.0f),
      m_ionizationLevel(0.5f),
      m_dischargeType(DischargeType::Corona),
      m_timeAccumulator(0.0f),
      m_oscillationPhase(0.0f) {
}

Vector2 PlasmaField::getFieldVector(const Vector2& position) const {
    // Vector from center to position
    Vector2 toPosition = position - m_center;
    float distance = toPosition.magnitude();
    
    if (distance > m_radius) {
        // Outside plasma field influence
        return Vector2(0.0f, 0.0f);
    }
    
    // Calculate field strength decay with distance
    float normalizedDistance = distance / m_radius;
    float fieldStrength = m_strength * (1.0f - normalizedDistance * normalizedDistance);
    
    // Direction depends on discharge type
    Vector2 fieldDirection;
    
    switch (m_dischargeType) {
        case DischargeType::Corona:
            // Radial field (away from center)
            if (distance > 0.0001f) {
                fieldDirection = toPosition * (1.0f / distance);
            } else {
                fieldDirection = Vector2(0.0f, 1.0f); // Default up if at center
            }
            break;
            
        case DischargeType::Arc:
            // Oscillating field
            fieldDirection = Vector2(std::cos(m_oscillationPhase), std::sin(m_oscillationPhase));
            break;
            
        case DischargeType::Lightning:
            // Strong directional field (vertical for lightning)
            fieldDirection = Vector2(0.0f, 1.0f);
            break;
            
        case DischargeType::AuroraEffect:
            // Swirling field, depends on position
            float angle = std::atan2(toPosition.y, toPosition.x) + m_oscillationPhase;
            fieldDirection = Vector2(std::cos(angle), std::sin(angle));
            break;
    }
    
    // Return field vector (direction * strength)
    return fieldDirection * fieldStrength * m_ionizationLevel;
}

float PlasmaField::getFieldStrengthAt(const Vector2& position) const {
    float distance = (position - m_center).magnitude();
    
    if (distance > m_radius) {
        return 0.0f;
    }
    
    // Strength decreases quadratically with distance
    float normalizedDistance = distance / m_radius;
    return m_strength * (1.0f - normalizedDistance * normalizedDistance) * m_ionizationLevel;
}

float PlasmaField::getIonizationAt(const Vector2& position) const {
    float distance = (position - m_center).magnitude();
    
    if (distance > m_radius) {
        return 0.0f;
    }
    
    // Ionization decreases with distance
    float normalizedDistance = distance / m_radius;
    return m_ionizationLevel * (1.0f - normalizedDistance);
}

void PlasmaField::update(float deltaTime) {
    // Update time-based effects
    m_timeAccumulator += deltaTime;
    
    // Update oscillation phase
    float oscillationFrequency = 2.0f; // Hz
    m_oscillationPhase = std::fmod(m_timeAccumulator * oscillationFrequency * 6.28318f, 6.28318f);
    
    // Temperature fluctuation
    float tempFluctuation = std::sin(m_timeAccumulator * 0.5f) * 500.0f;
    m_temperature = 5000.0f + tempFluctuation;
    
    // Ionization level fluctuation
    float ionFluctuation = std::sin(m_timeAccumulator * 0.3f) * 0.1f;
    m_ionizationLevel = std::max(0.1f, std::min(0.9f, 0.5f + ionFluctuation));
}

std::shared_ptr<LightningField> PlasmaField::generateLightning(
    const Vector2& start, const Vector2& end, float strength, float duration) {
    // Create a new lightning field
    return std::make_shared<LightningField>(strength, start, end, duration);
}

// Ionosphere implementation
Ionosphere::Ionosphere(float baseHeight, float thickness)
    : m_baseHeight(baseHeight),
      m_thickness(thickness),
      m_ionDensity(1.0f),
      m_fieldStrength(5000.0f) {
}

bool Ionosphere::containsPosition(const Vector2& position) const {
    return position.y >= m_baseHeight && position.y <= (m_baseHeight + m_thickness);
}

Vector2 Ionosphere::getFieldVectorAt(const Vector2& position) const {
    if (!containsPosition(position)) {
        return Vector2(0.0f, 0.0f);
    }
    
    // Basic field is horizontal bands (like aurora)
    float heightFactor = (position.y - m_baseHeight) / m_thickness;
    float phaseShift = position.x * 0.001f;
    
    // Create undulating pattern
    float xComponent = std::sin(heightFactor * 10.0f + phaseShift) * m_fieldStrength;
    float yComponent = std::cos(heightFactor * 8.0f) * m_fieldStrength * 0.5f;
    
    // Add contributions from plasma fields
    Vector2 fieldVector(xComponent, yComponent);
    
    for (const auto& plasma : m_plasmaFields) {
        fieldVector += plasma->getFieldVector(position);
    }
    
    // Add contributions from lightning
    for (const auto& lightning : m_lightningFields) {
        if (lightning->isActive()) {
            fieldVector += lightning->getFieldVector(position);
        }
    }
    
    return fieldVector;
}

float Ionosphere::getIonizationAt(const Vector2& position) const {
    if (!containsPosition(position)) {
        return 0.0f;
    }
    
    // Base ionization decreases with height
    float heightFactor = (position.y - m_baseHeight) / m_thickness;
    float baseIonization = m_ionDensity * (1.0f - heightFactor * 0.5f);
    
    // Add contributions from plasma fields
    float totalIonization = baseIonization;
    
    for (const auto& plasma : m_plasmaFields) {
        totalIonization += plasma->getIonizationAt(position);
    }
    
    // Cap at 1.0
    return std::min(totalIonization, 1.0f);
}

std::shared_ptr<LightningField> Ionosphere::generateLightning(
    const Vector2& start, const Vector2& end, float strength) {
    
    // Create lightning with random duration between 0.2 and 1.5 seconds
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> durationDist(0.2f, 1.5f);
    
    float duration = durationDist(gen);
    auto lightning = std::make_shared<LightningField>(strength, start, end, duration);
    
    // Add to lightning collection
    m_lightningFields.push_back(lightning);
    
    return lightning;
}

void Ionosphere::addPlasmaField(std::shared_ptr<PlasmaField> plasma) {
    m_plasmaFields.push_back(plasma);
}

void Ionosphere::update(float deltaTime) {
    // Update all plasma fields
    for (auto& plasma : m_plasmaFields) {
        plasma->update(deltaTime);
    }
    
    // Update lightning
    updateLightning(deltaTime);
    
    // Clean up expired lightning
    cleanupExpiredLightning();
}

void Ionosphere::updateLightning(float deltaTime) {
    for (auto& lightning : m_lightningFields) {
        if (lightning->isActive()) {
            // Update lightning
            lightning->update(deltaTime);
        }
    }
}

void Ionosphere::cleanupExpiredLightning() {
    m_lightningFields.erase(
        std::remove_if(m_lightningFields.begin(), m_lightningFields.end(),
            [](const std::shared_ptr<LightningField>& lightning) {
                return !lightning->isActive();
            }
        ),
        m_lightningFields.end()
    );
}

} // namespace Archimedes