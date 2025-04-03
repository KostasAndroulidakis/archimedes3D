#include "Engine.h"

namespace Archimedes {

Engine::Engine() : m_initialized(false) {
}

bool Engine::initialize() {
    m_world = std::make_shared<World>();
    m_initialized = true;
    return true;
}

void Engine::step(float deltaTime) {
    if (!m_initialized) {
        return;
    }
    
    m_world->update(deltaTime);
}

} // namespace Archimedes