#include "Vector2.h"
#include <cmath>
#include "../constants/Constants.h"

namespace Archimedes {

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const {
    float mag = magnitude();
    if (mag > Constants::Physics::EPSILON) {
        return Vector2(x / mag, y / mag);
    }
    return Vector2();
}

} // namespace Archimedes