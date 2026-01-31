#pragma once
#include <godot_cpp/classes/image.hpp>
#include "base_world.hpp"
#include "connectivity_matrix.hpp"

using namespace godot;

class World: public BaseWorld {
    ConnectivityMatrix cm;
public:
    World() {};
    World(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_mph, const Ref<Image> p_dir, int p_sec_per_step, int p_feet_per_cell); 
};