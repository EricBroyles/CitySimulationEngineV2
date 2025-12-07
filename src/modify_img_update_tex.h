#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/image.hpp"
#include "godot_cpp/classes/image_texture.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp" 

using namespace godot;

class ExpModifyImgUpdateTex : public RefCounted {
	GDCLASS(ExpModifyImgUpdateTex, RefCounted);

protected:
	static void _bind_methods();

public:
	ExpModifyImgUpdateTex() = default;
	~ExpModifyImgUpdateTex() override = default;

	void make_stripes(Ref<Image> img, Ref<ImageTexture> tex);
};

//#pragma once
//
//#include "godot_cpp/classes/ref.hpp"
//#include "godot_cpp/classes/ref_counted.hpp"
//#include "godot_cpp/classes/image.hpp"
//#include "godot_cpp/classes/image_texture.hpp"
//#include "godot_cpp/core/class_db.hpp"
//#include "godot_cpp/classes/wrapped.hpp"
//#include "godot_cpp/core/object.hpp"
//
///*
//in Progress
//find stuff inside of godot-cpp/include 
//How to write documantation in C++?
//How to modify a passed image and update a texutre?
//What is ref_counted
//what is wrapped
//
//
//hi
//*/
//
//using namespace godot;
//
//class ExpModifyImgUpdateTex : public RefCounted {
//	GDCLASS(ExpModifyImgUpdateTex, RefCounted);
//
//protected:
//	static void _bind_methods();
//
//public:
//	ExpModifyImgUpdateTex() = default;
//	~ExpModifyImgUpdateTex() override = default;
//
//	void make_stripes(Ref<Image> img, Ref<ImageTexture> tex);
//};


//#pragma once
//
//#include "godot_cpp/classes/ref_counted.hpp"
//#include "godot_cpp/classes/wrapped.hpp"
//#include "godot_cpp/variant/variant.hpp"
//
//using namespace godot;
//
//class ExampleClass : public RefCounted {
//	GDCLASS(ExampleClass, RefCounted)
//
//protected:
//	static void _bind_methods();
//
//public:
//	ExampleClass() = default;
//	~ExampleClass() override = default;
//
//	void print_type(const Variant &p_variant) const;
//};
