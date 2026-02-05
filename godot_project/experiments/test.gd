extends Node

func _ready() -> void:
	var tester: Tester = Tester.new()
	#tester.cell_vec_tests()
	#tester.direction_tests()
	#tester.speed_tests()
	#tester.terrain_type_tests()
	#tester.terrain_mod_tests()
	#tester.matrix_tests()
	#tester.image_matrix_tests()
	#tester.world_tests()
	#tester.cmid_tests()
	#tester.cm_tests()
	#tester.timing()
	tester.construct_cm()
	
