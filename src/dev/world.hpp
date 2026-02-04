#pragma once
#include <godot_cpp/classes/image.hpp>
#include "base_world.hpp"
#include "connectivity_matrix.hpp"

using namespace godot;

class World: public BaseWorld {
    ConnectivityMatrix cm;
public:
    World() {};
    World(const Ref<InputPackage> input);
};