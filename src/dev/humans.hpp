// work in progress

/*

bi directional relationship.

Looking through humans. I wnat to know which car is theres
Looking through each car I want to know which human owns it.

*/

#pragma once
#include "idx.hpp"
#include "input.hpp"
#include "world.hpp"
#include "humans.hpp"
#include "personal_vehicle.hpp"

class Humans {
    using Homes = std::vector<Cell>;
    using Destinations = std::vector<Cell>;
    using Positions = std::vector<Cell>;
    using NavSeqs = std::vector<Cell>;
    using PVIdxs = std::vector<PersonalVehicleIdx>; //
    Homes homes;
    Destinations destinations;
    Positions position;
    PVIdxs pvidxs; //if dont own a pv, then id is invalid 
    NavSeqs navseqs;
    World& world;
    int num_humans;
public:
    Humans() {}
    Humans(const InputPackage& input, const World& world): 
        homes(input->get_num_humans()), 
        destinations(input->get_num_humans()), 
        position(input->get_num_humans()), 
        pvidxs(input->get_num_humans()), 
        navseqs(input->get_num_humans()), 
        world(world) 
    {
        HumanIdx max_h = HumanIdx(num_humans);
        PVIDX pvid = PVIDX(0);
        for (HumanIdx h = 0; h < max_h; h++) {
            //const Cell home = world.building_manager.reserve_random_building_cell();
            //if home is invalid. remove spot and update num_humans
            //homes[i] = home;
            //position[i] = home;
            //destinations[i] = world.building_manager.get_random_building_cell() // may be invalid
            
            // if (random number ... < pv ownership rate.) {
            //     this human owns a car. That car may or maynot have a valid parking space, reserved reasonably close to their position
            //     give them the PVIDX, and increment the PVIDX
            // }
            // else {
            //     they dont own a car, dont increment the PVIDX
            //     give this human a PVIDX(INVALID)
            // }
            

            //  None:  destination is invalid.
            //  Walk: Score = Walk_Preference * (world.estimated_walk_time(cell1, cell2) = Euclidean cell distance * average_walk_speed)
            //  Drive: do I have a car?
            //navseq[i] = NavSeq(world, cell1, cell2, ) //make sure to check if it is possible.

        }
    }

    //override [] operator to use HumanIDX
};