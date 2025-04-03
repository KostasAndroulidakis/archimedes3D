#pragma once

#include "ElectromagneticField.h"
#include "FieldTypes.h"
#include <vector>

namespace Archimedes {

// Plasma discharge types
enum class DischargeType {
    Corona,         // Glow around charged objects
    Arc,            // Continuous discharge between points
    Lightning,      // Intense, brief discharge
    AuroraEffect    // Atmospheric light display near poles
};

// Class for modeling plasma phenomena
class PlasmaField {
public:
    PlasmaField(float strength, const Vector2& center, float radius);
    
    // Get plasma properties
    Vector2 getCenter() const { return m_center; }
    float getRadius() const { return m_radius; }
    float getTemperature() const { return m_temperature; }
    float getIonizationLevel() const { return m_ionizationLevel; }
    DischargeType getDischargeType() const { return m_dischargeType; }
    
    // Set plasma properties
    void setCenter(const Vector2& center) { m_center = center; }
    void setRadius(float radius) { m_radius = radius; }
    void setTemperature(float temperature) { m_temperature = temperature; }
    void setIonizationLevel(float level) { m_ionizationLevel = level; }
    void setDischargeType(DischargeType type) { m_dischargeType = type; }
    
    // Get field at position
    Vector2 getFieldAt(const Vector2& position) const;
    float getFieldStrengthAt(const Vector2& position) const;
    
    // Calculate ionization effect at position
    float getIonizationAt(const Vector2& position) const;
    
    // Update plasma behavior
    void update(float deltaTime);
    
    // Generate lightning discharge between points
    static std::shared_ptr<LightningField> generateLightning(
        const Vector2& start, const Vector2& end, float strength, float duration);
    
private:
    Vector2 m_center;           // Center of plasma field
    float m_strength;           // Field strength
    float m_radius;             // Radius of influence
    float m_temperature;        // Temperature in Kelvin
    float m_ionizationLevel;    // Level of ionization (0-1)
    DischargeType m_dischargeType; // Type of discharge
    
    // Internal state variables
    float m_timeAccumulator;    // For time-based effects
    float m_oscillationPhase;   // For plasma oscillations
};

// Ionosphere model for the earth
class Ionosphere {
public:
    Ionosphere(float baseHeight, float thickness);
    
    // Get ionosphere properties
    float getBaseHeight() const { return m_baseHeight; }
    float getThickness() const { return m_thickness; }
    float getIonDensity() const { return m_ionDensity; }
    
    // Check if a position is inside the ionosphere
    bool containsPosition(const Vector2& position) const;
    
    // Get ionosphere field effect at position
    Vector2 getFieldVectorAt(const Vector2& position) const;
    
    // Get ionization level at position
    float getIonizationAt(const Vector2& position) const;
    
    // Create a lightning discharge in the ionosphere
    void generateLightningStrike(const Vector2& position);
    
    // Add plasma discharge
    void addPlasmaField(std::shared_ptr<PlasmaField> plasma);
    
    // Update ionosphere state
    void update(float deltaTime);
    
private:
    float m_baseHeight;         // Height where ionosphere begins
    float m_thickness;          // Thickness of the ionosphere
    float m_ionDensity;         // Density of charged particles
    float m_fieldStrength;      // Strength of the electromagnetic field
    
    std::vector<std::shared_ptr<PlasmaField>> m_plasmaFields;
    std::vector<std::shared_ptr<LightningField>> m_lightningFields;
    
    // Update lightning fields
    void updateLightning(float deltaTime);
    
    // Clean up expired lightning
    void cleanupExpiredLightning();
};

} // namespace Archimedes