#pragma once

/**
 * Master include file for all constants used in the Archimedes engine.
 * Include this file to access all constants or include specific constant files
 * for better granularity and reduced dependencies.
 */

// IWYU pragma: begin_exports
#include "PhysicsConstants.h"
#include "MaterialConstants.h"
#include "AtmosphereConstants.h"
#include "EnvironmentConstants.h"
#include "SimulationConstants.h"
#include "MathConstants.h"
// IWYU pragma: end_exports

// This header is a convenience file that includes all constants.
// For more granular control and better compile-time dependencies,
// consider including only the specific constants files your module needs.
