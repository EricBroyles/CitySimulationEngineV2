#pragma once

#include "world.h"
#include "cell.h"

using namespace godot;

class Human {

private:
    const World& world

public:
    Human();
    Human(const World& world);
    Human(const World& world, Cell home, Cell destination)
    ~Human();

};