extends Node

func _ready() -> void:
	var tester: Tester = Tester.new()
	
	var start_time = Time.get_ticks_usec()
	
	#tester.cell_vec()
	#tester.speed()
	#tester.direction()
	#tester.terrain_mod()
	#tester.terrain_type()
	#tester.matrix()
	#tester.cmid()
	#tester.construct_cm()
	#tester.benchmark_cm()
	#tester.cm()
	#tester.timing()
	#tester.world()
	tester.idx()
	
	var end_time = Time.get_ticks_usec()
	var elapsed_ms = (end_time - start_time) / 1000.0
	var elapsed_sec = elapsed_ms / 1000.0
	
	print("Total test execution time: %.3f ms (%.3f seconds)" % [elapsed_ms, elapsed_sec]) #Total test execution time: 6284.278 ms (6.284 seconds) before pointer
	
	# Total test execution time: 7105.149 ms (7.105 seconds) with pointer but with std::vector<TT> new_data(mat.cols * mat.rows); after a smaller variable (memory ineffoceint)

	
