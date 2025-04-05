#include "../include/solid.h"
#include <unordered_map>

namespace archimedes3d {

bool SolidMaterials::registryInitialized = false;
std::unordered_map<std::string, std::shared_ptr<SolidMaterial>> SolidMaterials::registry;

void SolidMaterials::initializeRegistry() {
    if (registryInitialized) return;
    
    registry["wood"] = createWood();
    registry["ice"] = createIce();
    registry["concrete"] = createConcrete();
    registry["aluminum"] = createAluminum();
    registry["steel"] = createSteel();
    registry["copper"] = createCopper();
    registry["lead"] = createLead();
    registry["gold"] = createGold();
    registry["aerogel"] = createAerogel();
    
    registryInitialized = true;
}

std::shared_ptr<SolidMaterial> SolidMaterials::get(const std::string& name) {
    if (!registryInitialized) {
        initializeRegistry();
    }
    
    auto it = registry.find(name);
    if (it != registry.end()) {
        return it->second;
    }
    
    return nullptr;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createWood() {
    auto wood = std::make_shared<SolidMaterial>("Wood", 700.0);
    wood->setElasticity(11.0e9);         // ~11 GPa
    wood->setTensileStrength(50.0e6);    // ~50 MPa
    wood->setHardness(3.0);              // Mohs scale approximation
    wood->setElectricalConductivity(1.0e-14); // Very poor conductor
    wood->setThermalConductivity(0.12);  // W/(m·K)
    wood->setSpecificHeat(1700.0);       // J/(kg·K)
    return wood;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createIce() {
    auto ice = std::make_shared<SolidMaterial>("Ice", 917.0);
    ice->setElasticity(9.5e9);           // ~9.5 GPa
    ice->setTensileStrength(1.0e6);      // ~1 MPa
    ice->setHardness(1.5);               // Mohs scale
    ice->setElectricalConductivity(1.0e-10); // Poor conductor
    ice->setThermalConductivity(2.18);   // W/(m·K)
    ice->setSpecificHeat(2100.0);        // J/(kg·K)
    return ice;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createConcrete() {
    auto concrete = std::make_shared<SolidMaterial>("Concrete", 2400.0);
    concrete->setElasticity(30.0e9);      // ~30 GPa
    concrete->setTensileStrength(3.0e6);  // ~3 MPa
    concrete->setHardness(7.0);           // Mohs scale approximation
    concrete->setElectricalConductivity(1.0e-6); // Poor conductor
    concrete->setThermalConductivity(1.7);    // W/(m·K)
    concrete->setSpecificHeat(880.0);         // J/(kg·K)
    return concrete;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createAluminum() {
    auto aluminum = std::make_shared<SolidMaterial>("Aluminum", 2700.0);
    aluminum->setElasticity(69.0e9);       // 69 GPa
    aluminum->setTensileStrength(310.0e6); // 310 MPa
    aluminum->setHardness(2.75);           // Mohs scale
    aluminum->setElectricalConductivity(3.5e7); // Good conductor
    aluminum->setMagneticPermeability(1.000022); // Slightly paramagnetic
    aluminum->setThermalConductivity(237.0);    // W/(m·K)
    aluminum->setSpecificHeat(897.0);          // J/(kg·K)
    return aluminum;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createSteel() {
    auto steel = std::make_shared<SolidMaterial>("Steel", 7850.0);
    steel->setElasticity(200.0e9);       // 200 GPa
    steel->setTensileStrength(400.0e6);  // 400 MPa
    steel->setHardness(4.5);             // Mohs scale approximation
    steel->setElectricalConductivity(6.99e6); // Good conductor
    steel->setMagneticPermeability(100.0);    // Ferromagnetic
    steel->setThermalConductivity(50.2);      // W/(m·K)
    steel->setSpecificHeat(490.0);            // J/(kg·K)
    return steel;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createCopper() {
    auto copper = std::make_shared<SolidMaterial>("Copper", 8960.0);
    copper->setElasticity(117.0e9);       // 117 GPa
    copper->setTensileStrength(220.0e6);  // 220 MPa
    copper->setHardness(3.0);             // Mohs scale
    copper->setElectricalConductivity(5.96e7); // Excellent conductor
    copper->setMagneticPermeability(0.999994); // Slightly diamagnetic
    copper->setThermalConductivity(401.0);     // W/(m·K)
    copper->setSpecificHeat(385.0);            // J/(kg·K)
    return copper;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createLead() {
    auto lead = std::make_shared<SolidMaterial>("Lead", 11340.0);
    lead->setElasticity(16.0e9);         // 16 GPa
    lead->setTensileStrength(18.0e6);    // 18 MPa
    lead->setHardness(1.5);              // Mohs scale
    lead->setElectricalConductivity(4.55e6);  // Good conductor
    lead->setMagneticPermeability(0.99998);   // Diamagnetic
    lead->setThermalConductivity(35.3);       // W/(m·K)
    lead->setSpecificHeat(129.0);             // J/(kg·K)
    return lead;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createGold() {
    auto gold = std::make_shared<SolidMaterial>("Gold", 19300.0);
    gold->setElasticity(79.0e9);          // 79 GPa
    gold->setTensileStrength(120.0e6);    // 120 MPa
    gold->setHardness(2.5);               // Mohs scale
    gold->setElectricalConductivity(4.52e7);  // Excellent conductor
    gold->setMagneticPermeability(0.99996);   // Diamagnetic
    gold->setThermalConductivity(317.0);      // W/(m·K)
    gold->setSpecificHeat(129.0);             // J/(kg·K)
    return gold;
}

std::shared_ptr<SolidMaterial> SolidMaterials::createAerogel() {
    auto aerogel = std::make_shared<SolidMaterial>("Aerogel", 3.0);
    aerogel->setElasticity(1.0e6);         // Very flexible
    aerogel->setTensileStrength(16.0e3);   // Very fragile
    aerogel->setHardness(0.5);             // Extremely soft
    aerogel->setElectricalConductivity(1.0e-15); // Insulator
    aerogel->setThermalConductivity(0.013);     // Excellent insulator
    aerogel->setSpecificHeat(1000.0);           // J/(kg·K)
    return aerogel;
}

} // namespace archimedes3d
