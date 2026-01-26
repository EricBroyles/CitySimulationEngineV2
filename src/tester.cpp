#include <godot_cpp/variant/string.hpp> //might not need
#include "tester.h"
#include "dev\cell.hpp"
#include "dev\vec.hpp"
#include "dev\direction.hpp"
using namespace godot;

void Tester::_bind_methods() {
	ClassDB::bind_method(D_METHOD("cell_vec_tests"), &Tester::cell_vec_tests);
}

void Tester::cell_vec_tests() const {
    print_line("@Test --- Vec2i (Basic Math Vector)");
    // Construction
    print_line(vformat("[Pass: %s] Vec2i() == Vec2i(0,0)", Vec2i() == Vec2i(0,0)));
    print_line(vformat("[Pass: %s] Vec2i(5,10).x == 5 and .y == 10", Vec2i(5,10).x == 5 && Vec2i(5,10).y == 10));

    // Equality
    print_line(vformat("[Pass: %s] Vec2i(1,1) == Vec2i(1,1)", Vec2i(1,1) == Vec2i(1,1)));
    print_line(vformat("[Pass: %s] Vec2i(1,1) != Vec2i(2,3)", Vec2i(1,1) != Vec2i(2,3)));

    // Addition
    Vec2i vec_add = Vec2i(1,1);
    print_line("Variable: vec_add = Vec2i(1,1)");
    print_line(vformat("[Pass: %s] vec_add += Vec2i(2,3) == Vec2i(3,4)", (vec_add += Vec2i(2,3)) == Vec2i(3,4)));
    print_line(vformat("[Pass: %s] vec_add is now Vec2i(3,4)", vec_add == Vec2i(3,4)));
    print_line(vformat("[Pass: %s] Vec2i(1,1) + Vec2i(2,3) == Vec2i(3,4)", (Vec2i(1,1) + Vec2i(2,3)) == Vec2i(3,4)));

    // Subtraction
    Vec2i vec_sub = Vec2i(5,8);
    print_line("Variable: vec_sub = Vec2i(5,8)");
    print_line(vformat("[Pass: %s] vec_sub -= Vec2i(2,3) == Vec2i(3,5)", (vec_sub -= Vec2i(2,3)) == Vec2i(3,5)));
    print_line(vformat("[Pass: %s] Vec2i(5,8) - Vec2i(2,3) == Vec2i(3,5)", (Vec2i(5,8) - Vec2i(2,3)) == Vec2i(3,5)));

    print_line("");
    print_line("@Test --- Cell (Grid Coordinates)");
    // Construction
    print_line(vformat("[Pass: %s] Cell() creates invalid cell", Cell().is_invalid()));
    print_line(vformat("[Pass: %s] Cell(1,1) is valid", Cell(1,1).is_valid()));
    print_line(vformat("[Pass: %s] Cell(2,3) is valid", Cell(2,3).is_valid()));
    print_line(vformat("[Pass: %s] Cell(-1,-1) is invalid", Cell(-1,-1).is_invalid()));
    print_line(vformat("[Pass: %s] Cell(Vec2i(5,10)) creates cell at (5,10)", Cell(Vec2i(5,10)).x() == 5 && Cell(Vec2i(5,10)).y() == 10));
    print_line(vformat("[Pass: %s] Cell(Vec2i(-4,-5)) is invalid", Cell(Vec2i(-4,-5)).is_invalid()));

    // Accessors
    Cell test_cell = Cell(7,9);
    print_line("Variable: test_cell = Cell(7,9)");
    print_line(vformat("[Pass: %s] test_cell.x() == 7", test_cell.x() == 7));
    print_line(vformat("[Pass: %s] test_cell.y() == 9", test_cell.y() == 9));

    // Validation
    print_line(vformat("[Pass: %s] Cell(0,0) is valid", Cell(0,0).is_valid()));
    print_line(vformat("[Pass: %s] Cell(-1,5) is invalid", Cell(-1,5).is_invalid()));
    print_line(vformat("[Pass: %s] Cell(5,-1) is invalid", Cell(5,-1).is_invalid()));
    Cell invalidate_test = Cell(5,5);
    invalidate_test.invalidate();
    print_line(vformat("[Pass: %s] Cell(5,5).invalidate() makes it invalid", invalidate_test.is_invalid()));

    // Bounds checking
    print_line(vformat("[Pass: %s] Cell(1,1) is in bounds [0-2, 0-3]", Cell(1,1).in_bounds(0,0,2,3)));
    print_line(vformat("[Pass: %s] Cell(2,3) is NOT in bounds [0-1, 0-2]", !Cell(2,3).in_bounds(0,0,1,2)));
    print_line(vformat("[Pass: %s] Cell() is NOT in bounds [0-1, 0-2]", !Cell().in_bounds(0,0,1,2)));
    print_line(vformat("[Pass: %s] Cell(0,0) is in bounds [0-0, 0-0]", Cell(0,0).in_bounds(0,0,0,0)));
    print_line(vformat("[Pass: %s] Cell(5,5) is NOT in bounds [0-4, 0-4]", !Cell(5,5).in_bounds(0,0,4,4)));

    // Equality
    print_line(vformat("[Pass: %s] Cell() == Cell()", Cell() == Cell()));
    print_line(vformat("[Pass: %s] Cell(1,1) == Cell(1,1)", Cell(1,1) == Cell(1,1)));
    print_line(vformat("[Pass: %s] Cell(1,1) != Cell(2,3)", Cell(1,1) != Cell(2,3)));
    print_line(vformat("[Pass: %s] Cell(0,0) != Cell()", Cell(0,0) != Cell()));

    // Resolution/scaling constructor
    print_line(vformat("[Pass: %s] Cell(Cell(1,1), 2) == Cell(0,0)", Cell(Cell(1,1), 2) == Cell(0,0)));
    print_line(vformat("[Pass: %s] Cell(Cell(2,3), 2) == Cell(1,1)", Cell(Cell(2,3), 2) == Cell(1,1)));
    print_line(vformat("[Pass: %s] Cell(Cell(2,0), 2) == Cell(1,0)", Cell(Cell(2,0), 2) == Cell(1,0)));
    print_line(vformat("[Pass: %s] Cell(Cell(5,7), 2) == Cell(2,3)", Cell(Cell(5,7), 2) == Cell(2,3)));

    // Addition with Cell
    Cell add_cell = Cell(1,1);
    print_line("");
    print_line("Variable: add_cell = Cell(1,1)");
    print_line(vformat("[Pass: %s] add_cell += Cell(2,3) == Cell(3,4)", (add_cell += Cell(2,3)) == Cell(3,4)));
    print_line(vformat("[Pass: %s] add_cell is now Cell(3,4)", add_cell == Cell(3,4)));
    print_line(vformat("[Pass: %s] add_cell += Cell(-1,-1) == Cell(2,3)", (add_cell += Cell(-1,-1)) == Cell(2,3)));

    // Addition with Vec2i
    Cell add_vec_cell = Cell(1,1);
    print_line("");
    print_line("Variable: add_vec_cell = Cell(1,1)");
    print_line(vformat("[Pass: %s] add_vec_cell += Vec2i(2,3) == Cell(3,4)", (add_vec_cell += Vec2i(2,3)) == Cell(3,4)));
    print_line(vformat("[Pass: %s] add_vec_cell += Vec2i(-4,-2) == Cell(-1,2)", (add_vec_cell += Vec2i(-4,-2)) == Cell(-1,2)));

    // Operator+ combinations
    print_line("");
    print_line(vformat("[Pass: %s] Cell(1,1) + Cell(2,3) == Cell(3,4)", (Cell(1,1) + Cell(2,3)) == Cell(3,4)));
    print_line(vformat("[Pass: %s] Cell(1,1) + Vec2i(2,3) == Cell(3,4)", (Cell(1,1) + Vec2i(2,3)) == Cell(3,4)));
    print_line(vformat("[Pass: %s] Vec2i(1,1) + Cell(2,3) == Cell(3,4)", (Vec2i(1,1) + Cell(2,3)) == Cell(3,4)));
    print_line(vformat("[Pass: %s] Cell(-3,-2) + Cell(4,3) == Cell(1,1)", (Cell(-3,-2) + Cell(4,3)) == Cell(1,1)));

    // Complex expression
    Cell complex_add = Cell(1,1);
    print_line("");
    print_line("Variable: complex_add = Cell(1,1)");
    print_line(vformat("[Pass: %s] complex_add += Cell(-3,-2) + Cell(4,3) == Cell(2,2)", 
        (complex_add += Cell(-3,-2) + Cell(4,3)) == Cell(2,2)));

    print_line("");
    print_line("@Test --- Cell ↔ Vec2i Conversions");
    // Implicit conversion
    Cell conv_cell = Cell(5,10);
    print_line("Variable: conv_cell = Cell(5,10)");
    Vec2i implicit_vec = conv_cell;  // Uses operator Vec2i()
    print_line(vformat("[Pass: %s] Vec2i implicit_vec = conv_cell; creates Vec2i(5,10)", 
        implicit_vec == Vec2i(5,10)));

    // Explicit conversion
    Vec2i explicit_vec = conv_cell.to_vec2i();
    print_line(vformat("[Pass: %s] conv_cell.to_vec2i() == Vec2i(5,10)", 
        explicit_vec == Vec2i(5,10)));

    // Mixed operations
    print_line(vformat("[Pass: %s] Vec2i(1,1) + Cell(2,3) results in Cell type", 
        (Vec2i(1,1) + Cell(2,3)) == Cell(3,4)));

    print_line("");
    print_line("@Test --- Edge Cases");
    print_line(vformat("[Pass: %s] Cell(0,-1) is invalid", Cell(0,-1).is_invalid()));
    print_line(vformat("[Pass: %s] Cell(-1,0) is invalid", Cell(-1,0).is_invalid()));
    print_line(vformat("[Pass: %s] Cell(0,0) is valid", Cell(0,0).is_valid()));
    print_line(vformat("[Pass: %s] Very large coordinates Cell(10000,10000) is valid", 
        Cell(10000,10000).is_valid()));

    Cell chain_test = Cell(1,1);
    print_line("Variable: chain_test = Cell(1,1)");
    print_line(vformat("[Pass: %s] Chained operations: (chain_test += Vec2i(2,2)) += Cell(3,3) == Cell(6,6)", 
        ((chain_test += Vec2i(2,2)) += Cell(3,3)) == Cell(6,6)));
}



