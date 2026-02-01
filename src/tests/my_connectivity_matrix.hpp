#pragma once
#include "terrain_type.hpp"
#include "direction.hpp"
#include "base_world.hpp"
#include "connectivity_matrix.hpp"

using namespace godot;

class MyConnectivityMatrix {
public:
    static void one_tt_one_dir(int cols, int rows, TerrainType p_tt, Direction p_dir) {
        Ref<Image> tt = BaseWorld::emulate_image_r8(cols, rows, p_tt.val, {});
        Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, p_dir.val, {});
        Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
        ConnectivityMatrix cm = ConnectivityMatrix(base);
        cm.display_full();
    }
    static void list_tt_list_dir(int cols, int rows, std::vector<uint8_t> list_tt, std::vector<uint8_t> list_dir) {
        Ref<Image> tt = BaseWorld::emulate_image_r8(cols, rows, TerrainType::NONE, list_tt);
        Ref<Image> dir = BaseWorld::emulate_image_r8(cols, rows, Direction::NONE, list_dir);
        Ref<Image> tm = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        Ref<Image> mph = BaseWorld::emulate_image_r8(cols, rows, 0, {});
        BaseWorld base = BaseWorld(tt, tm, mph, dir, 0, 0);
        ConnectivityMatrix cm = ConnectivityMatrix(base);
        cm.display_full();
    }

};
