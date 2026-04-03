#pragma once
#include <iostream>

struct vec2 {
    float x, y;

    constexpr vec2 operator+(const vec2& otro) const {
        return vec2{x + otro.x, y + otro.y};
    }

    constexpr vec2 operator-(const vec2& otro) const {
        return vec2{x - otro.x, y - otro.y};
    }

    constexpr vec2 operator+=(const vec2& otro) {
        x += otro.x;
        y += otro.y;
        return *this;
    }

};

constexpr vec2 operator*(const vec2& vec, float escalar) {
    return vec2{vec.x * escalar, vec.y * escalar};
}

constexpr vec2 operator*(float escalar, const vec2& vec) {
    return vec * escalar;
}

inline std::ostream& operator<<(std::ostream& os, const vec2& vec) {
    os << "[X: " << vec.x << ", Y: " << vec.y << "]";
    return os;
}