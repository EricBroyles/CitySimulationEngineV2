#include "base_world.hpp"
#include "../input_package.hpp"

using namespace godot;

BaseWorld::BaseWorld(): valid(false), cols(0), rows(0), sec_per_step(0), feet_per_cell(0) {}

BaseWorld::BaseWorld(const Ref<InputPackage> input):
    valid(true),
    cols(input->get_cols()), 
    rows(input->get_rows()),
    sec_per_step(input->get_sec_per_step()), 
    feet_per_cell(input->get_feet_per_cell()),
    tt(input->get_tt()), 
    tm(input->get_tm()), 
    dir(input->get_dir()), 
    speed(input->get_mph(), input->get_sec_per_step(), input->get_feet_per_cell()),
    avg_walk_speed(input->get_avg_walk_speed()), 
    avg_drive_speed(input->get_avg_drive_speed()) {}
