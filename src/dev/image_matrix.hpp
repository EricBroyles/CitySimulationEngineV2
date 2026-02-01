/*
@brief
* wraps a godot image to make it easier to interact with in C++ and to give it a more useful type
*/
#pragma once
#include <type_traits>
#include <godot_cpp/classes/image.hpp>
#include "cell.hpp"
#include "terrain_type.hpp"
#include "terrain_mod.hpp"
#include "speed.hpp"
#include "direction.hpp"

using namespace godot;

template <typename T> class ImageMatrix {
    Ref<Image> data;
public:
    int cols, rows;
    ImageMatrix(): cols(0), rows(0) {}
    ImageMatrix(const Ref<Image> img): cols(img->get_width()), rows(img->get_height()), data(img) {}
    const uint8_t get_r8(const Cell cell) const { return data->get_pixel(cell.x,cell.y).r * 255; }
    const TerrainType get_tt(const Cell cell) const requires std::is_same_v<T, TerrainType> { 
        return TerrainType(get_r8(cell)); }
    const TerrainMod get_tm(const Cell cell) const requires std::is_same_v<T, TerrainMod> { 
        return TerrainMod(get_r8(cell)); }
    const Speed get_speed(const Cell cell, int sec_per_step, int feet_per_cell) const requires std::is_same_v<T, Speed> { 
        return Speed(get_r8(cell), sec_per_step, feet_per_cell); }
    const Direction get_dir(const Cell cell) const requires std::is_same_v<T, Direction> { 
        return Direction(get_r8(cell)); }

    // this will also get setters for the agents, give it type Agents. 
    // the require removes the code for the versions that dont meet those reqs. 
    // set_agent()

};

