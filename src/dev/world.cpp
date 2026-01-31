#include "world.hpp"

World::World(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_mph, const Ref<Image> p_dir, int p_sec_per_step, int p_feet_per_cell):
    BaseWorld(p_tt, p_tm, p_mph, p_dir, p_sec_per_step, p_feet_per_cell) {
    cm = ConnectivityMatrix(*this);
} 



