#pragma once
#include <godot_cpp/classes/image.hpp>
#include "base_world.hpp"
#include "connectivity_matrix.hpp"

using namespace godot;

struct World: public BaseWorld {
    ConnectivityMatrix cm;
    World() {};
    World(const Ref<InputPackage> input);
};