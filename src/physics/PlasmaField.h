#pragma once

#include "../math/Vector2.h"
#include <cstdlib> // For rand() function

// Forward declarations for constants
namespace Archimedes {
namespace Constants {
namespace Physics {
// Forward declarations if needed
}
}
}

namespace Archimedes {

// Types of plasma discharges
enum class DischargeType {
    LightningBolt,
    AuroraEffect,
    SolarFlare,
    PlasmaSheet
};

class PlasmaField {
public:
    PlasmaField(float strength, const Vector2& position, float radius = 1000.0f)
        : m_strength(strength), m_position(position), m_radius(radius),
          m_dischargeType(DischargeType::AuroraEffect), m_ionizationLevel(0.5f),
          m_temperature(5000.0f), m_active(true), m_elapsedTime(0.0f),
          m_duration(-1.0f) {} // -1 for indefinite duration
    
    // Set field properties
    void setStrength(float strength) { m_strength = strength; }
    void setPosition(const Vector2& position) { m_position = position; }
    void setRadius(float radius) { m_radius = radius; }
    void setDischargeType(DischargeType type) { m_dischargeType = type; }
    void setIonizationLevel(float level) { m_ionizationLevel = level; }
    void setTemperature(float temp) { m_temperature = temp; }
    void setDuration(float duration) { m_duration = duration; }
    
    // Get field properties
    float getStrength() const { return m_strength; }
    Vector2 getPosition() const { return m_position; }
    float getRadius() const { return m_radius; }
    DischargeType getDischargeType() const { return m_dischargeType; }
    float getIonizationLevel() const { return m_ionizationLevel; }
    float getTemperature() const { return m_temperature; }
    bool isActive() const { return m_active; }
    
    // Calculate field vector at position
    Vector2 getFieldVector(const Vector2& position) const {
        if (!m_active) {
            return Vector2(0.0f, 0.0f);
        }
        
        // Distance from field center
        Vector2 direction = position - m_position;
        float distance = direction.magnitude();
        
        // If outside radius, no effect
        if (distance > m_radius) {
            return Vector2(0.0f, 0.0f);
        }
        
        // Normalize direction and scale by strength and distance
        if (distance > 0.001f) {
            direction = direction * (1.0f / distance);
        } else {
            return Vector2(0.0f, 0.0f); // At exact center, no direction
        }
        
        // Field strength falls off with distance
        float normalizedDistance = distance / m_radius;
        float strengthFactor = m_strength * (1.0f - normalizedDistance);
        
        // Different discharge types have different field patterns
        switch (m_dischargeType) {
            case DischargeType::LightningBolt:
                // Lightning fields are strongly directional (vertical)
                return Vector2(0.0f, -1.0f) * strengthFactor;
                
            case DischargeType::AuroraEffect:
                // Aurora fields have swirling patterns
                return Vector2(-direction.y, direction.x) * strengthFactor;
                
            case DischargeType::SolarFlare:
                // Solar flares explode outward
                return direction * strengthFactor;
                
            case DischargeType::PlasmaSheet:
                // Plasma sheets flow horizontally
                return Vector2(1.0f, 0.0f) * strengthFactor;
                
            default:
                return direction * strengthFactor;
        }
    }
    
    // Update the field
    void update(float deltaTime) {
        // If has limited duration, check if expired
        if (m_duration > 0.0f) {
            m_elapsedTime += deltaTime;
            if (m_elapsedTime >= m_duration) {
                m_active = false;
            }
        }
        
        // Different update behavior based on discharge type
        switch (m_dischargeType) {
            case DischargeType::LightningBolt:
                // Lightning bolts decay rapidly
                m_strength *= 0.9f;
                if (m_strength < 0.1f) {
                    m_active = false;
                }
                break;
                
            case DischargeType::AuroraEffect:
                // Auroras slowly fluctuate
                m_strength = m_strength * 0.99f + m_strength * 0.02f * (rand() / (float)RAND_MAX);
                break;
                
            case DischargeType::SolarFlare:
                // Solar flares expand
                m_radius += 10.0f * deltaTime;
                m_strength -= 0.1f * deltaTime;
                if (m_strength <= 0.0f) {
                    m_active = false;
                }
                break;
                
            case DischargeType::PlasmaSheet:
                // Plasma sheets move
                m_position = m_position + Vector2(10.0f * deltaTime, 0.0f);
                break;
        }
    }
    
private:
    float m_strength;
    Vector2 m_position;
    float m_radius;
    DischargeType m_dischargeType;
    float m_ionizationLevel;
    float m_temperature;
    bool m_active;
    float m_elapsedTime;
    float m_duration;
};

} // namespace Archimedes