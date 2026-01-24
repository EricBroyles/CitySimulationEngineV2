#include <godot_cpp/variant/string.hpp>
#include "tester.h"
#include "dev\cell.hpp"
using namespace godot;

void Tester::_bind_methods() {
	ClassDB::bind_method(D_METHOD("cell_tests"), &Tester::cell_tests);
}

void Tester::cell_tests() const {
    Cell invalid_cell = Cell();
    Cell c1_1 = Cell(1,1);
    Cell c2_3 = Cell(2,3);
    Cell c5_5 = Cell(5,5);
    bool pass = false;

    print_line("@Test --- Cell()");
    pass = (invalid_cell.x == -1 && invalid_cell.y == -1) ? true : false;
    print_line(vformat("[Pass: %s] (X: %d, Y: %d)", pass, invalid_cell.x, invalid_cell.y));

    print_line("@Test --- static constexpr Cell = Cell(5,5) == Cell(5,5)");
    pass = (Tester::CELL5_5 == c5_5) ? true : false;
    print_line(vformat("[Pass: %s] (X: %d, Y: %d)", pass, Tester::CELL5_5.x, Tester::CELL5_5.y));

    print_line("@Test --- Cell(1,1) + Cell(2,3) + Cell(5,5) == Cell(8,9)");
    Cell c_add = c1_1 + c2_3 + c5_5;
    pass = (c_add == Cell(8,9)) ? true : false;
    print_line(vformat("[Pass: %s] (X: %d, Y: %d)", pass, c_add.x, c_add.y)); 
}

