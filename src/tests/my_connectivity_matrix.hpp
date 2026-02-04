#pragma once
#include <chrono>
#include "../dev/connectivity_matrix.hpp"
#include "my_timing_experiments.hpp"
#include "my_input_package.hpp"
#include "my_matrix.hpp"

using namespace godot;

struct MyConnectivityMatrix {

    static void display(const CM& cm) {
        print_line("Walk: ");
        MyMatrix<CMID>::display_full_as_int(cm.get_walk());
        print_line("Drive: ");
        MyMatrix<CMID>::display_full_as_int(cm.get_drive());
    }

    static CM create_from_one_tt_one_dir(int cols, int rows, TT p_tt, Dir p_dir) {
        Ref<InputPackage> input = MyInputPackage::emulate(cols, rows, p_tt, TM(), p_dir, MPH());
        BaseWorld base = BaseWorld(input);
        auto start = MyTimingExperiments::now();
        CM cm = CM(base);
        MyTimingExperiments::display_duration("CM Load Time:", start);
        return cm;
    }



};



// #pragma once
// #include <chrono>
// #include "terrain_type.hpp"
// #include "direction.hpp"
// #include "base_world.hpp"
// #include "connectivity_matrix.hpp"

// using namespace godot;

// class MyConnectivityMatrix {
// public:
//     static void one_tt_one_dir(int cols, int rows, TT p_tt, Dir p_dir, bool do_display_full = true) {
//         Ref<Image> tt = BaseWorld::emulate_image_r8(cols, rows, p_tt.val, {});
//         Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, p_dir.val, {});
//         Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);

//         auto start = std::chrono::high_resolution_clock::now();
//         ConnectivityMatrix cm = ConnectivityMatrix(base);
//         auto end = std::chrono::high_resolution_clock::now();

//         if(do_display_full) { cm.display_full(); }
//         print_line(vformat("walk groups: %d | drive groups: %d", cm.num_walk_groups, cm.num_drive_groups));
        
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("Completed in %.2f ms", duration.count() / 1000.0));      
//     }
//     static void list_tt_list_dir(int cols, int rows, std::vector<uint8_t> list_tt, std::vector<uint8_t> list_dir) {
//         Ref<Image> tt = BaseWorld::emulate_image_r8(cols, rows, TT::NONE, list_tt); //NONE is just the background 
//         Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, Dir::NONE, list_dir); //NONE is just the background 
//         Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
//         ConnectivityMatrix cm = ConnectivityMatrix(base);
//         cm.display_full();
//         print_line(vformat("walk groups: %d | drive groups: %d", cm.num_walk_groups, cm.num_drive_groups));
//     }
//     static void w_connection(const Dir p_dir) {
//         int cols = 5;
//         int rows = 3;
//         static const Matrix<uint8_t> tt_matrix = Matrix<uint8_t>(cols, rows, {
//             TT::PARKING, TT::BARRIER, TT::PARKING, TT::BARRIER, TT::PARKING,
//             TT::PARKING, TT::BARRIER, TT::PARKING, TT::BARRIER, TT::PARKING,
//             TT::BARRIER, TT::PARKING, TT::BARRIER, TT::PARKING, TT::BARRIER
//         });
//         Ref<Image> tt = BaseWorld::emulate_image_r8_from_matrix(tt_matrix); 
//         Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, p_dir.val, {}); 
//         Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
//         ConnectivityMatrix cm = ConnectivityMatrix(base);
//         cm.display_full();
//         print_line(vformat("walk groups: %d | drive groups: %d", cm.num_walk_groups, cm.num_drive_groups));
//     }

//     static void bottom_leak(const Dir p_dir) {
//         int cols = 10;
//         int rows = 3;
//         static const Matrix<uint8_t> tt_matrix = Matrix<uint8_t>(cols, rows, {
//             TT::PARKING, TT::PARKING, TT::BARRIER, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING,
//             TT::PARKING, TT::PARKING, TT::BARRIER, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING,
//             TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING, TT::PARKING
//         });
//         Ref<Image> tt = BaseWorld::emulate_image_r8_from_matrix(tt_matrix); 
//         Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, p_dir.val, {}); 
//         Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
//         BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
//         ConnectivityMatrix cm = ConnectivityMatrix(base);
//         cm.display_full();
//         print_line(vformat("walk groups: %d | drive groups: %d", cm.num_walk_groups, cm.num_drive_groups));
//     }

//     //performance test. for a 4096 by 4096.
// };
