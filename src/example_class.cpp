#include "example_class.h"

#include <godot_cpp/variant/vector2i.hpp>

// int main() {
//     godot::Vector2i cell(5, 10);
//     cell.x;  // 5
//     cell.y;  // 10
//     std::cout << "HEllo World" << std::endl;
//     return 0;
// }

void ExampleClass::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass::print_type);
}

void ExampleClass::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

