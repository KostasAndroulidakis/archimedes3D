#pragma once

#include "../physics/ElectromagneticField.h"
#include "../physics/PlasmaField.h"
#include "../managers/FieldManager.h"
#include <memory>

namespace Archimedes {

// Factory class for creating electromagnetic fields
class Electromagnetism {
public:
    // Create standard electromagnetic model
    static void setupStandardModel(std::shared_ptr<FieldManager> fieldManager);
    
    // Create specific field types
    static std::shared_ptr<UniformField> createGlobalField();
    static std::shared_ptr<PointSourceField> createCentralField();
    static std::shared_ptr<Ionosphere> createIonosphere();
    
    // Create atmospheric electricity components
    static std::shared_ptr<PlasmaField> createAuroraField();
    static std::shared_ptr<LightningField> createLightningStrike(const Vector2& groundPoint);
    
    // Create electromagnetic barrier
    static std::shared_ptr<ElectromagneticField> createFirmamentBarrier();
};

} // namespace Archimedes