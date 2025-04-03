#include "PlasmaField.h"
#include "../utils/Constants.h"
#include <cmath>
#include <random>

namespace Archimedes {

// Random number generator
namespace {
    std::random_device rd;
    std::mt19937 rng(rd());
    
    float getRandomFloat(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }
}

// PlasmaField implementation
PlasmaField::PlasmaField(float strength, const Vector2& center, float radius)
    : m_center(center),
      m_strength(strength),
      m_radius(radius),
      m_temperature(5000.0f), // Default plasma temperature
      m_ionizationLevel(0.5f), // Default ionization
      m_dischargeType(DischargeType::Corona),
      m_timeAccumulator(0.0f),
      m_oscillationPhase(0.0f) {
}

Vector2 PlasmaField::getFieldAt(const Vector2& position) const {
    // Calculate distance from center
    float distance = (position - m_center).magnitude();
    
    // If outside the radius, no effect
    if (distance > m_radius) {
        return Vector2(0.0f, 0.0f);
    }
    
    // Calculate decay factor (stronger near center)
    float decay = 1.0f - (distance / m_radius);
    
    // Calculate direction (plasma radiates outward from center)
    Vector2 direction;
    if (distance > 0.0001f) {
        direction = (position - m_center) * (1.0f / distance);
    } else {
        // At center, use random direction
        float angle = getRandomFloat(0.0f, 2.0f * 3.14159f);
        direction = Vector2(std::cos(angle), std::sin(angle));
    }
    
    // Apply oscillation effect using phase
    float oscillationFactor = std::sin(m_oscillationPhase) * 0.2f + 0.8f;
    
    // Scale by strength, decay, and oscillation
    return direction * m_strength * decay * oscillationFactor;
}

float PlasmaField::getFieldStrengthAt(const Vector2& position) const {
    // Calculate distance from center
    float distance = (position - m_center).magnitude();
    
    // If outside the radius, no effect
    if (distance > m_radius) {
        return 0.0f;
    }
    
    // Calculate decay factor (stronger near center)
    float decay = 1.0f - (distance / m_radius);
    
    // Apply oscillation effect
    float oscillationFactor = std::sin(m_oscillationPhase) * 0.2f + 0.8f;
    
    return m_strength * decay * oscillationFactor;
}

float PlasmaField::getIonizationAt(const Vector2& position) const {
    // Calculate distance from center
    float distance = (position - m_center).magnitude();
    
    // If outside the radius, no ionization
    if (distance > m_radius) {
        return 0.0f;
    }
    
    // Calculate decay factor (stronger near center)
    float decay = 1.0f - (distance / m_radius);
    
    // Ionization level is affected by temperature
    float temperatureFactor = m_temperature / 10000.0f; // Normalized to 1.0 at 10000K
    temperatureFactor = std::min(temperatureFactor, 1.0f);
    
    return m_ionizationLevel * decay * temperatureFactor;
}

void PlasmaField::update(float deltaTime) {
    // Update time accumulator
    m_timeAccumulator += deltaTime;
    
    // Update oscillation phase
    m_oscillationPhase += deltaTime * 2.0f;
    if (m_oscillationPhase > 2.0f * 3.14159f) {
        m_oscillationPhase -= 2.0f * 3.14159f;
    }
    
    // Random fluctuations in strength (plasma is chaotic)
    float fluctuation = getRandomFloat(-0.1f, 0.1f);
    m_strength *= (1.0f + fluctuation * deltaTime);
    
    // Ensure strength stays within reasonable bounds
    m_strength = std::max(0.1f, std::min(m_strength, 10.0f));
}

std::shared_ptr<LightningField> PlasmaField::generateLightning(
    const Vector2& start, const Vector2& end, float strength, float duration) {
    return std::make_shared<LightningField>(strength, start, end, duration);
}

// Ionosphere implementation
Ionosphere::Ionosphere(float baseHeight, float thickness)
    : m_baseHeight(baseHeight),
      m_thickness(thickness),
      m_ionDensity(1.0f),
      m_fieldStrength(0.5f) {
}

bool Ionosphere::containsPosition(const Vector2& position) const {
    return position.y >= m_baseHeight && position.y <= (m_baseHeight + m_thickness);
}

Vector2 Ionosphere::getFieldVectorAt(const Vector2& position) const {
    if (!containsPosition(position)) {
        return Vector2(0.0f, 0.0f);
    }
    
    // Basic horizontal field in ionosphere
    return Vector2(m_fieldStrength, 0.0f);
}

float Ionosphere::getIonizationAt(const Vector2& position) const {
    if (!containsPosition(position)) {
        return 0.0f;
    }
    
    // Calculate relative height within ionosphere
    float relativeHeight = (position.y - m_baseHeight) / m_thickness;
    
    // Ionization peaks in the middle of the layer
    float heightFactor = 1.0f - std::abs(relativeHeight - 0.5f) * 2.0f;
    
    return m_ionDensity * heightFactor;
}

void Ionosphere::generateLightningStrike(const Vector2& position) {
    // Create a lightning strike from ionosphere to ground
    float height = position.y;
    
    // Lightning source is in the ionosphere
    Vector2 source(position.x, m_baseHeight + getRandomFloat(0.0f, m_thickness));
    
    // Lightning target is on ground
    Vector2 target(position.x + getRandomFloat(-100.0f, 100.0f), 0.0f);
    
    // Create lightning with random strength and duration
    float strength = getRandomFloat(1.0f, 10.0f);
    float duration = getRandomFloat(0.5f, 2.0f);
    
    auto lightning = std::make_shared<LightningField>(strength, source, target, duration);
    m_lightningFields.push_back(lightning);
}

void Ionosphere::addPlasmaField(std::shared_ptr<PlasmaField> plasma) {
    m_plasmaFields.push_back(plasma);
}

void Ionosphere::update(float deltaTime) {
    // Update all plasma fields
    for (auto& plasma : m_plasmaFields) {
        plasma->update(deltaTime);
    }
    
    // Update lightning fields
    updateLightning(deltaTime);
    
    // Clean up expired lightning
    cleanupExpiredLightning();
    
    // Random chance of new lightning generation
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    if (chance(rng) < Constants::Environment::Lightning::GENERATION_PROBABILITY) {
        // Generate random position for lightning
        std::uniform_real_distribution<float> posX(
            Constants::Environment::Lightning::MIN_POSITION_X,
            Constants::Environment::Lightning::MAX_POSITION_X
        );
        Vector2 lightningPosition(posX(rng), m_baseHeight);
        generateLightningStrike(lightningPosition);
    }
}

void Ionosphere::updateLightning(float deltaTime) {
    for (auto& lightning : m_lightningFields) {
        lightning->update(deltaTime);
    }
}

void Ionosphere::cleanupExpiredLightning() {
    // Remove expired lightning
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