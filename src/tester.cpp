// #include <godot_cpp/variant/string.hpp> //might not need
#include "tester.h"
#include "dev\cell.hpp"
#include "dev\vec.hpp"
#include "dev\direction.hpp"
using namespace godot;

void Tester::_bind_methods() {
	ClassDB::bind_method(D_METHOD("cell_vec_tests"), &Tester::cell_vec_tests);
	ClassDB::bind_method(D_METHOD("direction_tests"), &Tester::direction_tests);
	ClassDB::bind_method(D_METHOD("speed_tests"), &Tester::speed_tests);
}

void Tester::speed_tests() const {

}

void Tester::direction_tests() const {
    print_line("@Test --- Direction: Construction");
    print_line(vformat("[Pass: %s] Direction() creates NONE", Direction().val == Direction::NONE));
    print_line(vformat("[Pass: %s] Direction(Direction::E) creates E", Direction(Direction::E).val == Direction::E));
    print_line(vformat("[Pass: %s] Direction(0b00000001) creates E", Direction(0b00000001).val == Direction::E));
    print_line(vformat("[Pass: %s] Direction(Direction::ALL) has all bits", Direction(Direction::ALL).val == Direction::ALL));

    print_line("");
    print_line("@Test --- Direction: is_none() and count()");
    print_line(vformat("[Pass: %s] Direction() is_none() returns true", Direction().is_none()));
    print_line(vformat("[Pass: %s] Direction(Direction::E) is_none() returns false", !Direction(Direction::E).is_none()));
    print_line(vformat("[Pass: %s] Direction(Direction::NONE).count() == 0", Direction(Direction::NONE).count() == 0));
    print_line(vformat("[Pass: %s] Direction(Direction::E).count() == 1", Direction(Direction::E).count() == 1));
    print_line(vformat("[Pass: %s] Direction(Direction::NE).count() == 1", Direction(Direction::NE).count() == 1));
    print_line(vformat("[Pass: %s] Direction(Direction::E | Direction::N).count() == 2", 
        Direction(Direction::E | Direction::N).count() == 2));
    print_line(vformat("[Pass: %s] Direction(Direction::ALL).count() == 8", Direction(Direction::ALL).count() == 8));
    print_line(vformat("[Pass: %s] Direction(0b10110101).count() == 5", Direction(0b10110101).count() == 5));

    print_line("");
    print_line("@Test --- Direction: operator[]");
    Direction test_dir(Direction::E | Direction::N | Direction::W);
    print_line("Variable: test_dir = Direction(E | N | W) = 0b00010101");
    print_line(vformat("[Pass: %s] test_dir[0] (E bit) is true", test_dir[0]));
    print_line(vformat("[Pass: %s] test_dir[1] (NE bit) is false", !test_dir[1]));
    print_line(vformat("[Pass: %s] test_dir[2] (N bit) is true", test_dir[2]));
    print_line(vformat("[Pass: %s] test_dir[4] (W bit) is true", test_dir[4]));
    print_line(vformat("[Pass: %s] test_dir[7] (SE bit) is false", !test_dir[7]));
    print_line(vformat("[Pass: %s] test_dir[-1] (out of bounds) is false", !test_dir[-1]));
    print_line(vformat("[Pass: %s] test_dir[8] (out of bounds) is false", !test_dir[8]));

    print_line("");
    print_line("@Test --- Direction: Equality operators");
    print_line(vformat("[Pass: %s] Direction() == Direction()", Direction() == Direction()));
    print_line(vformat("[Pass: %s] Direction(Direction::E) == Direction(Direction::E)", 
        Direction(Direction::E) == Direction(Direction::E)));
    print_line(vformat("[Pass: %s] Direction(Direction::E) != Direction(Direction::N)", 
        Direction(Direction::E) != Direction(Direction::N)));
    print_line(vformat("[Pass: %s] Direction(Direction::E | Direction::N) == Direction(0b00000101)", 
        Direction(Direction::E | Direction::N) == Direction(0b00000101)));

    print_line("");
    print_line("@Test --- Direction: Bitwise OR");
    Direction or_test = Direction(Direction::E);
    print_line("Variable: or_test = Direction(E)");
    print_line(vformat("[Pass: %s] or_test |= Direction(N) results in E|N", 
        (or_test |= Direction(Direction::N)) == Direction(Direction::E | Direction::N)));
    print_line(vformat("[Pass: %s] or_test now has count() == 2", or_test.count() == 2));
    print_line(vformat("[Pass: %s] Direction(E) | Direction(N) == Direction(E|N)", 
        (Direction(Direction::E) | Direction(Direction::N)) == Direction(Direction::E | Direction::N)));
    print_line(vformat("[Pass: %s] Direction(E|W) | Direction(N|S) == Direction(E|W|N|S)", 
        (Direction(Direction::E | Direction::W) | Direction(Direction::N | Direction::S)) == 
        Direction(Direction::E | Direction::W | Direction::N | Direction::S)));

    print_line("");
    print_line("@Test --- Direction: Bitwise AND");
    Direction and_test = Direction(Direction::E | Direction::N | Direction::W);
    print_line("Variable: and_test = Direction(E|N|W)");
    print_line(vformat("[Pass: %s] and_test &= Direction(E|N) results in E|N", 
        (and_test &= Direction(Direction::E | Direction::N)) == Direction(Direction::E | Direction::N)));
    print_line(vformat("[Pass: %s] Direction(E|N) & Direction(N|W) == Direction(N)", 
        (Direction(Direction::E | Direction::N) & Direction(Direction::N | Direction::W)) == Direction(Direction::N)));
    print_line(vformat("[Pass: %s] Direction(E) & Direction(N) == Direction(NONE)", 
        (Direction(Direction::E) & Direction(Direction::N)) == Direction(Direction::NONE)));
    print_line(vformat("[Pass: %s] Direction(ALL) & Direction(E) == Direction(E)", 
        (Direction(Direction::ALL) & Direction(Direction::E)) == Direction(Direction::E)));

    print_line("");
    print_line("@Test --- Direction: Addition");
    Direction add_test = Direction(Direction::E);
    print_line("Variable: add_test = Direction(E) = 0b00000001");
    print_line(vformat("[Pass: %s] add_test += Direction(N) results in 0b00000101", 
        (add_test += Direction(Direction::N)).val == 0b00000101));
    print_line(vformat("[Pass: %s] Direction(0b00000001) + Direction(0b00000010) == Direction(0b00000011)", 
        (Direction(0b00000001) + Direction(0b00000010)) == Direction(0b00000011)));

    print_line("");
    print_line("@Test --- Direction: Subtraction");
    Direction sub_test = Direction(0b00000101);
    print_line("Variable: sub_test = Direction(0b00000101)");
    print_line(vformat("[Pass: %s] sub_test -= Direction(0b00000001) results in 0b00000100", 
        (sub_test -= Direction(0b00000001)).val == 0b00000100));
    print_line(vformat("[Pass: %s] Direction(0b00000101) - Direction(0b00000001) == Direction(0b00000100)", 
        (Direction(0b00000101) - Direction(0b00000001)) == Direction(0b00000100)));

    print_line("");
    print_line("@Test --- Direction: Matching");
    Direction match_test1(Direction::E | Direction::N);
    Direction match_test2(Direction::N | Direction::W);
    print_line("Variable: match_test1 = Direction(E|N)");
    print_line("Variable: match_test2 = Direction(N|W)");
    print_line(vformat("[Pass: %s] match_test1.no_matches(Direction(W|S)) is true", 
        match_test1.no_matches(Direction(Direction::W | Direction::S))));
    print_line(vformat("[Pass: %s] match_test1.no_matches(match_test2) is false (N matches)", 
        !match_test1.no_matches(match_test2)));
    print_line(vformat("[Pass: %s] match_test1.atleast1_matches(match_test2) is true (N matches)", 
        match_test1.atleast1_matches(match_test2)));
    print_line(vformat("[Pass: %s] Direction(E).no_matches(Direction(W)) is true", 
        Direction(Direction::E).no_matches(Direction(Direction::W))));
    print_line(vformat("[Pass: %s] Direction().no_matches(Direction()) is true (both NONE)", 
        Direction().no_matches(Direction())));

    print_line("");
    print_line("@Test --- SoloDirection: Valid Construction");
    print_line(vformat("[Pass: %s] SoloDirection() creates NONE", SoloDirection().val == Direction::NONE));
    print_line(vformat("[Pass: %s] SoloDirection(Direction::E) is valid", SoloDirection(Direction::E).val == Direction::E));
    print_line(vformat("[Pass: %s] SoloDirection(Direction::N) is valid", SoloDirection(Direction::N).val == Direction::N));
    print_line(vformat("[Pass: %s] SoloDirection(Direction::NONE) is valid", SoloDirection(Direction::NONE).val == Direction::NONE));

    Direction solo_source(Direction::W);
    print_line("Variable: solo_source = Direction(W)");
    print_line(vformat("[Pass: %s] SoloDirection(solo_source) is valid", 
        SoloDirection(solo_source).val == Direction::W));

    print_line("");
    print_line("@Test --- SoloDirection: Invalid Construction (should throw)");
    bool threw_multi = false;
    try {
        SoloDirection invalid(Direction::E | Direction::N);
    } catch (const std::invalid_argument& e) {
        threw_multi = true;
    }
    print_line(vformat("[Pass: %s] SoloDirection(E|N) throws exception", threw_multi));

    bool threw_all = false;
    try {
        SoloDirection invalid(Direction::ALL);
    } catch (const std::invalid_argument& e) {
        threw_all = true;
    }
    print_line(vformat("[Pass: %s] SoloDirection(ALL) throws exception", threw_all));

    bool threw_from_dir = false;
    try {
        Direction multi(Direction::E | Direction::W);
        SoloDirection invalid(multi);
    } catch (const std::invalid_argument& e) {
        threw_from_dir = true;
    }
    print_line(vformat("[Pass: %s] SoloDirection(Direction with multiple bits) throws exception", threw_from_dir));

    print_line("");
    print_line("@Test --- SoloDirection: to_vec2i()");
    print_line(vformat("[Pass: %s] SoloDirection(E).to_vec2i() == Vec2i(1,0)", 
        SoloDirection(Direction::E).to_vec2i() == Vec2i(1,0)));
    print_line(vformat("[Pass: %s] SoloDirection(NE).to_vec2i() == Vec2i(1,1)", 
        SoloDirection(Direction::NE).to_vec2i() == Vec2i(1,-1)));
    print_line(vformat("[Pass: %s] SoloDirection(N).to_vec2i() == Vec2i(0,1)", 
        SoloDirection(Direction::N).to_vec2i() == Vec2i(0,-1)));
    print_line(vformat("[Pass: %s] SoloDirection(NW).to_vec2i() == Vec2i(-1,1)", 
        SoloDirection(Direction::NW).to_vec2i() == Vec2i(-1,-1)));
    print_line(vformat("[Pass: %s] SoloDirection(W).to_vec2i() == Vec2i(-1,0)", 
        SoloDirection(Direction::W).to_vec2i() == Vec2i(-1,0)));
    print_line(vformat("[Pass: %s] SoloDirection(SW).to_vec2i() == Vec2i(-1,-1)", 
        SoloDirection(Direction::SW).to_vec2i() == Vec2i(-1,1)));
    print_line(vformat("[Pass: %s] SoloDirection(S).to_vec2i() == Vec2i(0,-1)", 
        SoloDirection(Direction::S).to_vec2i() == Vec2i(0,1)));
    print_line(vformat("[Pass: %s] SoloDirection(SE).to_vec2i() == Vec2i(1,-1)", 
        SoloDirection(Direction::SE).to_vec2i() == Vec2i(1,1)));
    print_line(vformat("[Pass: %s] SoloDirection(NONE).to_vec2i() == Vec2i(0,0)", 
        SoloDirection(Direction::NONE).to_vec2i() == Vec2i(0,0)));

    print_line("");
    print_line("@Test --- SoloDirection: Inheritance (is-a Direction)");
    SoloDirection solo_inherit(Direction::E);
    Direction base_from_solo = solo_inherit;  // Implicit upcast
    print_line(vformat("[Pass: %s] SoloDirection can be assigned to Direction", 
        base_from_solo.val == Direction::E));
    print_line(vformat("[Pass: %s] SoloDirection inherits count() method", 
        solo_inherit.count() == 1));
    print_line(vformat("[Pass: %s] SoloDirection inherits is_none() method", 
        !solo_inherit.is_none()));
    print_line(vformat("[Pass: %s] SoloDirection(NONE).is_none() is true", 
        SoloDirection().is_none()));

    print_line("");
    print_line("@Test --- Edge Cases");
    print_line(vformat("[Pass: %s] Direction with all bits set has count == 8", 
        Direction(0b11111111).count() == 8));
    print_line(vformat("[Pass: %s] Direction(0).is_none() is true", 
        Direction(0).is_none()));
    print_line(vformat("[Pass: %s] Multiple OR operations: (E|N|W|S).count() == 4", 
        (Direction(Direction::E) | Direction(Direction::N) | Direction(Direction::W) | Direction(Direction::S)).count() == 4));
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



