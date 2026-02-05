#pragma once
#include <chrono>
#include <vector>
#include "../dev/connectivity_matrix.hpp"
#include "my_timing_experiments.hpp"
#include "my_input_package.hpp"
#include "my_matrix.hpp"

using namespace godot;

struct MyConnectivityMatrix {
    inline static Matrix<CMID> CMID_BARRIER_4x4{4,4,CMID(CMID::BARRIER)};
    inline static Matrix<CMID> CMID_FULL_4x4{4,4,CMID(0)};
    inline static Matrix<CMID> CMID_HORI_4x4{4,4,{
        CMID(0), CMID(0), CMID(0), CMID(0),
        CMID(4), CMID(4), CMID(4), CMID(4),
        CMID(8), CMID(8), CMID(8), CMID(8),
        CMID(12), CMID(12), CMID(12), CMID(12)}};
    inline static Matrix<CMID> CMID_VERT_4x4{4,4,{
        CMID(0), CMID(1), CMID(2), CMID(3),
        CMID(0), CMID(1), CMID(2), CMID(3),
        CMID(0), CMID(1), CMID(2), CMID(3),
        CMID(0), CMID(1), CMID(2), CMID(3)}};
    inline static Matrix<CMID> CMID_POS_DIAG_4x4{4,4,{
        CMID(0), CMID(1), CMID(2), CMID(3),
        CMID(1), CMID(2), CMID(3), CMID(7),
        CMID(2), CMID(3), CMID(7), CMID(11),
        CMID(3), CMID(7), CMID(11), CMID(15)}}; 
    inline static Matrix<CMID> CMID_NEG_DIAG_4x4{4,4,{
        CMID(0), CMID(1), CMID(2), CMID(3),
        CMID(4), CMID(0), CMID(1), CMID(2),
        CMID(8), CMID(4), CMID(0), CMID(1),
        CMID(12), CMID(8), CMID(4), CMID(0)}};
    inline static Matrix<CMID> W_CONNECTION{5,3,{
        CMID(0), CMID(-1), CMID(0), CMID(-1), CMID(0),
        CMID(0), CMID(-1), CMID(0), CMID(-1), CMID(0),
        CMID(-1), CMID(0), CMID(-1), CMID(0), CMID(-1)}}; 
    inline static Matrix<CMID> BOTTOM_LEAK{7,3,{
        CMID(0), CMID(-1), CMID(2),  CMID(-1), CMID(0), CMID(0), CMID(0),
        CMID(0), CMID(-1), CMID(-1), CMID(-1), CMID(0), CMID(0), CMID(0),
        CMID(0), CMID(0),  CMID(0),  CMID(0),  CMID(0), CMID(0), CMID(0)}}; 

    static void display(const CM& cm) {
        print_line("Walk: ");
        MyMatrix<CMID>::display_full_as_int(cm.get_walk());
        print_line("Drive: ");
        MyMatrix<CMID>::display_full_as_int(cm.get_drive());
    }

    static bool validate_matrices(const CM& cm, const Matrix<CMID>& correct_walk, const Matrix<CMID>& correct_drive) {
        return cm.get_walk() == correct_walk && cm.get_drive() == correct_drive;
    }

    static bool validate_num_groups(const CM& cm, int correct_num_walk_groups, int correct_num_drive_groups) {
        return cm.num_walk_groups == correct_num_walk_groups && cm.num_drive_groups == correct_num_drive_groups;
    }

    static CM create(const Ref<InputPackage> input, bool display_time = false) {
        BaseWorld base = BaseWorld(input);
        auto start = MyTimingExperiments::now();
        CM cm = CM(base);
        if (display_time) MyTimingExperiments::display_duration("CM Load Time:", start);
        return cm;
    }

    static CM create(int cols, int rows, TT p_tt, Dir p_dir, bool display_time = false) {
        Ref<InputPackage> input = MyInputPackage::create(cols, rows, p_tt, TM(), p_dir, MPH());
        return create(input, display_time);
    }

    static CM create(int cols, int rows, const std::vector<TT>& list_tt, const std::vector<Dir> list_dir, bool display_time = false) {
        Ref<InputPackage> input = MyInputPackage::create(cols, rows, list_tt, {}, list_dir, {});
        return create(input, display_time);
    }

    static CM create_w_connection(const Dir fill_dir, bool display_time = false) {
        constexpr TT P = TT(TT::PARKING); 
        constexpr TT B = TT(TT::BARRIER);
        const std::vector<TT> LIST_TT{
            P, B, P, B, P,
            P, B, P, B, P,
            B, P, B, P, B}; // Must match size of W_CONNECTION or will crash silently.
        const std::vector<Dir> LIST_DIR{fill_dir};
        CM cm = create(5, 3, LIST_TT, LIST_DIR, display_time);
        return cm;
    }

    static CM create_bottom_leak(const Dir fill_dir, bool display_time = false) {
        constexpr TT P = TT(TT::PARKING); 
        constexpr TT B = TT(TT::BARRIER);
        const std::vector<TT> LIST_TT{
            P, B, P, B, P, P, P,
            P, B, B, B, P, P, P,
            P, P, P, P, P, P, P}; // Must match size of BOTTOM_LEAK or will crash silently.
        const std::vector<Dir> LIST_DIR{fill_dir};
        CM cm = create(7, 3, LIST_TT, LIST_DIR, display_time);
        return cm;   
    }
};

using MyCM = MyConnectivityMatrix;

