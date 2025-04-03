#include "Electromagnetism.h"
#include <random>

namespace Archimedes {

void Electromagnetism::setupStandardModel(std::shared_ptr<FieldManager> fieldManager) {
    if (!fieldManager) {
        return;
    }
    
    // Add global field (background field)
    fieldManager->addField(createGlobalField());
    
    // Add central field
    fieldManager->addField(createCentralField());
    
    // Add firmament barrier
    fieldManager->addField(createFirmamentBarrier());
}

std::shared_ptr<UniformField> Electromagnetism::createGlobalField() {
    // Create a uniform magnetic field pointing vertically
    return std::make_shared<UniformField>(
        FieldType::Magnetic,
        50.0f,       // Moderate field strength
        Vector2(0.0f, 1.0f)  // Pointing upward
    );
}

std::shared_ptr<PointSourceField> Electromagnetism::createCentralField() {
    // Create a point source field at the center (0,0)
    return std::make_shared<PointSourceField>(
        FieldType::Electric,
        10000.0f,    // Strong field
        Vector2(0.0f, -100000.0f)  // Located deep below the surface
    );
}

std::shared_ptr<Ionosphere> Electromagnetism::createIonosphere() {
    // Create ionosphere layer starting at 80km with 500km thickness
    return std::make_shared<Ionosphere>(80000.0f, 500000.0f);
}

std::shared_ptr<PlasmaField> Electromagnetism::createAuroraField() {
    // Random position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(-100000.0f, 100000.0f);
    std::uniform_real_distribution<float> height(90000.0f, 120000.0f);
    
    auto aurora = std::make_shared<PlasmaField>(
        1000.0f,     // Field strength
        Vector2(posX(gen), height(gen)),  // Random position in upper atmosphere
        20000.0f     // Large radius
    );
    
    // Configure as aurora
    aurora->setDischargeType(DischargeType::AuroraEffect);
    aurora->setIonizationLevel(0.7f);
    aurora->setTemperature(3000.0f);
    
    return aurora;
}

std::shared_ptr<LightningField> Electromagnetism::createLightningStrike(const Vector2& groundPoint) {
    // Create a lightning strike from clouds to ground
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> heightDist(5000.0f, 10000.0f);
    std::uniform_real_distribution<float> strengthDist(8000.0f, 15000.0f);
    std::uniform_real_distribution<float> durationDist(0.3f, 1.2f);
    
    float cloudHeight = heightDist(gen);
    float strength = strengthDist(gen);
    float duration = durationDist(gen);
    
    // Cloud position is slightly offset from ground position
    std::uniform_real_distribution<float> offsetDist(-1000.0f, 1000.0f);
    Vector2 cloudPos(groundPoint.x + offsetDist(gen), cloudHeight);
    
    return std::make_shared<LightningField>(strength, cloudPos, groundPoint, duration);
}

std::shared_ptr<ElectromagneticField> Electromagnetism::createFirmamentBarrier() {
    // Create an electromagnetic barrier at the firmament
    auto field = std::make_shared<UniformField>(
        FieldType::Electric,
        2000000.0f,  // Extremely strong field
        Vector2(0.0f, -1.0f)  // Pointing downward, repelling charged objects
    );
    
    return field;
}

} // namespace Archimedes