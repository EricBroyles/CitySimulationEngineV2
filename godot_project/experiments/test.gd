extends Node

func _ready() -> void:
	var tester: Tester = Tester.new()
	tester.cell_vec_tests()
	tester.direction_tests()
	tester.speed_tests()
	
