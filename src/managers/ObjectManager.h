#pragma once

#include <vector>
#include <memory>
#include "../physics/PhysicsObject.h"

namespace Archimedes {

class ObjectManager {
public:
    ObjectManager();
    
    // Add object to the world
    void addObject(std::shared_ptr<PhysicsObject> object);
    
    // Update physics for all objects
    void updateObjects(float deltaTime, const class Medium& medium);
    
    // Get all objects
    const std::vector<std::shared_ptr<PhysicsObject>>& getObjects() const { return m_objects; }
    
private:
    std::vector<std::shared_ptr<PhysicsObject>> m_objects;
};

} // namespace Archimedes