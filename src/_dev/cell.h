// #pragma once

// using namespace godot;

// struct Cell {
//     static constexpr int NUM_ADJACENT = 8;
//     size_t x;
//     size_t y;
//     Cell(): x(-1), y(-1) {}
//     Cell(size_t px, size_t py): x(px), y(py) {}
//     Cell(const Cell& cell, int resolution): x(cell.x/resolution), y(cell.y/resolution) {} //lower resolution
//     Cell(const Cell& cell, size_t px, size_t py): x(cell.x+px), y(cell.y+py) {}
//     bool is_valid() const {return (x >= 0) && (y >= 0);}
//     void invalid() {x(-1); y(-1);}
//     bool in_bounds(size_t lbx, size_t lby, size_t ubx, size_t uby) {
//         if (x < lbx || x > ubx) {return false;}
//         if (y < lby || y > uby) {return false;}
//         return true;
//     }
//     size_t get_rowwise_idx(size_t cols) {return y * cols + c;}
//     Cell get_adjacent(const SoloDirection& solo_dir) const {
//         Vec2i vec = solo_dir.get_vector();
//         return Cell(x+vec.x, y+vec.y);
//     }
//     bool operator==(const Cell& other) const {return x == other.x && y == other.y;}
//     Cell operator+(const Vec2i& other) const {Cell(x + other.x, y + other.y);}
//     Cell operator+(const Cell& other)  const {Cell(x + other.x, y + other.y);}
// };

// struct Vec2i {
//     int x;
//     int y;
//     Vec2i(): x(0), y(0) {}
//     Vec2i(int px, int py): x(px), y(py) {}
// }
