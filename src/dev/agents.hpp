// work in progress

#pragma once
#include "idx.hpp"
#include "input.hpp"
#include "world.hpp"
#include "humans.hpp"
#include "personal_vehicle.hpp"


//How to assign Cars <-> Humans
//How to assign initial space for parking and buildng for people (inside class)
//How to allow

class Agents {
    Humans humans;
    PersonalVehicles pvs;
    int human_step_every_x_steps;
    int pv_step_every_x_steps;


public:
    Agents(const InputPackage& input, const World& world): 
        humans(input, world), 
        pvs(input, world),
        human_step_every_x_steps(input->human_step_every_x_steps),
        pv_step_every_x_steps(input->pv_step_every_x_steps),
        {}
    void step(int curr_step) {


    }
};