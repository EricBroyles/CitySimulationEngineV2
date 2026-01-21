#pragma once
#include <vector>
#include <godot_cpp/classes/image.hpp>
#include "velocity.h"
using namespace godot;

class World {
private:
    bool valid;
    const Ref<Image> tt;
    const Ref<Image> tm;
    const Ref<Image> dir;
    const Ref<Image> mph;
    const int step_duration;
    const int cell_width;
    const std::vector<Speed> speed; 
    const ConnectivityMatrix cm;

    // const ConnectivityMatrix walk_cm;
    // const ConnectivityMatrix drive_cm;
    
public:
    enum class TT {NONE, ROAD, WALKWAY, CROSSWALK, PARKING, BUILDING, BARRIER};
    enum class TM {NONE, JUNCTION_STOP, JUNCTION1, JUNCTION2, JUNCTION3, LANE_DIVIDER}
    const int cols;
    const int rows;
    World();
    World(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_dir, const Ref<Image> p_mph, const int p_step_duration, const int p_cell_width);
    bool is_valid() const {return valid;}
    void invalid() {valid(false);}

};