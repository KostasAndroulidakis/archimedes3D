# Archimedes 3D Physics Engine

A physics engine based on density and buoyancy rather than traditional gravity.

## Core Concept

Archimedes reframes gravitational forces as buoyancy effects based on density differences:
- Objects denser than the surrounding medium sink
- Objects less dense than the surrounding medium rise
- Motion is determined by relative densities, not by gravitational constants

## Project Structure

- `src/core`: Engine core and simulation loop
- `src/physics`: Physics calculations and object representations
- `src/environment`: Media definitions (air, water, etc.)
- `src/math`: Mathematical utilities
- `src/utils`: Helper functions and configuration

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running Examples

After building, run the buoyancy demo:
```bash
./BuoyancyDemo
```

## Roadmap

- [x] Basic 2D prototype with buoyancy simulation
- [ ] Full 3D implementation
- [ ] Atmospheric layers of the earth
- [ ] Pressure systems
- [ ] Electromagnetic fields
- [ ] Plasma physics
