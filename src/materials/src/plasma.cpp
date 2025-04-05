#include "../include/plasma.h"

namespace archimedes3d {

bool PlasmaMaterials::registryInitialized = false;
std::unordered_map<std::string, std::shared_ptr<PlasmaMaterial>> PlasmaMaterials::registry;

void PlasmaMaterials::initializeRegistry() {
    if (registryInitialized) return;
    
    registry["ionized_air"] = createIonizedAir();
    registry["solar_plasma"] = createSolarPlasma();
    registry["neon_plasma"] = createNeonPlasma();
    registry["argon_plasma"] = createArgonPlasma();
    registry["hydrogen_plasma"] = createHydrogenPlasma();
    registry["helium_plasma"] = createHeliumPlasma();
    registry["xenon_plasma"] = createXenonPlasma();
    registry["mercury_plasma"] = createMercuryPlasma();
    registry["plasma_jet"] = createPlasmaJet();
    
    registryInitialized = true;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::get(const std::string& name) {
    if (!registryInitialized) {
        initializeRegistry();
    }
    
    auto it = registry.find(name);
    if (it != registry.end()) {
        return it->second;
    }
    
    return nullptr;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createIonizedAir() {
    auto plasma = std::make_shared<PlasmaMaterial>("Ionized Air", 1.0);  // Approximate density
    plasma->setIonizationLevel(0.01);         // Low ionization (1%)
    plasma->setElectronDensity(1.0e16);       // Electrons/m³
    plasma->setPlasmaFrequency(8.9e9);        // Hz
    plasma->setElectricalConductivity(0.1);   // Low conductivity
    plasma->setThermalConductivity(0.3);      // W/(m·K)
    plasma->setSpecificHeat(1005.0);          // Similar to air
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createSolarPlasma() {
    auto plasma = std::make_shared<PlasmaMaterial>("Solar Plasma", 1.0e-4);  // Very low density
    plasma->setIonizationLevel(1.0);          // Fully ionized
    plasma->setElectronDensity(1.0e20);       // High electron density
    plasma->setPlasmaFrequency(1.0e15);       // Very high
    plasma->setElectricalConductivity(1.0e7); // Highly conductive
    plasma->setThermalConductivity(100.0);    // High thermal conductivity 
    plasma->setSpecificHeat(20000.0);         // Very high heat capacity
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createNeonPlasma() {
    auto plasma = std::make_shared<PlasmaMaterial>("Neon Plasma", 0.9);
    plasma->setIonizationLevel(0.1);          // 10% ionized
    plasma->setElectronDensity(1.0e18);       // Moderate
    plasma->setPlasmaFrequency(2.8e11);       // Hz
    plasma->setElectricalConductivity(5.0e3); // Moderate conductivity
    plasma->setThermalConductivity(0.05);     // W/(m·K)
    plasma->setSpecificHeat(1000.0);          // J/(kg·K)
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createArgonPlasma() {
    auto plasma = std::make_shared<PlasmaMaterial>("Argon Plasma", 1.78);
    plasma->setIonizationLevel(0.15);         // 15% ionized
    plasma->setElectronDensity(5.0e18);       // Moderate-high
    plasma->setPlasmaFrequency(3.2e11);       // Hz
    plasma->setElectricalConductivity(8.0e3); // Good conductivity
    plasma->setThermalConductivity(0.02);     // Poor thermal conductor
    plasma->setSpecificHeat(520.0);           // J/(kg·K)
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createHydrogenPlasma() {
    auto plasma = std::make_shared<PlasmaMaterial>("Hydrogen Plasma", 0.09);
    plasma->setIonizationLevel(0.95);         // Nearly fully ionized
    plasma->setElectronDensity(1.0e19);       // High
    plasma->setPlasmaFrequency(5.0e11);       // Hz
    plasma->setElectricalConductivity(1.0e4); // Good conductor
    plasma->setThermalConductivity(0.18);     // W/(m·K)
    plasma->setSpecificHeat(14300.0);         // Very high specific heat
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createHeliumPlasma() {
    auto plasma = std::make_shared<PlasmaMaterial>("Helium Plasma", 0.18);
    plasma->setIonizationLevel(0.8);          // 80% ionized
    plasma->setElectronDensity(8.0e18);       // High
    plasma->setPlasmaFrequency(4.0e11);       // Hz
    plasma->setElectricalConductivity(9.0e3); // Good conductor
    plasma->setThermalConductivity(0.15);     // W/(m·K)
    plasma->setSpecificHeat(5193.0);          // J/(kg·K)
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createXenonPlasma() {
    auto plasma = std::make_shared<PlasmaMaterial>("Xenon Plasma", 5.9);
    plasma->setIonizationLevel(0.3);          // 30% ionized
    plasma->setElectronDensity(2.0e18);       // Moderate
    plasma->setPlasmaFrequency(2.5e11);       // Hz
    plasma->setElectricalConductivity(3.0e3); // Moderate conductivity
    plasma->setThermalConductivity(0.006);    // Poor thermal conductor
    plasma->setSpecificHeat(160.0);           // Low specific heat
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createMercuryPlasma() {
    auto plasma = std::make_shared<PlasmaMaterial>("Mercury Plasma", 13.6);
    plasma->setIonizationLevel(0.25);         // 25% ionized
    plasma->setElectronDensity(1.5e18);       // Moderate
    plasma->setPlasmaFrequency(2.2e11);       // Hz
    plasma->setElectricalConductivity(1.0e4); // Good conductor
    plasma->setThermalConductivity(0.01);     // Poor thermal conductor
    plasma->setSpecificHeat(140.0);           // J/(kg·K)
    return plasma;
}

std::shared_ptr<PlasmaMaterial> PlasmaMaterials::createPlasmaJet() {
    auto plasma = std::make_shared<PlasmaMaterial>("Plasma Jet", 0.5);
    plasma->setIonizationLevel(0.9);          // 90% ionized
    plasma->setElectronDensity(1.0e20);       // Very high
    plasma->setPlasmaFrequency(5.6e11);       // Hz
    plasma->setElectricalConductivity(2.0e5); // Excellent conductor
    plasma->setThermalConductivity(5.0);      // Good thermal conductor
    plasma->setSpecificHeat(10000.0);         // Very high heat capacity
    return plasma;
}

} // namespace archimedes3d
