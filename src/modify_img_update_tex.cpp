#include "modify_img_update_tex.h"
#include <godot_cpp/variant/utility_functions.hpp>

void ExpModifyImgUpdateTex::_bind_methods() {
	ClassDB::bind_method(D_METHOD("make_stripes", "img", "tex"), &ExpModifyImgUpdateTex::make_stripes);
    
}

void ExpModifyImgUpdateTex::make_stripes(Ref<Image> img, Ref<ImageTexture> tex) {

    if (img.is_null() || tex.is_null()) {
		UtilityFunctions::printerr("Img is null or tex is null");
	}


    int w = img->get_width();
    int h = img->get_height();
    for (int x = 0; x < w; x++) {
        bool white = (x / 10) % 2 == 0;   // stripe width = 10 pixels
        Color color = white ? Color(1,1,1) : Color(0,0,0);

        for (int y = 0; y < h; y++) {
            img->set_pixel(x, y, color);
        }
    }


    // Now update the texture from the modified image
    tex->update(img);
}
