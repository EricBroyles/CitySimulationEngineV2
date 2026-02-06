#include "input_package.hpp"

using namespace godot;

void InputPackage::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_image_matrices", "p_tt", "p_tm", "p_dir", "p_mph"), &InputPackage::set_image_matrices);
	ClassDB::bind_method(D_METHOD("set_sec_per_step", "val"), &InputPackage::set_sec_per_step);
	ClassDB::bind_method(D_METHOD("set_feet_per_cell", "val"), &InputPackage::set_feet_per_cell);
	ClassDB::bind_method(D_METHOD("set_num_steps", "val"), &InputPackage::set_num_steps);
	ClassDB::bind_method(D_METHOD("set_num_humans", "val"), &InputPackage::set_num_humans);
	ClassDB::bind_method(D_METHOD("set_personal_vehicle_ownership_rate", "val"), &InputPackage::set_personal_vehicle_ownership_rate);
	ClassDB::bind_method(D_METHOD("override_avg_mph", "walk_mph", "drive_mph"), &InputPackage::override_avg_mph);
}    