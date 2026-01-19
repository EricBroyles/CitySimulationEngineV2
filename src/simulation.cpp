#include "simulation.h"
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/texture_rect.hpp>

using namespace godot;

void Simulation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("setup", "p_step_duration", "p_cell_width", "p_num_steps"), &Simulation::setup);
    ClassDB::bind_method(D_METHOD("set_world", "tt", "tm", "dir", "mph"), &Simulation::set_world);
    ClassDB::bind_method(D_METHOD("set_agents", "num_humans", "personal_vehicle_ownership"), &Simulation::set_agents);
    ClassDB::bind_method(D_METHOD("is_done"), &Simulation::is_done);
    ClassDB::bind_method(D_METHOD("step"), &Simulation::step);
    ClassDB::bind_method(D_METHOD("is_valid"), &Simulation::is_valid);
}

Simulation::Simulation(): 
    valid(false), 
    step_duration(1), 
    cell_width(10), 
    current_step(0), 
    num_steps(0), 
    world(World()), 
    agents(Agents()) {}

Simulation::~Simulation() {
    //custom cleanup here
}

void Simulation::setup(int p_step_duration, int p_cell_width, int p_num_steps) {
    valid = true;
    step_duration = p_step_duration;
    cell_width = p_cell_width;
    num_steps = p_num_steps;
}

void Simulation::set_world(const Ref<Image> tt, const Ref<Image> tm, const Ref<Image> dir, const Ref<Image> mph) {
    world = World(tt, tm, dir, mph);
}

void Simulation::set_agents(int num_humans, float personal_vehicle_ownership) {
    agents = Agents(world, num_humans, personal_vehicle_ownership);
    agents.set_destinations();
    agents.set_navseqs();
}

bool Simulation::is_valid() const {
    return valid;
}

bool Simulation::is_done() const {
    return current_step >= num_steps;
}

void Simulation::step() {
    print_line(vformat("Step: %d", current_step));
    agents.step();
    current_step += 1;
}

Ref<Image> Simulation::get_agents_img() {
    return agents.get_agents_img();
}




