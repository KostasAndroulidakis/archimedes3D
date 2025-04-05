#include "../include/gas.h"

namespace archimedes3d {

bool GasMaterials::registryInitialized = false;
std::unordered_map<std::string, std::shared_ptr<GasMaterial>> GasMaterials::registry;

void GasMaterials::initializeRegistry() {
    if (registryInitialized) return;
    
    registry["air"] = createAir();
    registry["helium"] = createHelium();
    registry["hydrogen"] = createHydrogen();
    registry["oxygen"] = createOxygen();
    registry["carbon_dioxide"] = createCarbonDioxide();
    registry["methane"] = createMethane();
    registry["steam"] = createSteam();
    registry["nitrogen"] = createNitrogen();
    registry["argon"] = createArgon();
    
    registryInitialized = true;
}

std::shared_ptr<GasMaterial> GasMaterials::get(const std::string& name) {
    if (!registryInitialized) {
        initializeRegistry();
    }
    
    auto it = registry.find(name);
    if (it != registry.end()) {
        return it->second;
    }
    
    return nullptr;
}

std::shared_ptr<GasMaterial> GasMaterials::createAir() {
    auto air = std::make_shared<GasMaterial>("Air", 1.225);
    air->setCompressionFactor(1.0);           // Near-ideal at STP
    air->setExpansionCoefficient(3.43e-3);    // 1/K
    air->setElectricalConductivity(3.0e-15);  // Poor conductor
    air->setThermalConductivity(0.026);       // W/(m·K)
    air->setSpecificHeat(1005.0);             // J/(kg·K)
    return air;
}

std::shared_ptr<GasMaterial> GasMaterials::createHelium() {
    auto helium = std::make_shared<GasMaterial>("Helium", 0.1786);
    helium->setCompressionFactor(1.0004);      // Nearly ideal
    helium->setExpansionCoefficient(3.665e-3); // 1/K
    helium->setElectricalConductivity(0.0);    // Non-conductor
    helium->setThermalConductivity(0.151);     // W/(m·K)
    helium->setSpecificHeat(5193.0);           // J/(kg·K)
    return helium;
}

std::shared_ptr<GasMaterial> GasMaterials::createHydrogen() {
    auto hydrogen = std::make_shared<GasMaterial>("Hydrogen", 0.0899);
    hydrogen->setCompressionFactor(1.0006);      // Nearly ideal
    hydrogen->setExpansionCoefficient(3.661e-3); // 1/K
    hydrogen->setElectricalConductivity(0.0);    // Non-conductor
    hydrogen->setThermalConductivity(0.182);     // W/(m·K)
    hydrogen->setSpecificHeat(14304.0);          // J/(kg·K)
    return hydrogen;
}

std::shared_ptr<GasMaterial> GasMaterials::createOxygen() {
    auto oxygen = std::make_shared<GasMaterial>("Oxygen", 1.429);
    oxygen->setCompressionFactor(0.9994);      // Nearly ideal
    oxygen->setExpansionCoefficient(3.43e-3);  // 1/K
    oxygen->setElectricalConductivity(0.0);    // Non-conductor
    oxygen->setMagneticPermeability(1.000002); // Slightly paramagnetic
    oxygen->setThermalConductivity(0.026);     // W/(m·K)
    oxygen->setSpecificHeat(919.0);            // J/(kg·K)
    return oxygen;
}

std::shared_ptr<GasMaterial> GasMaterials::createCarbonDioxide() {
    auto co2 = std::make_shared<GasMaterial>("Carbon Dioxide", 1.98);
    co2->setCompressionFactor(0.9942);        // Non-ideal
    co2->setExpansionCoefficient(3.37e-3);    // 1/K
    co2->setElectricalConductivity(0.0);      // Non-conductor
    co2->setThermalConductivity(0.0166);      // W/(m·K)
    co2->setSpecificHeat(843.0);              // J/(kg·K)
    return co2;
}

std::shared_ptr<GasMaterial> GasMaterials::createMethane() {
    auto methane = std::make_shared<GasMaterial>("Methane", 0.668);
    methane->setCompressionFactor(0.998);        // Nearly ideal
    methane->setExpansionCoefficient(3.56e-3);   // 1/K
    methane->setElectricalConductivity(0.0);     // Non-conductor
    methane->setThermalConductivity(0.034);      // W/(m·K)
    methane->setSpecificHeat(2220.0);            // J/(kg·K)
    return methane;
}

std::shared_ptr<GasMaterial> GasMaterials::createSteam() {
    auto steam = std::make_shared<GasMaterial>("Steam", 0.6);
    steam->setCompressionFactor(0.975);          // Non-ideal
    steam->setExpansionCoefficient(1.66e-3);     // 1/K
    steam->setElectricalConductivity(1.0e-16);   // Poor conductor
    steam->setThermalConductivity(0.025);        // W/(m·K)
    steam->setSpecificHeat(2080.0);              // J/(kg·K)
    return steam;
}

std::shared_ptr<GasMaterial> GasMaterials::createNitrogen() {
    auto nitrogen = std::make_shared<GasMaterial>("Nitrogen", 1.2506);
    nitrogen->setCompressionFactor(0.9998);      // Nearly ideal
    nitrogen->setExpansionCoefficient(3.67e-3);  // 1/K
    nitrogen->setElectricalConductivity(0.0);    // Non-conductor
    nitrogen->setMagneticPermeability(0.99999);  // Slightly diamagnetic
    nitrogen->setThermalConductivity(0.026);     // W/(m·K)
    nitrogen->setSpecificHeat(1040.0);           // J/(kg·K)
    return nitrogen;
}

std::shared_ptr<GasMaterial> GasMaterials::createArgon() {
    auto argon = std::make_shared<GasMaterial>("Argon", 1.784);
    argon->setCompressionFactor(0.9994);        // Nearly ideal
    argon->setExpansionCoefficient(3.68e-3);    // 1/K
    argon->setElectricalConductivity(0.0);      // Non-conductor
    argon->setThermalConductivity(0.018);       // W/(m·K)
    argon->setSpecificHeat(520.0);              // J/(kg·K)
    return argon;
}

} // namespace archimedes3d
