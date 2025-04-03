#pragma once

#include "PhysicsObject.h"
#include "../math/Vector2.h"
#include "../constants/MaterialConstants.h"
#include "../constants/SimulationConstants.h"
#include "../core/World.h"
#include "../managers/ObjectManager.h"
#include <memory>
#include <string>
#include <vector>

namespace Archimedes {

/**
 * Factory class for creating common physics objects with standard properties
 */
class ObjectFactory {
public:
    /**
     * Create a standard physics object
     * 
     * @param type The type of object to create ("stone", "wood", "balloon", etc)
     * @param position The initial position
     * @return A shared pointer to the created physics object
     */
    static std::shared_ptr<PhysicsObject> createStandardObject(const std::string& type, const Vector2& position) {
        if (type == "stone" || type == "Stone") {
            return std::make_shared<PhysicsObject>(
                Constants::Materials::TestObjects::STONE_MASS,
                Constants::Materials::TestObjects::STONE_VOLUME,
                position
            );
        }
        else if (type == "wood" || type == "Wood") {
            return std::make_shared<PhysicsObject>(
                Constants::Materials::TestObjects::WOOD_MASS,
                Constants::Materials::TestObjects::WOOD_VOLUME,
                position
            );
        }
        else if (type == "balloon" || type == "Balloon") {
            return std::make_shared<PhysicsObject>(
                Constants::Materials::TestObjects::BALLOON_MASS,
                Constants::Materials::TestObjects::BALLOON_VOLUME,
                position
            );
        }
        else if (type == "largeBalloon" || type == "LargeBalloon") {
            return std::make_shared<PhysicsObject>(
                Constants::Materials::TestObjects::LARGE_BALLOON_MASS,
                Constants::Materials::TestObjects::LARGE_BALLOON_VOLUME,
                position
            );
        }
        
        // Default case: return a generic object
        return std::make_shared<PhysicsObject>(1.0f, 0.001f, position);
    }
    
    /**
     * Create standard test objects at default positions
     * 
     * @param world The world to add the objects to
     * @return Vector of created objects
     */
    static std::vector<std::shared_ptr<PhysicsObject>> createStandardTestSet(std::shared_ptr<World> world) {
        std::vector<std::shared_ptr<PhysicsObject>> objects;
        
        // Create standard objects
        auto stone = createStandardObject("stone", 
            Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT1, Constants::Simulation::INITIAL_Y_POSITION));
        
        auto wood = createStandardObject("wood",
            Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT2, Constants::Simulation::INITIAL_Y_POSITION));
        
        auto balloon = createStandardObject("balloon",
            Vector2(Constants::Simulation::INITIAL_X_POSITION_OBJECT3, Constants::Simulation::INITIAL_Y_POSITION));
        
        // Add to world if provided
        if (world) {
            world->getObjectManager()->addObject(stone);
            world->getObjectManager()->addObject(wood);
            world->getObjectManager()->addObject(balloon);
        }
        
        // Add to return vector
        objects.push_back(stone);
        objects.push_back(wood);
        objects.push_back(balloon);
        
        return objects;
    }
};

} // namespace Archimedes