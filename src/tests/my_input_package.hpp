#pragma once
#include <godot_cpp/classes/image.hpp>
#include "../input_package.hpp"

using namespace godot;

struct MyInputPackage {
    static Ref<Image> create_image_r8(int cols, int rows, uint8_t fill_r8) {
        Ref<Image> image = Image::create(cols, rows, false, Image::FORMAT_R8);
        image->fill(Color(fill_r8 / 255.0f, 0, 0, 1));
        return image;
    }

    static Ref<Image> create_image_r8(int cols, int rows, const std::vector<uint8_t>& list_r8, uint8_t fill_r8 = 0) {
        Ref<Image> image = create_image_r8(cols, rows, fill_r8);
        if (list_r8.empty()) { return image; }
        int i = 0;
        for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Color px = Color(list_r8[i] / 255.0f, 0, 0, 1);
            image->set_pixel(x, y, px);
            i = (i+1) % list_r8.size();
        }}
    }

    static Ref<InputPackage> emulate(int cols, int rows, TT fill_tt, TM fill_tm, Dir fill_dir, MPH fill_mph) {
        Ref<Image> tt_img = create_image_r8(cols, rows, fill_tt.val);
        Ref<Image> tm_img = create_image_r8(cols, rows, fill_tm.val);
        Ref<Image> dir_img = create_image_r8(cols, rows, fill_dir.val);
        Ref<Image> mph_img = create_image_r8(cols, rows, fill_mph.val);
        Ref<InputPackage> input = memnew(InputPackage);
        input->set_image_matrices(tt_img, tm_img, dir_img, mph_img);
        return input;
    }

};
