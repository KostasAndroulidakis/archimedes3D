#pragma once

#include "material.h"
#include <memory>
#include <unordered_map>

namespace archimedes3d {

class PlasmaMaterials {
public:
    // Standard plasma materials
    static std::shared_ptr<PlasmaMaterial> createIonizedAir();
    static std::shared_ptr<PlasmaMaterial> createSolarPlasma();
    static std::shared_ptr<PlasmaMaterial> createNeonPlasma();
    static std::shared_ptr<PlasmaMaterial> createArgonPlasma();
    static std::shared_ptr<PlasmaMaterial> createHydrogenPlasma();
    static std::shared_ptr<PlasmaMaterial> createHeliumPlasma();
    static std::shared_ptr<PlasmaMaterial> createXenonPlasma();
    static std::shared_ptr<PlasmaMaterial> createMercuryPlasma();
    static std::shared_ptr<PlasmaMaterial> createPlasmaJet();
    
    // Registry access
    static std::shared_ptr<PlasmaMaterial> get(const std::string& name);
    
private:
    static void initializeRegistry();
    static bool registryInitialized;
    static std::unordered_map<std::string, std::shared_ptr<PlasmaMaterial>> registry;
};

} // namespace archimedes3d
