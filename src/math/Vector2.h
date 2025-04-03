#pragma once

#include "../utils/Constants.h"

namespace Archimedes {

class Vector2 {
public:
    float x, y;
    
    Vector2() : x(Constants::Math::VECTOR_DEFAULT_X), y(Constants::Math::VECTOR_DEFAULT_Y) {}
    Vector2(float x, float y) : x(x), y(y) {}
    
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    float magnitude() const;
    Vector2 normalized() const;
};

} // namespace Archimedes