#pragma once
#include "vec.hpp"

class Cell {
    Vec2i pos;
    static constexpr int INVALID = -1;
    
public:
    constexpr Cell(): pos(INVALID, INVALID) {}
    constexpr Cell(int px, int py): pos(px, py) {}
    constexpr Cell(Vec2i v): pos(v) {}
    constexpr Cell(const Cell& cell, int resolution): pos(cell.pos.x / resolution, cell.pos.y / resolution) {}
    constexpr int x() const { return pos.x; }
    constexpr int y() const { return pos.y; }
    constexpr bool is_valid() const { return pos.x >= 0 && pos.y >= 0; }
    constexpr bool is_invalid() const { return !is_valid(); }
    void invalidate() { pos.x = INVALID; pos.y = INVALID; }
    constexpr bool in_bounds(int lbx, int lby, int ubx, int uby) const { return pos.x >= lbx && pos.x <= ubx && pos.y >= lby && pos.y <= uby; }
    constexpr bool operator==(const Cell& rhs) const { return pos == rhs.pos; }
    constexpr bool operator!=(const Cell& rhs) const { return pos != rhs.pos; }
    Cell& operator+=(const Cell& rhs) { pos += rhs.pos; return *this; }
    Cell& operator+=(const Vec2i& rhs) { pos += rhs; return *this; }
    friend Cell operator+(Cell lhs, const Cell& rhs) { return lhs += rhs; }
    friend Cell operator+(Cell lhs, const Vec2i& rhs) { return lhs += rhs; }
    friend Cell operator+(const Vec2i& lhs, Cell rhs) { rhs += lhs; return rhs; }
    constexpr Vec2i to_vec2i() const { return pos; }
    constexpr operator Vec2i() const { return pos; }  // Implicit conversion to Vec2i
};