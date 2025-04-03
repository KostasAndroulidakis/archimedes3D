#include "PhysicsObject.h"
#include "../environment/Medium.h"
#include "../utils/Constants.h"
#include <cmath>

namespace Archimedes {

PhysicsObject::PhysicsObject(float mass, float volume, const Vector2& position)
    : m_mass(mass), m_volume(volume), m_position(position), m_velocity(0.0f, 0.0f), m_force(0.0f, 0.0f) {
}

void PhysicsObject::update(float deltaTime, const Medium& medium) {
    // Calculate densities
    float objectDensity = m_mass / m_volume;
    float mediumDensity = medium.getDensity();
    
    // Archimedes' principle: buoyant force = weight of displaced fluid
    // Force = medium_density * volume * displacement_constant
    const float displacementConstant = Constants::Physics::DISPLACEMENT_FACTOR;
    
    // Net force based on density difference (key principle of Archimedes engine)
    // If object is less dense than medium -> upward force
    // If object is more dense than medium -> downward force
    float densityDifference = objectDensity - mediumDensity;
    Vector2 netForce(0.0f, -densityDifference * m_volume * displacementConstant);
    
    // Add drag force based on velocity
    float dragCoefficient = Constants::Physics::STANDARD_DRAG_COEFFICIENT;
    float crossSectionalArea = std::pow(m_volume, 2.0f/3.0f); // Approximation
    float dragFactor = Constants::Simulation::DRAG_COEFFICIENT_FACTOR * mediumDensity * dragCoefficient * crossSectionalArea;
    
    float velocityMagnitude = m_velocity.magnitude();
    if (velocityMagnitude > Constants::Physics::VELOCITY_THRESHOLD) {
        Vector2 dragDirection = m_velocity * (-1.0f / velocityMagnitude);
        Vector2 dragForce = dragDirection * dragFactor * velocityMagnitude * velocityMagnitude;
        netForce += dragForce;
    }
    
    // Apply force
    m_force = netForce;
    
    // Calculate acceleration (F = ma, so a = F/m)
    Vector2 acceleration = m_force * (1.0f / m_mass);
    
    // Terminal velocity calculation to prevent numerical issues
    float terminalVelocity = std::sqrt((std::abs(densityDifference) * m_volume * displacementConstant) / 
                                    (Constants::Simulation::DRAG_COEFFICIENT_FACTOR * dragCoefficient * mediumDensity * crossSectionalArea));
    
    if (terminalVelocity > Constants::Physics::MAX_TERMINAL_VELOCITY) {
        terminalVelocity = Constants::Physics::MAX_TERMINAL_VELOCITY;
    }
    
    // Update velocity with acceleration
    m_velocity += acceleration * deltaTime;
    
    // Cap velocity at terminal velocity
    if (m_velocity.magnitude() > terminalVelocity) {
        m_velocity = m_velocity.normalized() * terminalVelocity;
    }
    
    // Update position
    Vector2 newPosition = m_position + m_velocity * deltaTime;
    
    // Ensure objects don't go below ground level
    if (newPosition.y < 0.0f) {
        newPosition.y = 0.0f;
        // If hitting ground, reverse/dampen vertical velocity
        if (m_velocity.y < 0.0f) {
            m_velocity.y = -m_velocity.y * Constants::Physics::VELOCITY_DAMPENING;
        }
    }
    
    m_position = newPosition;
}

void PhysicsObject::applyForce(const Vector2& force) {
    m_force += force;
}

} // namespace Archimedes