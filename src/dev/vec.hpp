#pragma once

struct Vec2i {
    int x, y;
    constexpr Vec2i(): x(0), y(0) {}
    constexpr Vec2i(int px, int py): x(px), y(py) {}
    constexpr bool operator==(const Vec2i rhs) const { return x == rhs.x && y == rhs.y; }
    constexpr bool operator!=(const Vec2i rhs) const { return x != rhs.x || y != rhs.y; }
    constexpr Vec2i& operator+=(const Vec2i rhs) { x += rhs.x; y += rhs.y; return *this; }
    constexpr Vec2i& operator-=(const Vec2i rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    friend constexpr Vec2i operator+(Vec2i lhs, const Vec2i rhs) { return lhs += rhs; }
    friend constexpr Vec2i operator-(Vec2i lhs, const Vec2i rhs) { return lhs -= rhs; }
};


