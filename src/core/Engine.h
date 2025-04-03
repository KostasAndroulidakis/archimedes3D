#pragma once

#include "World.h"
#include <memory>

namespace Archimedes {

class Engine {
public:
    Engine();
    
    // Initialize the engine
    bool initialize();
    
    // Run a single step of the simulation
    void step(float deltaTime);
    
    // Get the world object
    std::shared_ptr<World> getWorld() { return m_world; }
    
private:
    std::shared_ptr<World> m_world;
    bool m_initialized;
};

} // namespace Archimedes