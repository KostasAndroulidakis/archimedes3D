#pragma once

#include "material.h"
#include <memory>
#include <unordered_map>

namespace archimedes3d {

class GasMaterials {
public:
    // Standard gas materials
    static std::shared_ptr<GasMaterial> createAir();
    static std::shared_ptr<GasMaterial> createHelium();
    static std::shared_ptr<GasMaterial> createHydrogen();
    static std::shared_ptr<GasMaterial> createOxygen();
    static std::shared_ptr<GasMaterial> createCarbonDioxide();
    static std::shared_ptr<GasMaterial> createMethane();
    static std::shared_ptr<GasMaterial> createSteam();
    static std::shared_ptr<GasMaterial> createNitrogen();
    static std::shared_ptr<GasMaterial> createArgon();
    
    // Registry lookup
    static std::shared_ptr<GasMaterial> get(const std::string& name);
    
private:
    static void initializeRegistry();
    static bool registryInitialized;
    static std::unordered_map<std::string, std::shared_ptr<GasMaterial>> registry;
};

} // namespace archimedes3d
