#include "agents.h"
#include "world.h"
using namespace godot;

Agents::Agents(): 
    valid(false),
    {}

Agents::Agents(const World& p_world, int num_humans, float ownership): 
    valid(true),
    world(p_world),
    agents_img(Image::create(p_world.cols, p_world.rows, false, Image::FORMAT_RGBA8)), 
    {
        
    // humans
    // pvs

}

Agents::~Agents() {
}

void Agents::set_destinations() {
    // implementation
}

void Agents::set_navseqs() {
    // implementation
}

void Agents::step() {
    // implementation
}

Ref<Image> Agents::get_agents_img() const {
    return agents_img;
}
