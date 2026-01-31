// #pragma once
// #include <array>
// #include <godot_cpp/classes/image.hpp>
// #include "cell.hpp"
// #include "terrain_type.hpp"
// #include "terrain_mod.hpp"
// #include "speed.hpp"
// #include "direction.hpp"
// #include "image_matrix.hpp"
// #include "matrix.hpp"
// #include "cmid.hpp"

// using namespace godot;

// class World {
//     bool valid;
//     static constexpr int CM_CHECK_DIRS = 4;
//     static constexpr std::array<SoloDirection, CM_CHECK_DIRS> CM_UP_DIRS = {SoloDirection(Direction::NW), SoloDirection(Direction::N), SoloDirection(Direction::NE), SoloDirection(Direction::W)};
//     static constexpr std::array<SoloDirection, CM_CHECK_DIRS> CM_DOWN_DIRS = {SoloDirection(Direction::SE), SoloDirection(Direction::S), SoloDirection(Direction::SW), SoloDirection(Direction::E)};
//     const ImageMatrix<TerrainType> tt;
//     const ImageMatrix<TerrainMod> tm;
//     const ImageMatrix<Speed> speed;
//     const ImageMatrix<Direction> dir;
//     const int sec_per_step;
//     const int feet_per_cell;
//     Matrix<CMID> cm_walk;
//     Matrix<CMID> cm_drive;
//     bool is_cm_walk_barrier(const Cell& cell, const Direction& dir) const;
//     bool is_cm_drive_barrier(const Cell& cell, const Direction& dir) const;
//     void set_cm_barriers();
//     void set_cell_cmid(Matrix<CMID>& matrix, const Cell& cell);
//     void set_cmids();

// public:
//     int cols, rows;
//     World();
//     World(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_mph, const Ref<Image> p_dir, int p_sec_per_step, int p_feet_per_cell);
//     bool is_valid() const { return valid; }
//     bool is_invalid() const { return !is_valid(); }
//     bool in_bounds(const Cell& cell) const { return cell.in_bounds(0,0,cols,rows); }
//     bool out_of_bounds(const Cell& cell) const { return !in_bounds(cell); }
//     const TerrainType get_tt(const Cell& cell) const { return tt.get_tt(cell); }
//     const TerrainMod get_tm(const Cell& cell) const { return tm.get_tm(cell); }
//     const Speed get_speed(const Cell& cell) const { return speed.get_speed(cell, sec_per_step, feet_per_cell); }
//     const Direction get_dir(const Cell& cell) const { return dir.get_dir(cell); }
//     bool can_walk_at(const Cell& cell) const { return get_tt(cell).can_walk(); }
//     bool can_drive_at(const Cell& cell) const { return get_tt(cell).can_drive(); }
// };