#include "world.hpp"
#include "../input_package.hpp"

World::World(const Ref<InputPackage> input):
    BaseWorld(input) {
    cm = ConnectivityMatrix(*this);
} 



