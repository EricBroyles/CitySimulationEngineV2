class_name Utils
## COLORS

static func combine_bit_strs(bit_strs: PackedStringArray) -> String:
	#this is kinda dumb, just use an iteger and then bitwise | (it works, too lazy to fix)
	#assumes bit_strs are all of the same size
	# ex: 00110010
	#     01010101
	#     10000000
	# ->  11110111
	var num: int = bit_strs.size()
	var length: int = bit_strs[0].length()
	var result: String = ""
	for i in length:
		result += "0"
		for n in num: if bit_strs[n][i] == "1": result[i] = "1"; break;
	return result

static func ivec4_to_rgba8(ivec4: Vector4i) -> Color:
	#rgba8: represents ints from 0 -> 255
	var scaled_vec: Vector4 = ivec4 / 255.0
	return Color(scaled_vec.x, scaled_vec.y, scaled_vec.z, scaled_vec.w)
	
