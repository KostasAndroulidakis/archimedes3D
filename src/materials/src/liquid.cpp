#include "../include/liquid.h"

namespace archimedes3d {

bool LiquidMaterials::registryInitialized = false;
std::unordered_map<std::string, std::shared_ptr<LiquidMaterial>> LiquidMaterials::registry;

void LiquidMaterials::initializeRegistry() {
    if (registryInitialized) return;
    
    registry["water"] = createWater();
    registry["saltwater"] = createSaltwater();
    registry["oil"] = createOil();
    registry["gasoline"] = createGasoline();
    registry["mercury"] = createMercury();
    registry["ethanol"] = createEthanol();
    registry["blood"] = createBlood();
    registry["honey"] = createHoney();
    registry["liquid_nitrogen"] = createLiquidNitrogen();
    
    registryInitialized = true;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::get(const std::string& name) {
    if (!registryInitialized) {
        initializeRegistry();
    }
    
    auto it = registry.find(name);
    if (it != registry.end()) {
        return it->second;
    }
    
    return nullptr;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createWater() {
    auto water = std::make_shared<LiquidMaterial>("Water", 1000.0);
    water->setViscosity(0.001);             // Pa·s at 20°C
    water->setSurfaceTension(0.072);        // N/m at 20°C
    water->setFreezingPoint(273.15);        // K (0°C)
    water->setElectricalConductivity(5.5e-6); // S/m (pure water)
    water->setThermalConductivity(0.598);   // W/(m·K)
    water->setSpecificHeat(4182.0);         // J/(kg·K)
    return water;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createSaltwater() {
    auto saltwater = std::make_shared<LiquidMaterial>("Saltwater", 1025.0);
    saltwater->setViscosity(0.00108);          // Pa·s
    saltwater->setSurfaceTension(0.073);       // N/m
    saltwater->setFreezingPoint(271.15);       // K (approx. -2°C)
    saltwater->setElectricalConductivity(5.0); // S/m (higher than pure water)
    saltwater->setThermalConductivity(0.596);  // W/(m·K)
    saltwater->setSpecificHeat(3993.0);        // J/(kg·K)
    return saltwater;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createOil() {
    auto oil = std::make_shared<LiquidMaterial>("Vegetable Oil", 920.0);
    oil->setViscosity(0.04);                // Pa·s
    oil->setSurfaceTension(0.032);          // N/m
    oil->setFreezingPoint(263.15);          // K (approx. -10°C)
    oil->setElectricalConductivity(1.0e-11); // S/m (insulator)
    oil->setThermalConductivity(0.17);      // W/(m·K)
    oil->setSpecificHeat(1670.0);           // J/(kg·K)
    return oil;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createGasoline() {
    auto gasoline = std::make_shared<LiquidMaterial>("Gasoline", 750.0);
    gasoline->setViscosity(0.0006);           // Pa·s
    gasoline->setSurfaceTension(0.022);       // N/m
    gasoline->setFreezingPoint(183.15);       // K (approx. -90°C)
    gasoline->setElectricalConductivity(1.0e-14); // S/m (poor conductor)
    gasoline->setThermalConductivity(0.15);   // W/(m·K)
    gasoline->setSpecificHeat(2220.0);        // J/(kg·K)
    return gasoline;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createMercury() {
    auto mercury = std::make_shared<LiquidMaterial>("Mercury", 13600.0);
    mercury->setViscosity(0.00152);          // Pa·s
    mercury->setSurfaceTension(0.487);       // N/m
    mercury->setFreezingPoint(234.32);       // K (-38.83°C)
    mercury->setElectricalConductivity(1.0e6); // S/m (excellent conductor)
    mercury->setThermalConductivity(8.3);    // W/(m·K)
    mercury->setSpecificHeat(140.0);         // J/(kg·K)
    return mercury;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createEthanol() {
    auto ethanol = std::make_shared<LiquidMaterial>("Ethanol", 789.0);
    ethanol->setViscosity(0.00112);          // Pa·s
    ethanol->setSurfaceTension(0.022);       // N/m
    ethanol->setFreezingPoint(159.05);       // K (-114.1°C)
    ethanol->setElectricalConductivity(1.0e-7); // S/m
    ethanol->setThermalConductivity(0.171);  // W/(m·K)
    ethanol->setSpecificHeat(2440.0);        // J/(kg·K)
    return ethanol;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createBlood() {
    auto blood = std::make_shared<LiquidMaterial>("Blood", 1060.0);
    blood->setViscosity(0.004);              // Pa·s
    blood->setSurfaceTension(0.058);         // N/m
    blood->setFreezingPoint(271.35);         // K (approx. -1.8°C)
    blood->setElectricalConductivity(0.7);   // S/m
    blood->setThermalConductivity(0.492);    // W/(m·K)
    blood->setSpecificHeat(3650.0);          // J/(kg·K)
    return blood;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createHoney() {
    auto honey = std::make_shared<LiquidMaterial>("Honey", 1420.0);
    honey->setViscosity(10.0);               // Pa·s (highly viscous)
    honey->setSurfaceTension(0.07);          // N/m
    honey->setFreezingPoint(253.15);         // K (approx. -20°C)
    honey->setElectricalConductivity(1.0e-6); // S/m
    honey->setThermalConductivity(0.5);      // W/(m·K)
    honey->setSpecificHeat(2260.0);          // J/(kg·K)
    return honey;
}

std::shared_ptr<LiquidMaterial> LiquidMaterials::createLiquidNitrogen() {
    auto ln2 = std::make_shared<LiquidMaterial>("Liquid Nitrogen", 808.0);
    ln2->setViscosity(0.000158);           // Pa·s
    ln2->setSurfaceTension(0.0089);        // N/m
    ln2->setFreezingPoint(63.15);          // K (-210°C)
    ln2->setElectricalConductivity(1.0e-16); // S/m (insulator)
    ln2->setThermalConductivity(0.1396);   // W/(m·K)
    ln2->setSpecificHeat(1040.0);          // J/(kg·K)
    return ln2;
}

} // namespace archimedes3d
