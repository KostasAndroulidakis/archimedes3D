#include "../include/material.h"

namespace archimedes3d {

// Material base class implementation
Material::Material() 
    : density(0.0)
    , electricalConductivity(0.0)
    , magneticPermeability(1.0) // Default to vacuum permeability
    , thermalConductivity(0.0)
    , specificHeat(0.0)
    , name("Unnamed Material") 
{
}

Material::Material(const std::string& name, double density)
    : density(density)
    , electricalConductivity(0.0)
    , magneticPermeability(1.0)
    , thermalConductivity(0.0)
    , specificHeat(0.0)
    , name(name)
{
}

double Material::calculateBuoyantForce(double volume, const Medium& medium) const {
    // Implementation will depend on Medium class definition
    // Archimedes principle: F_b = ρ_fluid × V × a₀
    // This is just a placeholder - will be implemented later
    return 0.0;
}

// SolidMaterial implementation
SolidMaterial::SolidMaterial()
    : Material()
    , elasticity(0.0)
    , tensileStrength(0.0)
    , hardness(0.0)
{
}

SolidMaterial::SolidMaterial(const std::string& name, double density)
    : Material(name, density)
    , elasticity(0.0)
    , tensileStrength(0.0)
    , hardness(0.0)
{
}

// LiquidMaterial implementation
LiquidMaterial::LiquidMaterial()
    : Material()
    , viscosity(0.0)
    , surfaceTension(0.0)
    , freezingPoint(0.0)
{
}

LiquidMaterial::LiquidMaterial(const std::string& name, double density)
    : Material(name, density)
    , viscosity(0.0)
    , surfaceTension(0.0)
    , freezingPoint(0.0)
{
}

// GasMaterial implementation
GasMaterial::GasMaterial()
    : Material()
    , compressionFactor(1.0) // Ideal gas by default
    , expansionCoefficient(0.0)
{
}

GasMaterial::GasMaterial(const std::string& name, double density)
    : Material(name, density)
    , compressionFactor(1.0)
    , expansionCoefficient(0.0)
{
}

// PlasmaMaterial implementation
PlasmaMaterial::PlasmaMaterial()
    : Material()
    , ionizationLevel(0.0)
    , electronDensity(0.0)
    , plasmaFrequency(0.0)
{
}

PlasmaMaterial::PlasmaMaterial(const std::string& name, double density)
    : Material(name, density)
    , ionizationLevel(0.0)
    , electronDensity(0.0)
    , plasmaFrequency(0.0)
{
}

} // namespace archimedes3d
