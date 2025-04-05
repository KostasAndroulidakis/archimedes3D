#pragma once

#include "material.h"
#include <memory>
#include <unordered_map>

namespace archimedes3d {

// Factory function to create standard solid materials
class SolidMaterials {
public:
    // Standard solid materials 
    static std::shared_ptr<SolidMaterial> createWood();
    static std::shared_ptr<SolidMaterial> createIce();
    static std::shared_ptr<SolidMaterial> createConcrete();
    static std::shared_ptr<SolidMaterial> createAluminum();
    static std::shared_ptr<SolidMaterial> createSteel();
    static std::shared_ptr<SolidMaterial> createCopper();
    static std::shared_ptr<SolidMaterial> createLead();
    static std::shared_ptr<SolidMaterial> createGold();
    static std::shared_ptr<SolidMaterial> createAerogel();
    
    // Registry of all available solid materials
    static std::shared_ptr<SolidMaterial> get(const std::string& name);
    
private:
    static void initializeRegistry();
    static bool registryInitialized;
    static std::unordered_map<std::string, std::shared_ptr<SolidMaterial>> registry;
};

} // namespace archimedes3d
