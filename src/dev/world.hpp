#pragma once
#include "cell.hpp"
#include "terrain_type.hpp"
#include "terrain_mod.hpp"
#include "speed.hpp"
#include "direction.hpp"
#include "image_matrix.hpp"

class World {
    bool valid;
    const ImageMatrix<TerrainType> tt;
    const ImageMatrix<TerrainMod> tm;
    const ImageMatrix<Speed> speed;
    const ImageMatrix<Direction> dir;
    const int sec_per_step;
    const int feet_per_cell;
    // cm

public:
    World(): valid(false), sec_per_step(0), feet_per_cell(0) {}
    World(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_mph, const Ref<Image> p_dir, int p_sec_per_step, int p_feet_per_cell): 
        valid(true), sec_per_step(p_sec_per_step), feet_per_cell(p_feet_per_cell),
        tt(p_tt), tm(p_tm), speed(p_mph), dir(p_dir) {}
    bool is_valid() const { return valid; }
    bool is_invalid() const { return !is_valid(); }
    const TerrainType get_tt(const Cell& cell) const { return tt.get_tt(cell); }
    const TerrainMod get_tm(const Cell& cell) const { return tm.get_tm(cell); }
    const Speed get_speed(const Cell& cell) const { return speed.get_speed(cell, sec_per_step, feet_per_cell); }
    const Direction get_dir(const Cell& cell) const { return dir.get_dir(cell); }
    bool can_walk_at(const Cell& cell) const { return get_tt(cell).can_walk(); }
    bool can_drive_at(const Cell& cell) const { return get_tt(cell).can_drive(); }
};