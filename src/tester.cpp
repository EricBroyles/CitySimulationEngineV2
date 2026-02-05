#include "tester.hpp"
#include "dev/cmid.hpp"
#include "tests/my_connectivity_matrix.hpp"

using namespace godot;

void Tester::_bind_methods() {
    ClassDB::bind_method(D_METHOD("cell_vec"), &Tester::cell_vec);
    ClassDB::bind_method(D_METHOD("speed"), &Tester::speed);
    ClassDB::bind_method(D_METHOD("direction"), &Tester::direction);
    ClassDB::bind_method(D_METHOD("terrain_mod"), &Tester::terrain_mod);
    ClassDB::bind_method(D_METHOD("terrain_type"), &Tester::terrain_type);
    ClassDB::bind_method(D_METHOD("matrix"), &Tester::matrix);
    ClassDB::bind_method(D_METHOD("cmid"), &Tester::cmid);
    ClassDB::bind_method(D_METHOD("construct_cm"), &Tester::construct_cm);
    ClassDB::bind_method(D_METHOD("benchmark_cm"), &Tester::benchmark_cm);
    ClassDB::bind_method(D_METHOD("cm"), &Tester::cm);

}

void Tester::cm() const {
    print_line("==================================");
    print_line("@Test: cm"); int passed = 0, total = 0;

    {
        CM cm = MyCM::create(4, 4, TT(TT::WALKWAY), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = cm.can_walk_between(Cell(0,0), Cell(3,3));
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::ALL, can_walk_between(Cell(0,0), Cell(3,3))", pass)); if (pass) passed++; total++;
        pass = cm.can_walk_between(Cell(3,2), Cell(3,2));
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::ALL, can_walk_between(Cell(3,2), Cell(3,2))", pass)); if (pass) passed++; total++;
        pass = !cm.can_drive_between(Cell(0,0), Cell(3,3));
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::ALL, not can_drive_between(Cell(0,0), Cell(3,3))", pass)); if (pass) passed++; total++;
        pass = !cm.can_drive_between(Cell(3,2), Cell(3,2));
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::ALL, not can_drive_between(Cell(3,2), Cell(3,2))", pass)); if (pass) passed++; total++;
    }

    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}

void Tester::benchmark_cm() const {
    print_line("==================================");
    print_line("@Benchmark: cm"); bool display_time = true;
    
    {
        print_line("\nCM 4096x4096 TT::NONE Dir::NONE"); // all barriers so best case
        CM cm = MyCM::create(4096, 4096, TT(TT::NONE), Dir(Dir::NONE), display_time);
    }

    {
        print_line("\nCM 4096x4096 TT::NONE Dir::ALL"); // all barriers so best case
        CM cm = MyCM::create(4096, 4096, TT(TT::NONE), Dir(Dir::ALL), display_time);
    }

    {
        print_line("\nCM 4096x4096 TT::ROAD Dir::ALL"); // walk is all barrier, drive is no barrier.
        CM cm = MyCM::create(4096, 4096, TT(TT::ROAD), Dir(Dir::ALL), display_time);
    }

    {
        print_line("\nCM 4096x4096 TT::PARKING Dir::ALL"); // no barriers so worst case.
        CM cm = MyCM::create(4096, 4096, TT(TT::PARKING), Dir(Dir::ALL), display_time);
    }

    print_line("==================================");
}

void Tester::construct_cm() const {
    print_line("==================================");
    print_line("@TEST: construct_cm"); int passed = 0, total = 0;

    /*
    TT VARIES while Dir is ALL
    */

    {
        CM cm = MyCM::create(4, 4, TT(TT::NONE), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::NONE, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::ROAD), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_FULL_4x4) && MyCM::validate_num_groups(cm, 0, 1);
        print_line(vformat("[Pass: %s] TT::ROAD, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::WALKWAY), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 1, 0);
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::CROSSWALK), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_FULL_4x4) && MyCM::validate_num_groups(cm, 1, 1);
        print_line(vformat("[Pass: %s] TT::CROSSWALK, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_FULL_4x4) && MyCM::validate_num_groups(cm, 1, 1);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BUILDING), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 1, 0);
        print_line(vformat("[Pass: %s] TT::BUILDING, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BARRIER), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::BARRIER, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    /*
    TT VARIES while Dir is NONE
    */

    {
        CM cm = MyCM::create(4, 4, TT(TT::NONE), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::NONE, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::ROAD), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::ROAD, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::WALKWAY), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::CROSSWALK), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::CROSSWALK, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BUILDING), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::BUILDING, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BARRIER), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::BARRIER, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    /*
    TT PARKING while Dir VARIES from E->SE
    */

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::E));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_HORI_4x4, MyCM::CMID_HORI_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::E", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::W));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_HORI_4x4, MyCM::CMID_HORI_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::W", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::N));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_VERT_4x4, MyCM::CMID_VERT_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::N", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::S));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_VERT_4x4, MyCM::CMID_VERT_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::S", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::NE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_POS_DIAG_4x4, MyCM::CMID_POS_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::NE", pass)); if (pass) passed++; total++;
    }

        {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::SW));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_POS_DIAG_4x4, MyCM::CMID_POS_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::SW", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::NW));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_NEG_DIAG_4x4, MyCM::CMID_NEG_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::NW", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::SE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_NEG_DIAG_4x4, MyCM::CMID_NEG_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::SE", pass)); if (pass) passed++; total++;
    }

    /*
    W Connection
    */

    {
        CM cm = MyCM::create_w_connection(Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::W_CONNECTION, MyCM::W_CONNECTION) && MyCM::validate_num_groups(cm, 1, 1);
        print_line(vformat("[Pass: %s] W Connection with Dir::ALL", pass)); if (pass) passed++; total++;
    }

    /*
    Bottom Leak
    */

    {
        CM cm = MyCM::create_bottom_leak(Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::BOTTOM_LEAK, MyCM::BOTTOM_LEAK) && MyCM::validate_num_groups(cm, 2, 2);
        print_line(vformat("[Pass: %s] Bottom Leak with Dir::ALL", pass)); if (pass) passed++; total++;
    }
 
    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}

void Tester::cmid() const {
    print_line("==================================");
    print_line("@Test: cmid"); int passed = 0, total = 0; 

    {
        CMID default_id;
        CMID custom_id(5);
        CMID barrier_id(CMID::BARRIER);
        bool pass = (default_id.val == CMID::INVALID && custom_id.val == 5 &&
                    barrier_id.val == CMID::BARRIER && CMID::INVALID == -2 &&
                    CMID::BARRIER == -1);
        print_line(vformat("[Pass: %s] Construction and constant values", pass)); if (pass) passed++; total++; 
    }
    
        {
        CMID invalid_id;
        CMID barrier_id(CMID::BARRIER);
        CMID valid_id(0);
        CMID valid_id2(10);
        bool pass = (invalid_id.is_invalid() && !invalid_id.is_valid() &&
                !barrier_id.is_invalid() && barrier_id.is_valid() &&
                valid_id.is_valid() && !valid_id.is_invalid() &&
                valid_id2.is_valid() && !valid_id2.is_invalid());
        print_line(vformat("[Pass: %s] is_valid() and is_invalid() checks", pass)); if (pass) passed++; total++;
    }

    {
        CMID barrier_id(CMID::BARRIER);
        CMID not_barrier(0);
        CMID invalid_id;
        bool pass = (barrier_id.is_barrier() &&
                !not_barrier.is_barrier() &&
                !invalid_id.is_barrier());
        print_line(vformat("[Pass: %s] is_barrier() check", pass)); if (pass) passed++; total++;
    }

    {
        CMID id(5);
        id.invalidate();
        bool first_check = (id.val == CMID::INVALID && id.is_invalid());
        
        id = CMID(10);
        id.barrier();
        bool second_check = (id.val == CMID::BARRIER && id.is_barrier());
        
        bool pass = (first_check && second_check);
        print_line(vformat("[Pass: %s] invalidate() and barrier() methods", pass)); if (pass) passed++; total++;
    }

    {
        CMID id(5);
        CMID& result = ++id;
        bool pass = (id.val == 6 && result.val == 6 && &result == &id);
        print_line(vformat("[Pass: %s] Prefix increment operator (++id)", pass)); if (pass) passed++; total++;
    }

    {
        CMID id1(5);
        CMID id2(5);
        CMID id3(10);
        CMID barrier1(CMID::BARRIER);
        CMID barrier2(CMID::BARRIER);
        bool pass = (id1 == id2 &&
                !(id1 == id3) &&
                barrier1 == barrier2 &&
                !(id1 == barrier1));
        print_line(vformat("[Pass: %s] Equality operator (==)", pass)); if (pass) passed++; total++;
    }

    {
        CMID zero_id(0);
        CMID negative_id(-3);
        CMID large_id(1000000);
        bool pass = (zero_id.is_valid() &&
                negative_id.is_invalid() &&
                large_id.is_valid());
        print_line(vformat("[Pass: %s] Boundary values (0, negative, large positive)", pass)); if (pass) passed++; total++;
    }

    {
        CMID from_barrier(CMID::BARRIER);
        ++from_barrier;
        CMID from_zero(0);
        ++from_zero;
        CMID from_negative(-5);
        ++from_negative;
        bool pass = (from_barrier.val == 0 &&
                from_zero.val == 1 &&
                from_negative.val == -4);
        print_line(vformat("[Pass: %s] Increment from barrier, zero, and negative", pass)); if (pass) passed++; total++;
    }
   
    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}

void Tester::matrix() const {
    print_line("==================================");
    print_line("@Test: matrix");
    int passed = 0, total = 0;

    {
        Matrix<int> matrix(5, 5);
        matrix.at(Cell(2, 3)) = 42;
        bool pass = (matrix.at(Cell(2, 3)) == 42);
        print_line(vformat("[Pass: %s] Set and get value at Cell(2,3)", pass)); if (pass) passed++; total++;
    }

    {
        Matrix<int> matrix(3, 3);
        bool pass = (matrix.at(Cell(1, 1)) == 0); // int() == 0
        print_line(vformat("[Pass: %s] Default initialization to T()", pass)); if (pass) passed++; total++;
    }

    {
        Matrix<int> matrix(4, 4);
        matrix.at(Cell(2, 2)) = 100;
        const Matrix<int>& const_ref = matrix;
        bool pass = (const_ref.at(Cell(2, 2)) == 100);
        print_line(vformat("[Pass: %s] Const reference access", pass)); if (pass) passed++; total++;
    }

    {
        Matrix<float> matrix(2, 2);
        matrix.at(Cell(0, 0)) = 3.14f;
        matrix.at(Cell(1, 1)) = 2.71f;
        bool pass = (matrix.at(Cell(0, 0)) > 3.13f && matrix.at(Cell(0, 0)) < 3.15f &&
                matrix.at(Cell(1, 1)) > 2.70f && matrix.at(Cell(1, 1)) < 2.72f);
        print_line(vformat("[Pass: %s] Matrix<float> type", pass)); if (pass) passed++; total++;
    }

    {
        Matrix<int> matrix(5, 5);
        matrix.at(Cell(0, 0)) = 1;    // Top-left
        matrix.at(Cell(4, 0)) = 2;    // Top-right
        matrix.at(Cell(0, 4)) = 3;    // Bottom-left
        matrix.at(Cell(4, 4)) = 4;    // Bottom-right
        bool pass = (matrix.at(Cell(0, 0)) == 1 &&
                matrix.at(Cell(4, 0)) == 2 &&
                matrix.at(Cell(0, 4)) == 3 &&
                matrix.at(Cell(4, 4)) == 4);
        print_line(vformat("[Pass: %s] Edge cell access", pass)); if (pass) passed++; total++;
    }

    {
        Matrix<int> matrix(3, 3);
        matrix.at(Cell(1, 1)) = 10;
        int& ref = matrix.at(Cell(1, 1));
        ref = 20;
        bool pass = (matrix.at(Cell(1, 1)) == 20);
        print_line(vformat("[Pass: %s] Reference modification", pass)); if (pass) passed++; total++;
    }

    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}


void Tester::terrain_type() const {
    print_line("==================================");
    print_line("@Test: terrain_type");int passed = 0, total = 0;

    {
        bool pass = (TerrainType().val == TerrainType::NONE);
        print_line(vformat("[Pass: %s] TerrainType() creates NONE", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainType(TerrainType::ROAD).val == TerrainType::ROAD);
        print_line(vformat("[Pass: %s] TerrainType(ROAD) creates ROAD", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainType(TerrainType::WALKWAY).val == TerrainType::WALKWAY);
        print_line(vformat("[Pass: %s] TerrainType(WALKWAY) creates WALKWAY", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainType(TerrainType::CROSSWALK).val == TerrainType::CROSSWALK);
        print_line(vformat("[Pass: %s] TerrainType(CROSSWALK) creates CROSSWALK", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainType(TerrainType::PARKING).val == TerrainType::PARKING);
        print_line(vformat("[Pass: %s] TerrainType(PARKING) creates PARKING", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainType(TerrainType::BUILDING).val == TerrainType::BUILDING);
        print_line(vformat("[Pass: %s] TerrainType(BUILDING) creates BUILDING", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainType(TerrainType::BARRIER).val == TerrainType::BARRIER);
        print_line(vformat("[Pass: %s] TerrainType(BARRIER) creates BARRIER", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            TerrainType invalid(-1);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] TerrainType(-1) throws exception", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            TerrainType invalid(TerrainType::MAX);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] TerrainType(MAX) throws exception", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            TerrainType invalid(100);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] TerrainType(100) throws exception", pass)); if (pass) passed++; total++;
    }

    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}

void Tester::terrain_mod() const {
    print_line("==================================");
    print_line("@Test: terrain_mod"); int passed = 0, total = 0;

    {
        bool pass = (TerrainMod().val == TerrainMod::NONE);
        print_line(vformat("[Pass: %s] TerrainMod() creates NONE", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainMod(TerrainMod::JUNCTION_STOP).val == TerrainMod::JUNCTION_STOP);
        print_line(vformat("[Pass: %s] TerrainMod(JUNCTION_STOP)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainMod(TerrainMod::JUNCTION1).val == TerrainMod::JUNCTION1);
        print_line(vformat("[Pass: %s] TerrainMod(JUNCTION1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainMod(TerrainMod::JUNCTION2).val == TerrainMod::JUNCTION2);
        print_line(vformat("[Pass: %s] TerrainMod(JUNCTION2)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainMod(TerrainMod::JUNCTION3).val == TerrainMod::JUNCTION3);
        print_line(vformat("[Pass: %s] TerrainMod(JUNCTION3)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (TerrainMod(TerrainMod::LANE_DIVIDER).val == TerrainMod::LANE_DIVIDER);
        print_line(vformat("[Pass: %s] TerrainMod(LANE_DIVIDER)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            TerrainMod invalid(TerrainMod::MAX);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] TerrainMod(MAX) throws exception", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            TerrainMod invalid(100);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] TerrainMod(100) throws exception", pass)); if (pass) passed++; total++;
    }

    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}

void Tester::direction() const {
    print_line("==================================");
    print_line("@Test: direction"); int passed = 0, total = 0;

    {
        bool pass = (Direction().val == Direction::NONE);
        print_line(vformat("[Pass: %s] Direction() creates NONE", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::E).val == Direction::E);
        print_line(vformat("[Pass: %s] Direction(Direction::E) creates E", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(0b00000001).val == Direction::E);
        print_line(vformat("[Pass: %s] Direction(0b00000001) creates E", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::ALL).val == Direction::ALL);
        print_line(vformat("[Pass: %s] Direction(Direction::ALL) has all bits", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Direction().is_none();
        print_line(vformat("[Pass: %s] Direction() is_none() returns true", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = !Direction(Direction::E).is_none();
        print_line(vformat("[Pass: %s] Direction(Direction::E) is_none() returns false", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::NONE).count() == 0);
        print_line(vformat("[Pass: %s] Direction(Direction::NONE).count() == 0", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::E).count() == 1);
        print_line(vformat("[Pass: %s] Direction(Direction::E).count() == 1", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::NE).count() == 1);
        print_line(vformat("[Pass: %s] Direction(Direction::NE).count() == 1", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::E | Direction::N).count() == 2);
        print_line(vformat("[Pass: %s] Direction(Direction::E | Direction::N).count() == 2", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::ALL).count() == 8);
        print_line(vformat("[Pass: %s] Direction(Direction::ALL).count() == 8", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(0b10110101).count() == 5);
        print_line(vformat("[Pass: %s] Direction(0b10110101).count() == 5", pass)); if (pass) passed++; total++;
    }

    {
        Direction test_dir(Direction::E | Direction::N | Direction::W);
        bool pass = test_dir[0];
        print_line(vformat("[Pass: %s] test_dir[0] (E bit) is true", pass)); if (pass) passed++; total++;
    }

    {
        Direction test_dir(Direction::E | Direction::N | Direction::W);
        bool pass = !test_dir[1];
        print_line(vformat("[Pass: %s] test_dir[1] (NE bit) is false", pass)); if (pass) passed++; total++;
    }

    {
        Direction test_dir(Direction::E | Direction::N | Direction::W);
        bool pass = test_dir[2];
        print_line(vformat("[Pass: %s] test_dir[2] (N bit) is true", pass)); if (pass) passed++; total++;
    }

    {
        Direction test_dir(Direction::E | Direction::N | Direction::W);
        bool pass = test_dir[4];
        print_line(vformat("[Pass: %s] test_dir[4] (W bit) is true", pass)); if (pass) passed++; total++;
    }

    {
        Direction test_dir(Direction::E | Direction::N | Direction::W);
        bool pass = !test_dir[7];
        print_line(vformat("[Pass: %s] test_dir[7] (SE bit) is false", pass)); if (pass) passed++; total++;
    }

    {
        Direction test_dir(Direction::E | Direction::N | Direction::W);
        bool pass = !test_dir[-1];
        print_line(vformat("[Pass: %s] test_dir[-1] (out of bounds) is false", pass)); if (pass) passed++; total++;
    }

    {
        Direction test_dir(Direction::E | Direction::N | Direction::W);
        bool pass = !test_dir[8];
        print_line(vformat("[Pass: %s] test_dir[8] (out of bounds) is false", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction() == Direction());
        print_line(vformat("[Pass: %s] Direction() == Direction()", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::E) == Direction(Direction::E));
        print_line(vformat("[Pass: %s] Direction(Direction::E) == Direction(Direction::E)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::E) != Direction(Direction::N));
        print_line(vformat("[Pass: %s] Direction(Direction::E) != Direction(Direction::N)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(Direction::E | Direction::N) == Direction(0b00000101));
        print_line(vformat("[Pass: %s] Direction(Direction::E | Direction::N) == Direction(0b00000101)", pass)); if (pass) passed++; total++;
    }

    {
        Direction or_test = Direction(Direction::E);
        bool pass = ((or_test |= Direction(Direction::N)) == Direction(Direction::E | Direction::N));
        print_line(vformat("[Pass: %s] or_test |= Direction(N) results in E|N", pass)); if (pass) passed++; total++;
    }

    {
        Direction or_test = Direction(Direction::E);
        or_test |= Direction(Direction::N);
        bool pass = (or_test.count() == 2);
        print_line(vformat("[Pass: %s] or_test now has count() == 2", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(Direction::E) | Direction(Direction::N)) == Direction(Direction::E | Direction::N));
        print_line(vformat("[Pass: %s] Direction(E) | Direction(N) == Direction(E|N)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(Direction::E | Direction::W) | Direction(Direction::N | Direction::S)) == Direction(Direction::E | Direction::W | Direction::N | Direction::S));
        print_line(vformat("[Pass: %s] Direction(E|W) | Direction(N|S) == Direction(E|W|N|S)", pass)); if (pass) passed++; total++;
    }

    {
        Direction and_test = Direction(Direction::E | Direction::N | Direction::W);
        bool pass = ((and_test &= Direction(Direction::E | Direction::N)) == Direction(Direction::E | Direction::N));
        print_line(vformat("[Pass: %s] and_test &= Direction(E|N) results in E|N", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(Direction::E | Direction::N) & Direction(Direction::N | Direction::W)) == Direction(Direction::N));
        print_line(vformat("[Pass: %s] Direction(E|N) & Direction(N|W) == Direction(N)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(Direction::E) & Direction(Direction::N)) == Direction(Direction::NONE));
        print_line(vformat("[Pass: %s] Direction(E) & Direction(N) == Direction(NONE)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(Direction::ALL) & Direction(Direction::E)) == Direction(Direction::E));
        print_line(vformat("[Pass: %s] Direction(ALL) & Direction(E) == Direction(E)", pass)); if (pass) passed++; total++;
    }

    {
        Direction add_test = Direction(Direction::E);
        bool pass = ((add_test += Direction(Direction::N)).val == 0b00000101);
        print_line(vformat("[Pass: %s] add_test += Direction(N) results in 0b00000101", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(0b00000001) + Direction(0b00000010)) == Direction(0b00000011));
        print_line(vformat("[Pass: %s] Direction(0b00000001) + Direction(0b00000010) == Direction(0b00000011)", pass)); if (pass) passed++; total++;
    }

    {
        Direction sub_test = Direction(0b00000101);
        bool pass = ((sub_test -= Direction(0b00000001)).val == 0b00000100);
        print_line(vformat("[Pass: %s] sub_test -= Direction(0b00000001) results in 0b00000100", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(0b00000101) - Direction(0b00000001)) == Direction(0b00000100));
        print_line(vformat("[Pass: %s] Direction(0b00000101) - Direction(0b00000001) == Direction(0b00000100)", pass)); if (pass) passed++; total++;
    }

    {
        Direction match_test1(Direction::E | Direction::N);
        bool pass = match_test1.no_matches(Direction(Direction::W | Direction::S));
        print_line(vformat("[Pass: %s] match_test1.no_matches(Direction(W|S)) is true", pass)); if (pass) passed++; total++;
    }

    {
        Direction match_test1(Direction::E | Direction::N);
        Direction match_test2(Direction::N | Direction::W);
        bool pass = !match_test1.no_matches(match_test2);
        print_line(vformat("[Pass: %s] match_test1.no_matches(match_test2) is false (N matches)", pass)); if (pass) passed++; total++;
    }

    {
        Direction match_test1(Direction::E | Direction::N);
        Direction match_test2(Direction::N | Direction::W);
        bool pass = match_test1.atleast1_matches(match_test2);
        print_line(vformat("[Pass: %s] match_test1.atleast1_matches(match_test2) is true (N matches)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Direction(Direction::E).no_matches(Direction(Direction::W));
        print_line(vformat("[Pass: %s] Direction(E).no_matches(Direction(W)) is true", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Direction().no_matches(Direction());
        print_line(vformat("[Pass: %s] Direction().no_matches(Direction()) is true (both NONE)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection().val == Direction::NONE);
        print_line(vformat("[Pass: %s] SoloDirection() creates NONE", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::E).val == Direction::E);
        print_line(vformat("[Pass: %s] SoloDirection(Direction::E) is valid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::N).val == Direction::N);
        print_line(vformat("[Pass: %s] SoloDirection(Direction::N) is valid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::NONE).val == Direction::NONE);
        print_line(vformat("[Pass: %s] SoloDirection(Direction::NONE) is valid", pass)); if (pass) passed++; total++;
    }

    {
        Direction solo_source(Direction::W);
        bool pass = (SoloDirection(solo_source).val == Direction::W);
        print_line(vformat("[Pass: %s] SoloDirection(solo_source) is valid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            SoloDirection invalid(Direction::E | Direction::N);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] SoloDirection(E|N) throws exception", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            SoloDirection invalid(Direction::ALL);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] SoloDirection(ALL) throws exception", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = false;
        try {
            Direction multi(Direction::E | Direction::W);
            SoloDirection invalid(multi);
        } catch (const std::invalid_argument& e) {
            pass = true;
        }
        print_line(vformat("[Pass: %s] SoloDirection(Direction with multiple bits) throws exception", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::E).to_vec2i() == Vec2i(1,0));
        print_line(vformat("[Pass: %s] SoloDirection(E).to_vec2i() == Vec2i(1,0)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::NE).to_vec2i() == Vec2i(1,-1));
        print_line(vformat("[Pass: %s] SoloDirection(NE).to_vec2i() == Vec2i(1,-1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::N).to_vec2i() == Vec2i(0,-1));
        print_line(vformat("[Pass: %s] SoloDirection(N).to_vec2i() == Vec2i(0,-1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::NW).to_vec2i() == Vec2i(-1,-1));
        print_line(vformat("[Pass: %s] SoloDirection(NW).to_vec2i() == Vec2i(-1,-1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::W).to_vec2i() == Vec2i(-1,0));
        print_line(vformat("[Pass: %s] SoloDirection(W).to_vec2i() == Vec2i(-1,0)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::SW).to_vec2i() == Vec2i(-1,1));
        print_line(vformat("[Pass: %s] SoloDirection(SW).to_vec2i() == Vec2i(-1,1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::S).to_vec2i() == Vec2i(0,1));
        print_line(vformat("[Pass: %s] SoloDirection(S).to_vec2i() == Vec2i(0,1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::SE).to_vec2i() == Vec2i(1,1));
        print_line(vformat("[Pass: %s] SoloDirection(SE).to_vec2i() == Vec2i(1,1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (SoloDirection(Direction::NONE).to_vec2i() == Vec2i(0,0));
        print_line(vformat("[Pass: %s] SoloDirection(NONE).to_vec2i() == Vec2i(0,0)", pass)); if (pass) passed++; total++;
    }

    {
        SoloDirection solo_inherit(Direction::E);
        Direction base_from_solo = solo_inherit;
        bool pass = (base_from_solo.val == Direction::E);
        print_line(vformat("[Pass: %s] SoloDirection can be assigned to Direction", pass)); if (pass) passed++; total++;
    }

    {
        SoloDirection solo_inherit(Direction::E);
        bool pass = (solo_inherit.count() == 1);
        print_line(vformat("[Pass: %s] SoloDirection inherits count() method", pass)); if (pass) passed++; total++;
    }

    {
        SoloDirection solo_inherit(Direction::E);
        bool pass = !solo_inherit.is_none();
        print_line(vformat("[Pass: %s] SoloDirection inherits is_none() method", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = SoloDirection().is_none();
        print_line(vformat("[Pass: %s] SoloDirection(NONE).is_none() is true", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Direction(0b11111111).count() == 8);
        print_line(vformat("[Pass: %s] Direction with all bits set has count == 8", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Direction(0).is_none();
        print_line(vformat("[Pass: %s] Direction(0).is_none() is true", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Direction(Direction::E) | Direction(Direction::N) | Direction(Direction::W) | Direction(Direction::S)).count() == 4);
        print_line(vformat("[Pass: %s] Multiple OR operations: (E|N|W|S).count() == 4", pass)); if (pass) passed++; total++;
    }

    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}

void Tester::speed() const {
    print_line("==================================");
    print_line("@Test: speed"); int passed = 0, total = 0;

    {
        bool pass = (Speed().val == 0.0f);
        print_line(vformat("[Pass: %s] Speed() creates zero speed", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Speed(5.0f).val == 5.0f);
        print_line(vformat("[Pass: %s] Speed(5.0f) creates speed with val=5.0", pass)); if (pass) passed++; total++;
    }

    {
        Speed test_mph(MPH(60), 1, 10);
        bool pass = (abs(test_mph.val - 8.8f) < 0.01f);
        print_line(vformat("[Pass: %s] Speed(60 mph, 1 sec/step, 10 ft/cell) ≈ 8.8 cells/step", pass)); if (pass) passed++; total++;
    }

    {
        constexpr Speed compile_time(5.0f);
        bool pass = (compile_time.val == 5.0f);
        print_line(vformat("[Pass: %s] constexpr Speed works at compile time", pass)); if (pass) passed++; total++;
    }

    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}

void Tester::cell_vec() const {
    print_line("==================================");
    print_line("@Test: Vec2i & Cell");
    int passed = 0, total = 0;

    {
        bool pass = (Vec2i() == Vec2i(0,0));
        print_line(vformat("[Pass: %s] Vec2i() == Vec2i(0,0)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Vec2i(5,10).x == 5 && Vec2i(5,10).y == 10);
        print_line(vformat("[Pass: %s] Vec2i(5,10).x == 5 and .y == 10", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Vec2i(1,1) == Vec2i(1,1));
        print_line(vformat("[Pass: %s] Vec2i(1,1) == Vec2i(1,1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Vec2i(1,1) != Vec2i(2,3));
        print_line(vformat("[Pass: %s] Vec2i(1,1) != Vec2i(2,3)", pass)); if (pass) passed++; total++;
    }

    {
        Vec2i vec_add = Vec2i(1,1);
        bool pass = ((vec_add += Vec2i(2,3)) == Vec2i(3,4));
        print_line(vformat("[Pass: %s] vec_add += Vec2i(2,3) == Vec2i(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        Vec2i vec_add = Vec2i(1,1);
        vec_add += Vec2i(2,3);
        bool pass = (vec_add == Vec2i(3,4));
        print_line(vformat("[Pass: %s] vec_add is now Vec2i(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Vec2i(1,1) + Vec2i(2,3)) == Vec2i(3,4));
        print_line(vformat("[Pass: %s] Vec2i(1,1) + Vec2i(2,3) == Vec2i(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        Vec2i vec_sub = Vec2i(5,8);
        bool pass = ((vec_sub -= Vec2i(2,3)) == Vec2i(3,5));
        print_line(vformat("[Pass: %s] vec_sub -= Vec2i(2,3) == Vec2i(3,5)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Vec2i(5,8) - Vec2i(2,3)) == Vec2i(3,5));
        print_line(vformat("[Pass: %s] Vec2i(5,8) - Vec2i(2,3) == Vec2i(3,5)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell().is_invalid();
        print_line(vformat("[Pass: %s] Cell() creates invalid cell", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(1,1).is_valid();
        print_line(vformat("[Pass: %s] Cell(1,1) is valid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(2,3).is_valid();
        print_line(vformat("[Pass: %s] Cell(2,3) is valid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(-1,-1).is_invalid();
        print_line(vformat("[Pass: %s] Cell(-1,-1) is invalid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(Vec2i(5,10)).x == 5 && Cell(Vec2i(5,10)).y == 10);
        print_line(vformat("[Pass: %s] Cell(Vec2i(5,10)) creates cell at (5,10)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(Vec2i(-4,-5)).is_invalid();
        print_line(vformat("[Pass: %s] Cell(Vec2i(-4,-5)) is invalid", pass)); if (pass) passed++; total++;
    }

    {
        Cell test_cell = Cell(7,9);
        bool pass = (test_cell.x == 7);
        print_line(vformat("[Pass: %s] test_cell.x == 7", pass)); if (pass) passed++; total++;
    }

    {
        Cell test_cell = Cell(7,9);
        bool pass = (test_cell.y == 9);
        print_line(vformat("[Pass: %s] test_cell.y == 9", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(0,0).is_valid();
        print_line(vformat("[Pass: %s] Cell(0,0) is valid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(-1,5).is_invalid();
        print_line(vformat("[Pass: %s] Cell(-1,5) is invalid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(5,-1).is_invalid();
        print_line(vformat("[Pass: %s] Cell(5,-1) is invalid", pass)); if (pass) passed++; total++;
    }

    {
        Cell invalidate_test = Cell(5,5);
        invalidate_test.invalidate();
        bool pass = invalidate_test.is_invalid();
        print_line(vformat("[Pass: %s] Cell(5,5).invalidate() makes it invalid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(1,1).in_bounds(0,0,2,3);
        print_line(vformat("[Pass: %s] Cell(1,1) is in bounds [0-2, 0-3]", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = !Cell(2,3).in_bounds(0,0,1,2);
        print_line(vformat("[Pass: %s] Cell(2,3) is NOT in bounds [0-1, 0-2]", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = !Cell().in_bounds(0,0,1,2);
        print_line(vformat("[Pass: %s] Cell() is NOT in bounds [0-1, 0-2]", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(0,0).in_bounds(0,0,0,0);
        print_line(vformat("[Pass: %s] Cell(0,0) is in bounds [0-0, 0-0]", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = !Cell(5,5).in_bounds(0,0,4,4);
        print_line(vformat("[Pass: %s] Cell(5,5) is NOT in bounds [0-4, 0-4]", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell() == Cell());
        print_line(vformat("[Pass: %s] Cell() == Cell()", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(1,1) == Cell(1,1));
        print_line(vformat("[Pass: %s] Cell(1,1) == Cell(1,1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(1,1) != Cell(2,3));
        print_line(vformat("[Pass: %s] Cell(1,1) != Cell(2,3)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(0,0) != Cell());
        print_line(vformat("[Pass: %s] Cell(0,0) != Cell()", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(Cell(1,1), 2) == Cell(0,0));
        print_line(vformat("[Pass: %s] Cell(Cell(1,1), 2) == Cell(0,0)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(Cell(2,3), 2) == Cell(1,1));
        print_line(vformat("[Pass: %s] Cell(Cell(2,3), 2) == Cell(1,1)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(Cell(2,0), 2) == Cell(1,0));
        print_line(vformat("[Pass: %s] Cell(Cell(2,0), 2) == Cell(1,0)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(Cell(5,7), 2) == Cell(2,3));
        print_line(vformat("[Pass: %s] Cell(Cell(5,7), 2) == Cell(2,3)", pass)); if (pass) passed++; total++;
    }

    {
        Cell add_cell = Cell(1,1);
        bool pass = ((add_cell += Cell(2,3)) == Cell(3,4));
        print_line(vformat("[Pass: %s] add_cell += Cell(2,3) == Cell(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        Cell add_cell = Cell(1,1);
        add_cell += Cell(2,3);
        bool pass = (add_cell == Cell(3,4));
        print_line(vformat("[Pass: %s] add_cell is now Cell(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        Cell add_cell = Cell(3,4);
        bool pass = ((add_cell += Cell(-1,-1)) == Cell(2,3));
        print_line(vformat("[Pass: %s] add_cell += Cell(-1,-1) == Cell(2,3)", pass)); if (pass) passed++; total++;
    }

    {
        Cell add_vec_cell = Cell(1,1);
        bool pass = ((add_vec_cell += Vec2i(2,3)) == Cell(3,4));
        print_line(vformat("[Pass: %s] add_vec_cell += Vec2i(2,3) == Cell(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        Cell add_vec_cell = Cell(3,4);
        bool pass = ((add_vec_cell += Vec2i(-4,-2)) == Cell(-1,2));
        print_line(vformat("[Pass: %s] add_vec_cell += Vec2i(-4,-2) == Cell(-1,2)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Cell(1,1) + Cell(2,3)) == Cell(3,4));
        print_line(vformat("[Pass: %s] Cell(1,1) + Cell(2,3) == Cell(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Cell(1,1) + Vec2i(2,3)) == Cell(3,4));
        print_line(vformat("[Pass: %s] Cell(1,1) + Vec2i(2,3) == Cell(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Vec2i(1,1) + Cell(2,3)) == Cell(3,4));
        print_line(vformat("[Pass: %s] Vec2i(1,1) + Cell(2,3) == Cell(3,4)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Cell(-3,-2) + Cell(4,3)) == Cell(1,1));
        print_line(vformat("[Pass: %s] Cell(-3,-2) + Cell(4,3) == Cell(1,1)", pass)); if (pass) passed++; total++;
    }

    {
        Cell complex_add = Cell(1,1);
        bool pass = ((complex_add += Cell(-3,-2) + Cell(4,3)) == Cell(2,2));
        print_line(vformat("[Pass: %s] complex_add += Cell(-3,-2) + Cell(4,3) == Cell(2,2)", pass)); if (pass) passed++; total++;
    }

    {
        Cell conv_cell = Cell(5,10);
        Vec2i cast_vec = static_cast<Vec2i>(conv_cell);
        bool pass = (cast_vec == Vec2i(5,10));
        print_line(vformat("[Pass: %s] Vec2i cast_vec = conv_cell; creates Vec2i(5,10)", pass)); if (pass) passed++; total++;
    }

    {
        Cell conv_cell = Cell(5,10);
        Vec2i explicit_vec = conv_cell.to_vec2i();
        bool pass = (explicit_vec == Vec2i(5,10));
        print_line(vformat("[Pass: %s] conv_cell.to_vec2i() == Vec2i(5,10)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = ((Vec2i(1,1) + Cell(2,3)) == Cell(3,4));
        print_line(vformat("[Pass: %s] Vec2i(1,1) + Cell(2,3) results in Cell type", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(0,-1).is_invalid();
        print_line(vformat("[Pass: %s] Cell(0,-1) is invalid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(-1,0).is_invalid();
        print_line(vformat("[Pass: %s] Cell(-1,0) is invalid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(0,0).is_valid();
        print_line(vformat("[Pass: %s] Cell(0,0) is valid", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = Cell(10000,10000).is_valid();
        print_line(vformat("[Pass: %s] Very large coordinates Cell(10000,10000) is valid", pass)); if (pass) passed++; total++;
    }

    {
        Cell chain_test = Cell(1,1);
        bool pass = (((chain_test += Vec2i(2,2)) += Cell(3,3)) == Cell(6,6));
        print_line(vformat("[Pass: %s] Chained operations: (chain_test += Vec2i(2,2)) += Cell(3,3) == Cell(6,6)", pass)); if (pass) passed++; total++;
    }

    {
        bool pass = (Cell(1,2).to_idx(3) == 7);
        print_line(vformat("[Pass: %s] Cell(1,2) cols = 3 -> idx == 7", pass)); if (pass) passed++; total++;
    }

    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}





