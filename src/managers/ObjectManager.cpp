#include "ObjectManager.h"
#include "../environment/Medium.h"

namespace Archimedes {

ObjectManager::ObjectManager() {}

void ObjectManager::addObject(std::shared_ptr<PhysicsObject> object) {
    m_objects.push_back(object);
}

void ObjectManager::updateObjects(float deltaTime, const Medium& medium) {
    for (auto& object : m_objects) {
        object->update(deltaTime, medium);
    }
}

} // namespace Archimedes