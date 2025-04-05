#pragma once

#include "material.h"
#include <memory>
#include <unordered_map>

namespace archimedes3d {

class LiquidMaterials {
public:
    // Standard liquid materials
    static std::shared_ptr<LiquidMaterial> createWater();
    static std::shared_ptr<LiquidMaterial> createSaltwater();
    static std::shared_ptr<LiquidMaterial> createOil();
    static std::shared_ptr<LiquidMaterial> createGasoline();
    static std::shared_ptr<LiquidMaterial> createMercury();
    static std::shared_ptr<LiquidMaterial> createEthanol();
    static std::shared_ptr<LiquidMaterial> createBlood();
    static std::shared_ptr<LiquidMaterial> createHoney();
    static std::shared_ptr<LiquidMaterial> createLiquidNitrogen();
    
    // Registry access
    static std::shared_ptr<LiquidMaterial> get(const std::string& name);
    
private:
    static void initializeRegistry();
    static bool registryInitialized;
    static std::unordered_map<std::string, std::shared_ptr<LiquidMaterial>> registry;
};

} // namespace archimedes3d
