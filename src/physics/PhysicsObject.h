#pragma once

#include "../math/Vector2.h"

namespace Archimedes {

class Medium;

class PhysicsObject {
public:
    PhysicsObject(float mass, float volume, const Vector2& position);
    virtual ~PhysicsObject() = default;
    
    // Getters
    float getMass() const { return m_mass; }
    float getVolume() const { return m_volume; }
    float getDensity() const { return m_mass / m_volume; }
    Vector2 getPosition() const { return m_position; }
    Vector2 getVelocity() const { return m_velocity; }
    
    // Setters
    void setMass(float mass) { m_mass = mass; }
    void setVolume(float volume) { m_volume = volume; }
    void setPosition(const Vector2& position) { m_position = position; }
    void setVelocity(const Vector2& velocity) { m_velocity = velocity; }
    
    // Update physics state
    virtual void update(float deltaTime, const Medium& medium);
    
    // Apply a force to the object
    void applyForce(const Vector2& force);
    
protected:
    float m_mass;       // Mass in kg
    float m_volume;     // Volume in m³
    Vector2 m_position; // Position in world space
    Vector2 m_velocity; // Velocity in m/s
    Vector2 m_force;    // Accumulated force in N
};

} // namespace Archimedes