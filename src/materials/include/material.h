#pragma once

#include <string>

namespace archimedes3d {

// Forward declarations
class Medium;

/**
 * Base Material class - defines common properties for all materials
 */
class Material {
protected:
    // Core properties
    double density;               // kg/m³ - primary property for buoyancy calculations
    
    // Electromagnetic properties
    double electricalConductivity; // S/m
    double magneticPermeability;   // H/m
    
    // Thermal properties
    double thermalConductivity;    // W/(m·K)
    double specificHeat;           // J/(kg·K)
    
    // Identification
    std::string name;
    
public:
    // Constructors
    Material();
    Material(const std::string& name, double density);
    virtual ~Material() = default;
    
    // Core getters/setters
    double getDensity() const { return density; }
    void setDensity(double value) { density = value; }
    
    const std::string& getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }
    
    // EM properties
    double getElectricalConductivity() const { return electricalConductivity; }
    void setElectricalConductivity(double value) { electricalConductivity = value; }
    
    double getMagneticPermeability() const { return magneticPermeability; }
    void setMagneticPermeability(double value) { magneticPermeability = value; }
    
    // Thermal properties
    double getThermalConductivity() const { return thermalConductivity; }
    void setThermalConductivity(double value) { thermalConductivity = value; }
    
    double getSpecificHeat() const { return specificHeat; }
    void setSpecificHeat(double value) { specificHeat = value; }
    
    // Physics calculations
    virtual double calculateBuoyantForce(double volume, const Medium& medium) const;
    
    // State-specific properties (to be overridden)
    virtual bool isSolid() const { return false; }
    virtual bool isLiquid() const { return false; }
    virtual bool isGas() const { return false; }
    virtual bool isPlasma() const { return false; }
};

/**
 * Solid material specific properties
 */
class SolidMaterial : public Material {
protected:
    double elasticity;       // Young's modulus, Pa
    double tensileStrength;  // Pa
    double hardness;         // Mohs scale or similar
    
public:
    SolidMaterial();
    SolidMaterial(const std::string& name, double density);
    
    // Getters/setters
    double getElasticity() const { return elasticity; }
    void setElasticity(double value) { elasticity = value; }
    
    double getTensileStrength() const { return tensileStrength; }
    void setTensileStrength(double value) { tensileStrength = value; }
    
    double getHardness() const { return hardness; }
    void setHardness(double value) { hardness = value; }
    
    // Override from base
    bool isSolid() const override { return true; }
};

/**
 * Liquid material specific properties
 */
class LiquidMaterial : public Material {
protected:
    double viscosity;        // Pa·s
    double surfaceTension;   // N/m
    double freezingPoint;    // K
    
public:
    LiquidMaterial();
    LiquidMaterial(const std::string& name, double density);
    
    // Getters/setters
    double getViscosity() const { return viscosity; }
    void setViscosity(double value) { viscosity = value; }
    
    double getSurfaceTension() const { return surfaceTension; }
    void setSurfaceTension(double value) { surfaceTension = value; }
    
    double getFreezingPoint() const { return freezingPoint; }
    void setFreezingPoint(double value) { freezingPoint = value; }
    
    // Override from base
    bool isLiquid() const override { return true; }
};

/**
 * Gas material specific properties
 */
class GasMaterial : public Material {
protected:
    double compressionFactor;    // Z factor, dimensionless
    double expansionCoefficient;  // 1/K
    
public:
    GasMaterial();
    GasMaterial(const std::string& name, double density);
    
    // Getters/setters
    double getCompressionFactor() const { return compressionFactor; }
    void setCompressionFactor(double value) { compressionFactor = value; }
    
    double getExpansionCoefficient() const { return expansionCoefficient; }
    void setExpansionCoefficient(double value) { expansionCoefficient = value; }
    
    // Override from base
    bool isGas() const override { return true; }
};

/**
 * Plasma material specific properties
 */
class PlasmaMaterial : public Material {
protected:
    double ionizationLevel;    // 0.0-1.0
    double electronDensity;    // particles/m³
    double plasmaFrequency;    // Hz
    
public:
    PlasmaMaterial();
    PlasmaMaterial(const std::string& name, double density);
    
    // Getters/setters
    double getIonizationLevel() const { return ionizationLevel; }
    void setIonizationLevel(double value) { ionizationLevel = value; }
    
    double getElectronDensity() const { return electronDensity; }
    void setElectronDensity(double value) { electronDensity = value; }
    
    double getPlasmaFrequency() const { return plasmaFrequency; }
    void setPlasmaFrequency(double value) { plasmaFrequency = value; }
    
    // Override from base
    bool isPlasma() const override { return true; }
};

} // namespace archimedes3d
