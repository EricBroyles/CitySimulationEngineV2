#pragma once
#include <array>
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
    enum class TM {NONE, JUNCTION_STOP, JUNCTION1, JUNCTION2, JUNCTION3, LANE_DIVIDER};
    static constexpr std::array<bool, 7> CAN_WALK_TT = {false, false, true, true, true, true, false};
    static constexpr std::array<bool, 7> CAN_DRIVE_TT = {false, true, false, true, true, false, false};
    const int cols;
    const int rows;
    World();
    World(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_dir, const Ref<Image> p_mph, const int p_step_duration, const int p_cell_width);
    bool is_valid() const {return valid;}
    void invalid() {valid(false);}

    World::TT get_tt(const Cell& cell) const;
    World::TM get_tm(const Cell& cell) const;
    Direction get_dir(const Cell& cell) const;
    Speed get_speed(const Cell& cell) const;
    Cell random_building() const;
    Cell random_parking() const;
    bool can_walk_at(const Cell& cell) const {return CAN_WALK_TT[get_tt(cell)];}
    bool can_drive_at(const Cell& cell) const {return DRIVE_WALK_TT[get_tt(cell);]} //can_walk_here
    bool can_walk_between(const Cell& cell1, const Cell& cell2) const; //finish latter, connectivity
    bool in_bounds(const Cell& cell) const {return cell.in_bounds(0,0,cols,rows);}
    bool out_of_bounds(const Cell& cell) const {return !in_bounds(cell);}

};