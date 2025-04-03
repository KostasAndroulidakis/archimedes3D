#pragma once

#include <memory>
#include <vector>
#include "../math/Vector2.h"

// Forward declarations to avoid circular includes
namespace Archimedes {
    class PlasmaField;
}

namespace Archimedes {

class Ionosphere {
public:
    Ionosphere(float lowerBoundary, float upperBoundary)
        : m_lowerBoundary(lowerBoundary), m_upperBoundary(upperBoundary), m_ionizationLevel(0.5f) {}
    
    // Get ionization level at a height
    float getIonizationLevel(float height) const {
        if (height < m_lowerBoundary || height > m_upperBoundary) {
            return 0.0f;
        }
        
        // Ionization peaks in the middle of the layer
        float normalizedHeight = (height - m_lowerBoundary) / (m_upperBoundary - m_lowerBoundary);
        float peakFactor = 4.0f * normalizedHeight * (1.0f - normalizedHeight); // Peaks at 0.5
        
        return m_ionizationLevel * peakFactor;
    }
    
    // Set base ionization level (0-1)
    void setIonizationLevel(float level) {
        m_ionizationLevel = level;
    }
    
    // Add a plasma field to the ionosphere - using forward declaration
    void addPlasmaField(std::shared_ptr<PlasmaField> field);
    
    // Get all plasma fields - implemented in cpp to avoid circular dependencies
    std::vector<std::shared_ptr<PlasmaField>> getPlasmaFields() const;
    
    // Get ionosphere boundaries
    float getLowerBoundary() const { return m_lowerBoundary; }
    float getUpperBoundary() const { return m_upperBoundary; }
    
    // Update all plasma fields - implemented in cpp
    void update(float deltaTime);
    
    // Generate a lightning strike at position - stub implementation
    void generateLightningStrike(const Vector2& position) {
        // Implementation would generate a lightning strike
    }
    
private:
    float m_lowerBoundary;
    float m_upperBoundary;
    float m_ionizationLevel;
    std::vector<std::shared_ptr<PlasmaField>> m_plasmaFields;
};

} // namespace Archimedes