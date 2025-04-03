#pragma once

#include "../math/Vector2.h"
#include <vector>
#include <memory>

namespace Archimedes {

// Field behavior types
enum class FieldType {
    Electric,
    Magnetic,
    Plasma
};

class ElectromagneticField {
public:
    ElectromagneticField(FieldType type, float strength);
    virtual ~ElectromagneticField() = default;
    
    // Field properties
    FieldType getType() const { return m_type; }
    float getStrength() const { return m_strength; }
    void setStrength(float strength) { m_strength = strength; }
    
    // Calculate field vector at a point in space
    virtual Vector2 getFieldVector(const Vector2& position) const;
    
    // Calculate field strength at position
    virtual float getFieldStrengthAt(const Vector2& position) const;
    
    // Apply decay with distance
    virtual float calculateDecay(float distance) const;

protected:
    FieldType m_type;
    float m_strength;
};

// Uniform field (same strength and direction everywhere)
class UniformField : public ElectromagneticField {
public:
    UniformField(FieldType type, float strength, const Vector2& direction);
    
    // Get/set field direction
    Vector2 getDirection() const { return m_direction; }
    void setDirection(const Vector2& direction);
    
    // Override field vector calculation
    Vector2 getFieldVector(const Vector2& position) const override;
    
private:
    Vector2 m_direction; // Normalized direction vector
};

// Point source field (radiates from a point, decays with distance)
class PointSourceField : public ElectromagneticField {
public:
    PointSourceField(FieldType type, float strength, const Vector2& source);
    
    // Get/set source point
    Vector2 getSource() const { return m_source; }
    void setSource(const Vector2& source) { m_source = source; }
    
    // Override field methods
    Vector2 getFieldVector(const Vector2& position) const override;
    float getFieldStrengthAt(const Vector2& position) const override;
    
private:
    Vector2 m_source; // Field origin point
};

// Lightning field (temporary high-strength discharge between points)
class LightningField : public ElectromagneticField {
public:
    LightningField(float strength, const Vector2& start, const Vector2& end, float duration);
    
    // Get lightning properties
    Vector2 getStartPoint() const { return m_startPoint; }
    Vector2 getEndPoint() const { return m_endPoint; }
    float getDuration() const { return m_duration; }
    float getElapsedTime() const { return m_elapsedTime; }
    bool isActive() const { return m_elapsedTime < m_duration; }
    
    // Update lightning (reduce strength over time)
    void update(float deltaTime);
    
    // Override field methods
    Vector2 getFieldVector(const Vector2& position) const override;
    float getFieldStrengthAt(const Vector2& position) const override;
    
private:
    Vector2 m_startPoint;
    Vector2 m_endPoint;
    float m_duration;
    float m_elapsedTime;
    float m_initialStrength;
};

// Manager for multiple fields
class FieldManager {
public:
    // Add fields
    void addField(std::shared_ptr<ElectromagneticField> field);
    
    // Update all fields
    void update(float deltaTime);
    
    // Get net field vector at position
    Vector2 getNetFieldVector(const Vector2& position, FieldType type) const;
    
    // Get all fields of a specific type
    std::vector<std::shared_ptr<ElectromagneticField>> getFieldsByType(FieldType type) const;
    
private:
    std::vector<std::shared_ptr<ElectromagneticField>> m_fields;
};

} // namespace Archimedes