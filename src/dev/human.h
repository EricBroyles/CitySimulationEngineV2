#pragma once

#include "world.h"
#include "cell.h"

using namespace godot;

class Human {
private:
    bool valid;
    const World& world;
    Cell position;
    Cell home;
    Cell destination;
    Path path;
    Navseq navseq;
    PersonalVehicle& pv;

public:
    Human();
    Human(const World& world);
    Human(const World& world, Cell home, Cell destination);
    bool is_valid() const {return valid;}
    void invalid() {valid(false);}
};