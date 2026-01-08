extends Node

@onready var sprite = %Sprite2D

func _ready() -> void:
	var example := ExampleClass.new()
	example.print_type(example)
	var thing: ExpModifyImgUpdateTex = ExpModifyImgUpdateTex.new()
	print(thing)
	var img: Image = Image.create_empty(100,100,false, Image.FORMAT_RGBA8)
	var tex: ImageTexture = ImageTexture.create_from_image(img)
	thing.make_stripes(img, tex)
	sprite.texture = tex
	
	
	
