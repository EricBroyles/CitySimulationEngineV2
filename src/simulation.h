#pragma once

#include <godot_cpp/classes/image.hpp>
#include "dev/agents.h"
#include "dev/world.h"

using namespace godot;

/* 
    This is the C++ plugin access point and as a result it cannot have a constructor (godot objects do not have constructors). 
    After each step the agents.agents_img is modified, get this image and use it to update the shader in godot.

    agents_img: rgba8 r(agent type 0 -> 255) g(agent state 0 -> 255) 
    tt, tm, dir, mph, agents_img are all the same size.
    step modifies the agents_img which should be used in godot to update a texture for a shader

    godot:
    sim = Simulation.new()
    sim.setup(...)
    sim.set_world(...)
    sim.set_agents(.,.)
    sim.step()
    sim.get_agents_img
    # update the texture with the agents image
*/

class Simulation : public RefCounted {
    GDCLASS(Simulation, RefCounted);

private:
    bool valid;
    int step_duration; // SECONDS | amount of in game time each step takes
    int cell_width;    // FEET  
    int current_step;  // [0 num_steps)
    int num_steps;     
    const World world;
    Agents agents;

protected:
    static void _bind_methods(); 

public: 
    Simulation();
    ~Simulation();
    bool is_valid() const { return valid; }
    void setup(int step_duration, int cell_width, int num_steps);
    void set_world(const Ref<Image> tt, const Ref<Image> tm, const Ref<Image> dir, const Ref<Image> mph);
    void set_agents(int num_humans, float personal_vehicle_ownership);
    bool is_done() const { return current_step >= num_steps; }
    Ref<Image> get_agents_img();
    void step();
};