#pragma once
#include <godot_cpp/classes/image.hpp>
using namespace godot;

class World {
    private:
    public:
        World();
        World(const Ref<Image> tt, const Ref<Image> tm, const Ref<Image> dir, const Ref<Image> mph);
        ~World();

};