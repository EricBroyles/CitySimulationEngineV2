#pragma once
#include "terrain_type.hpp"
#include "direction.hpp"
#include "base_world.hpp"
#include "connectivity_matrix.hpp"

using namespace godot;

class MyConnectivityMatrix {
public:
    static void one_tt_one_dir(int cols, int rows, TT p_tt, Dir p_dir) {
        Ref<Image> tt = BaseWorld::emulate_image_r8(cols, rows, p_tt.val, {});
        Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, p_dir.val, {});
        Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
        ConnectivityMatrix cm = ConnectivityMatrix(base);
        cm.display_full();
    }
    static void list_tt_list_dir(int cols, int rows, std::vector<uint8_t> list_tt, std::vector<uint8_t> list_dir) {
        Ref<Image> tt = BaseWorld::emulate_image_r8(cols, rows, TT::NONE, list_tt); //NONE is just the background 
        Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, Dir::NONE, list_dir); //NONE is just the background 
        Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
        ConnectivityMatrix cm = ConnectivityMatrix(base);
        cm.display_full();
    }
    static void w_connection(const Dir p_dir) {
        int cols = 5;
        int rows = 3;
        static const Matrix<uint8_t> tt_matrix = Matrix<uint8_t>(cols, rows, {
            TT::PARKING, TT::BARRIER, TT::PARKING, TT::BARRIER, TT::PARKING,
            TT::PARKING, TT::BARRIER, TT::PARKING, TT::BARRIER, TT::PARKING,
            TT::BARRIER, TT::PARKING, TT::BARRIER, TT::PARKING, TT::BARRIER});
        Ref<Image> tt = BaseWorld::emulate_image_r8_from_matrix(tt_matrix); 
        Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, p_dir.val, {}); 
        Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
        ConnectivityMatrix cm = ConnectivityMatrix(base);
        cm.display_full();
    }

    //make each of these as arr of arr {{}} of TT and or Dir

    //NE Diagonal Divide with Bottom hole

    //NW Diagonal Divide with Bottom hole

    //NE Diagonal Divide with Top hole

    //NW Diagonal Divide with top hole

    //Trickle upwards

    //W connection

    //spiral open to the bottom left

};
