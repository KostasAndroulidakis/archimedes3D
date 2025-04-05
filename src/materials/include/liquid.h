#pragma once

#include <string>
#include <memory>
#include <functional>

namespace archimedes3d {

/**
 * @class Liquid
 * @brief Represents liquid materials in the Archimedes3D physics engine.
 * 
 * Liquids are characterized by their density, viscosity, surface tension,
 * and how they respond to temperature and pressure.
 */
class Liquid {
public:
    /**
     * @brief Construct a new Liquid object with specified properties
     * 
     * @param density Density in kg/m³
     * @param viscosity Dynamic viscosity in Pa·s
     * @param surfaceTension Surface tension in N/m
     * @param name Human-readable name of the liquid
     * @param conductivity Electrical conductivity in S/m
     * @param thermalExpansionCoeff Thermal expansion coefficient in K⁻¹
     */
    Liquid(double density, 
           double viscosity, 
           double surfaceTension, 
           const std::string& name,
           double conductivity = 0.0,
           double thermalExpansionCoeff = 0.0);

    /**
     * @brief Get the density at specified temperature and pressure
     * 
     * @param temperature Temperature in Kelvin (default = 293.15K or 20°C)
     * @param pressure Pressure in Pascal (default = 101325 Pa or 1 atm)
     * @return double Density in kg/m³
     */
    double getDensity(double temperature = 293.15, double pressure = 101325.0) const;

    /**
     * @brief Get the viscosity at specified temperature
     * 
     * @param temperature Temperature in Kelvin (default = 293.15K or 20°C)
     * @return double Dynamic viscosity in Pa·s
     */
    double getViscosity(double temperature = 293.15) const;

    /**
     * @brief Get the surface tension at specified temperature
     * 
     * @param temperature Temperature in Kelvin (default = 293.15K or 20°C)
     * @return double Surface tension in N/m
     */
    double getSurfaceTension(double temperature = 293.15) const;

    /**
     * @brief Get the electrical conductivity
     * 
     * @return double Conductivity in S/m
     */
    double getConductivity() const;

    /**
     * @brief Get the name of the liquid
     * 
     * @return const std::string& Name of the liquid
     */
    const std::string& getName() const;

    /**
     * @brief Calculate buoyant force on an object
     * 
     * @param volume Volume of the submerged object in m³
     * @param accelerationConstant Fundamental acceleration constant (a₀) in m/s²
     * @return double Buoyant force in Newtons
     */
    double calculateBuoyantForce(double volume, double accelerationConstant = 9.8) const;

private:
    double m_density;                  ///< Base density in kg/m³ (at 20°C, 1 atm)
    double m_viscosity;                ///< Dynamic viscosity in Pa·s
    double m_surfaceTension;           ///< Surface tension in N/m
    double m_conductivity;             ///< Electrical conductivity in S/m
    double m_thermalExpansionCoeff;    ///< Thermal expansion coefficient in K⁻¹
    std::string m_name;                ///< Human-readable name
};

} // namespace archimedes3d
