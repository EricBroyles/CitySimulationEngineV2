#pragma once
#include <godot_cpp/classes/image.hpp>
#include "cell.hpp"
#include "terrain_type.hpp"
#include "terrain_mod.hpp"
#include "speed.hpp"
#include "direction.hpp"
#include "matrix.hpp"
#include "../input_package.hpp"

using namespace godot;

class BaseWorld {
    const Matrix<TT> tt;
    const Matrix<TM> tm;
    const Matrix<Dir> dir;
    const Matrix<Speed> speed;
    const int sec_per_step;
    const int feet_per_cell;
    bool valid;
public:
    int cols, rows;
    BaseWorld();
    BaseWorld(const Ref<InputPackage> input);
    bool is_valid() const { return valid; }
    bool is_invalid() const { return !is_valid(); }
    bool in_bounds(const Cell cell) const { return cell.in_bounds(0,0,cols-1,rows-1); }
    bool out_of_bounds(const Cell cell) const { return !in_bounds(cell); }
    const TerrainType get_tt(const Cell cell) const { return tt.at(cell); }
    const TerrainMod get_tm(const Cell cell) const { return tm.at(cell); }
    const Speed get_speed(const Cell cell) const { return speed.at(cell); }
    const Direction get_dir(const Cell cell) const { return dir.at(cell); }
    bool can_walk_at(const Cell cell) const { return get_tt(cell).can_walk(); }
    bool can_drive_at(const Cell cell) const { return get_tt(cell).can_drive(); }
};