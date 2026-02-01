#pragma once
#include <godot_cpp/classes/image.hpp>
#include "cell.hpp"
#include "terrain_type.hpp"
#include "terrain_mod.hpp"
#include "speed.hpp"
#include "direction.hpp"
#include "image_matrix.hpp"

using namespace godot;

class BaseWorld {
    const ImageMatrix<TerrainType> tt;
    const ImageMatrix<TerrainMod> tm;
    const ImageMatrix<Speed> speed;
    const ImageMatrix<Direction> dir;
    const int sec_per_step;
    const int feet_per_cell;
    bool valid;
public:
    int cols, rows;
    BaseWorld();
    BaseWorld(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_mph, const Ref<Image> p_dir, int p_sec_per_step, int p_feet_per_cell);
    bool is_valid() const { return valid; }
    bool is_invalid() const { return !is_valid(); }
    bool in_bounds(const Cell cell) const { return cell.in_bounds(0,0,cols-1,rows-1); }
    bool out_of_bounds(const Cell cell) const { return !in_bounds(cell); }
    const TerrainType get_tt(const Cell cell) const { return tt.get_tt(cell); }
    const TerrainMod get_tm(const Cell cell) const { return tm.get_tm(cell); }
    const Speed get_speed(const Cell cell) const { return speed.get_speed(cell, sec_per_step, feet_per_cell); }
    const Direction get_dir(const Cell cell) const { return dir.get_dir(cell); }
    bool can_walk_at(const Cell cell) const { return get_tt(cell).can_walk(); }
    bool can_drive_at(const Cell cell) const { return get_tt(cell).can_drive(); }

    //emulate user data
    static Ref<Image> emulate_image_r8(int cols, int rows, uint8_t fill, std::vector<uint8_t> pop); 
};