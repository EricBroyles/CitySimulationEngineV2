#pragma once
#include "vec.hpp"

struct Cell {
    int x, y;
    static constexpr int INVALID = -1;
    
    constexpr Cell(): x(INVALID), y(INVALID) {}
    constexpr Cell(int px, int py): x(px), y(py) {}
    constexpr Cell(Vec2i v): x(v.x), y(v.y) {}
    constexpr Cell(const Cell& cell, int resolution): x(cell.x / resolution), y(cell.y / resolution) {}
    constexpr int to_idx(int cols) const { return y * cols + x; }
    constexpr bool is_valid() const { return x >= 0 && y >= 0; }
    constexpr bool is_invalid() const { return !is_valid(); }
    void invalidate() { x = INVALID; y = INVALID; }
    constexpr bool in_bounds(int lbx, int lby, int ubx, int uby) const { return x >= lbx && x <= ubx && y >= lby && y <= uby; }
    constexpr bool operator==(const Cell& rhs) const { return x == rhs.x && y == rhs.y; }
    constexpr bool operator!=(const Cell& rhs) const { return !(*this == rhs); }
    Cell& operator+=(const Cell& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Cell& operator+=(const Vec2i& rhs) { x += rhs.x; y += rhs.y; return *this; }
    friend Cell operator+(Cell lhs, const Cell& rhs) { return lhs += rhs; }
    friend Cell operator+(Cell lhs, const Vec2i& rhs) { return lhs += rhs; }
    friend Cell operator+(const Vec2i& lhs, Cell rhs) { rhs += lhs; return rhs; }
    constexpr Vec2i to_vec2i() const { return Vec2i(x, y); }
    constexpr operator Vec2i() const { return Vec2i(x, y); }
};