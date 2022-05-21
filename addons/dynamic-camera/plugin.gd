tool
extends EditorPlugin

var dynamic_camera = preload("DynamicCamera.gdns")
var icon = preload("icon.png")

func _enter_tree():
	add_custom_type("DynamicCamera", "Camera2D", dynamic_camera, icon)

func _exit_tree():
	remove_custom_type("DynamicCamera")
