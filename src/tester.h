/*
@class Tester

@brief
* Test all C++ code except simulation. 
* Interact with from godot.
* Best to run in a seperate test scene.
* All outputs are to the console via godot's print.

@additions
* #include
* Method H++
* Method C++
* Add method to _bind_methods in C++
* Recompile -> restart godot 
* Call method from godot

@examples
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
#include "dev\cell.hpp"
using namespace godot;

class Tester : public RefCounted {
    GDCLASS(Tester, RefCounted);
private:
    static constexpr Cell CELL5_5 = Cell(5,5); 
protected:
    static void _bind_methods(); 
public:
    Tester() {};
    void cell_tests() const;
};