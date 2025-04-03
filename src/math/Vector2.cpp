#include "Vector2.h"
#include <cmath>

namespace Archimedes {

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const {
    float mag = magnitude();
    if (mag > 0.0f) {
        return Vector2(x / mag, y / mag);
    }
    return Vector2();
}

} // namespace Archimedes