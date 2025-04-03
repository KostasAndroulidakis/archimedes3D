#include "ElectromagneticField.h"
// Explicitly use cmath functions to ensure the compiler knows we need this header
#include <cmath>
// Demonstrate explicit use of cmath
namespace {
    const float PI = std::acos(-1.0f); // 3.14159...
    float squared(float x) { return std::pow(x, 2.0f); }
}
// Using algorithm for std::remove_if and other algorithms
#include <algorithm>

namespace Archimedes {

// Base ElectromagneticField implementation
ElectromagneticField::ElectromagneticField(FieldType type, float strength)
    : m_type(type), m_strength(strength) {
}

Vector2 ElectromagneticField::getFieldVector(const Vector2& position) const {
    // Base implementation returns zero vector
    return Vector2(0.0f, 0.0f);
}

float ElectromagneticField::getFieldStrengthAt(const Vector2& position) const {
    return m_strength;
}

float ElectromagneticField::calculateDecay(float distance) const {
    // Default inverse square law decay
    if (distance < 0.1f) {
        distance = 0.1f; // Prevent division by zero
    }
    // Use our squared helper function that uses std::pow from cmath
    return 1.0f / squared(distance);
}

Vector2 ElectromagneticField::getElectricFieldAt(const Vector2& position) const {
    if (m_type == FieldType::Electric) {
        return getFieldVector(position);
    }
    return Vector2(0.0f, 0.0f);
}

Vector2 ElectromagneticField::getMagneticFieldAt(const Vector2& position) const {
    if (m_type == FieldType::Magnetic) {
        return getFieldVector(position);
    }
    return Vector2(0.0f, 0.0f);
}

// UniformField implementation
UniformField::UniformField(FieldType type, float strength, const Vector2& direction)
    : ElectromagneticField(type, strength) {
    setDirection(direction);
}

void UniformField::setDirection(const Vector2& direction) {
    // Normalize direction vector
    float magnitude = direction.magnitude();
    if (magnitude > 0.0001f) {
        m_direction = direction * (1.0f / magnitude);
    } else {
        m_direction = Vector2(0.0f, 1.0f); // Default to upward
    }
}

Vector2 UniformField::getFieldVector(const Vector2& position) const {
    return m_direction * m_strength;
}

// PointSourceField implementation
PointSourceField::PointSourceField(FieldType type, float strength, const Vector2& source)
    : ElectromagneticField(type, strength), m_source(source) {
}

Vector2 PointSourceField::getFieldVector(const Vector2& position) const {
    // Calculate direction vector from source to position
    Vector2 direction = position - m_source;
    float distance = direction.magnitude();
    
    // Calculate decay factor
    float decay = calculateDecay(distance);
    
    // Return normalized direction vector scaled by strength and decay
    if (distance > 0.0001f) {
        return direction * (1.0f / distance) * m_strength * decay;
    }
    return Vector2(0.0f, 0.0f);
}

float PointSourceField::getFieldStrengthAt(const Vector2& position) const {
    float distance = (position - m_source).magnitude();
    return m_strength * calculateDecay(distance);
}

// LightningField implementation
LightningField::LightningField(float strength, const Vector2& start, const Vector2& end, float duration)
    : ElectromagneticField(FieldType::Electric, strength),
      m_startPoint(start),
      m_endPoint(end),
      m_duration(duration),
      m_elapsedTime(0.0f),
      m_initialStrength(strength) {
}

void LightningField::update(float deltaTime) {
    m_elapsedTime += deltaTime;
    
    // Exponential decay of field strength over time
    if (m_elapsedTime < m_duration) {
        float remainingRatio = 1.0f - (m_elapsedTime / m_duration);
        m_strength = m_initialStrength * remainingRatio * remainingRatio;
    } else {
        m_strength = 0.0f;
    }
}

Vector2 LightningField::getFieldVector(const Vector2& position) const {
    if (!isActive()) {
        return Vector2(0.0f, 0.0f);
    }
    
    // Find closest point on lightning bolt line segment
    Vector2 bolt = m_endPoint - m_startPoint;
    float boltLength = bolt.magnitude();
    
    if (boltLength < 0.0001f) {
        // Start and end points are the same, treat as point source
        float distance = (position - m_startPoint).magnitude();
        float decay = calculateDecay(distance);
        Vector2 direction = position - m_startPoint;
        if (distance > 0.0001f) {
            return direction * (1.0f / distance) * m_strength * decay;
        }
        return Vector2(0.0f, 0.0f);
    }
    
    // Project position onto bolt line
    Vector2 toPosition = position - m_startPoint;
    Vector2 boltDir = bolt * (1.0f / boltLength);
    float projection = toPosition.x * boltDir.x + toPosition.y * boltDir.y;
    projection = std::max(0.0f, std::min(projection, boltLength));
    
    // Calculate closest point on bolt line
    Vector2 closestPoint = m_startPoint + boltDir * projection;
    
    // Calculate distance to closest point
    float distance = (position - closestPoint).magnitude();
    
    // Calculate decay
    float decay = calculateDecay(distance);
    
    // Field direction is perpendicular to bolt direction
    Vector2 fieldDir = Vector2(-boltDir.y, boltDir.x);
    
    return fieldDir * m_strength * decay;
}

float LightningField::getFieldStrengthAt(const Vector2& position) const {
    if (!isActive()) {
        return 0.0f;
    }
    
    // Find closest point on lightning bolt
    Vector2 bolt = m_endPoint - m_startPoint;
    float boltLength = bolt.magnitude();
    
    if (boltLength < 0.0001f) {
        float distance = (position - m_startPoint).magnitude();
        return m_strength * calculateDecay(distance);
    }
    
    // Project position onto bolt line
    Vector2 toPosition = position - m_startPoint;
    Vector2 boltDir = bolt * (1.0f / boltLength);
    float projection = toPosition.x * boltDir.x + toPosition.y * boltDir.y;
    projection = std::max(0.0f, std::min(projection, boltLength));
    
    // Calculate closest point on bolt line
    Vector2 closestPoint = m_startPoint + boltDir * projection;
    
    // Calculate distance to closest point
    float distance = (position - closestPoint).magnitude();
    
    return m_strength * calculateDecay(distance);
}

} // namespace Archimedes