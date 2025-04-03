#pragma once

#include "../math/Vector2.h"
#include "../environment/Medium.h"
#include "../constants/PhysicsConstants.h"

namespace Archimedes {

class BuoyancyCalculator {
public:
    /**
     * Calculate buoyancy force based on Archimedes' principle
     * 
     * @param objectMass The mass of the object in kg
     * @param objectVolume The volume of the object in cubic meters
     * @param medium The medium in which the object is submerged
     * @return The buoyancy force vector (primarily in y-direction)
     */
    static Vector2 calculateBuoyancyForce(float objectMass, float objectVolume, const Medium& medium) {
        float objectDensity = objectMass / objectVolume;
        float mediumDensity = medium.getDensity();
        
        // Buoyant force = density of medium * volume of object * buoyancy coefficient
        float buoyancyMagnitude = mediumDensity * objectVolume * Constants::Physics::BUOYANCY_COEFFICIENT;
        
        // Compute force due to density differential
        float densityDifferential = (mediumDensity - objectDensity) * objectVolume * Constants::Physics::DENSITY_DIFFERENTIAL_FACTOR;
        
        // Return the buoyancy force vector
        // If densityDifferential > 0, object rises (negative y-force in our coordinate system)
        // If densityDifferential < 0, object sinks (positive y-force)
        return Vector2(0.0f, -densityDifferential);
    }
    
    /**
     * Calculate the predicted direction of movement based on density differences
     * 
     * @param objectDensity The density of the object in kg/m³
     * @param mediumDensity The density of the medium in kg/m³
     * @return A direction vector indicating movement (normalized)
     */
    static Vector2 predictMovementDirection(float objectDensity, float mediumDensity) {
        // If object is less dense than medium, it rises
        if (objectDensity < mediumDensity) {
            return Vector2(0.0f, -1.0f);
        }
        // If object is more dense than medium, it sinks
        else if (objectDensity > mediumDensity) {
            return Vector2(0.0f, 1.0f);
        }
        // If densities are equal, no movement
        else {
            return Vector2(0.0f, 0.0f);
        }
    }
};

} // namespace Archimedes