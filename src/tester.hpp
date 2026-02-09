/*
@Tester

@brief
* Test all C++ code except simulation. 
* Interact with from godot.
* Best to run in a seperate test scene.
* All outputs are to the console via godot's print.

@additions
* #include inside .cpp
* Method H++
* Method C++
* Add method to _bind_methods in C++
* Recompile -> restart godot 
* Call method from godot

@use
==============================
"GDScript"
var tester: Tester = Tester()
tester.cell_tests()
tester.matrix_tests()
# etc...
-------------------------------
*/
#pragma once
#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

class Tester : public RefCounted {
    GDCLASS(Tester, RefCounted);
protected:
    static void _bind_methods(); 
public:
    Tester() {};
    void cell_vec() const;
    void speed() const;
    void direction() const;
    void terrain_mod() const;
    void terrain_type() const;
    void matrix() const;
    void cmid() const;
    void construct_cm() const;
    void benchmark_cm() const;
    void cm() const;
    void timing() const;
    void world() const;
    void idx() const;
};