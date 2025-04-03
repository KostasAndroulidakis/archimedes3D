#include "Pressure.h"

namespace Archimedes {

float Pressure::calculateHydrostaticPressure(float depth, float fluidDensity) {
    const float g = 9.8f; // Displacement constant
    return depth * fluidDensity * g;
}

float Pressure::calculatePressureDifference(float pressure1, float pressure2) {
    return pressure1 - pressure2;
}

float Pressure::calculateForce(float pressure, float area) {
    return pressure * area;
}

float Pressure::calculateVolumeChange(float initialVolume, float initialPressure, 
                                    float finalPressure, float temperature) {
    // Using ideal gas law: P1V1 = P2V2 (at constant temperature)
    // Therefore V2 = V1 * (P1/P2)
    return initialVolume * (initialPressure / finalPressure);
}

} // namespace Archimedes