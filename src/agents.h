#pragma once

#include <vector>
#include <godot_cpp/classes/image.hpp>
#include "world.h"
#include "human.h"
#include "personal_vehicle.h"

using namespace godot;

class Agents {

private:  
    bool valid;
    const World& world;
    Ref<Image> agents_img;
    std::vector<Human> humans;
    std::vector<PersonalVehicle> pvs;

    //HANDLE THE AGENTS COLOR IN HERE DONT NEED A SPERATE CLASS
    

public:
    Agents();
    Agents(const World& world, int num_humans, float personal_vehicle_ownership);
    ~Agents();
    void set_destinations();
    void set_navseqs();
    void step();
    Ref<Image> get_agents_img() const;
};