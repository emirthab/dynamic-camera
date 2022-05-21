#include "DynamicCamera.hpp"

void DynamicCamera::_register_methods()
{
    register_property<DynamicCamera>("fixed_zoom", &DynamicCamera::fixedZoom, true, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, "bool");
    register_property<DynamicCamera>("tolerance", &DynamicCamera::cameraTolerance, 100, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_RESOURCE_TYPE, "int");
    register_property<DynamicCamera>("stretch", &DynamicCamera::stretch, false);
    register_property<DynamicCamera>("speed", &DynamicCamera::cameraSpeed, 1);
    register_method("_ready", &DynamicCamera::_ready);
    register_method("_physics_process", &DynamicCamera::_physics_process);
    register_method("onWindowSizeChanged", &DynamicCamera::onWindowSizeChanged);
}

void DynamicCamera::_init() { }

void DynamicCamera::_ready()
{   
    defaultZoom = get_zoom();
    defaultWindowSize = get_viewport_rect().size;
    get_node("/root")->connect("size_changed", this, "onWindowSizeChanged");
}

void DynamicCamera::_physics_process(const double p_delta) {
    Vector2 camera_pos = get_global_mouse_position();
    Vector2 parentGlobalPosition = ( (Node2D*)get_parent() )->get_global_position();
    
    camera_pos.x = Math::clamp( camera_pos.x, 
                                parentGlobalPosition.x - cameraTolerance,
                                parentGlobalPosition.x + cameraTolerance);

    camera_pos.y = Math::clamp( camera_pos.y, 
                                parentGlobalPosition.y - cameraTolerance,
                                parentGlobalPosition.y + cameraTolerance);

    Vector2 realPos;
    realPos.x = Math::lerp( float(get_global_position().x), 
                            float(camera_pos.x), 
                            float(p_delta) * cameraSpeed);

    realPos.y = Math::lerp( float(get_global_position().y), 
                            float(camera_pos.y), 
                            float(p_delta) * cameraSpeed);

    set_global_position(realPos);
}

void DynamicCamera::onWindowSizeChanged() {
    float xRatio = get_viewport_rect().size.x / defaultWindowSize.x;
    float yRatio = get_viewport_rect().size.y / defaultWindowSize.y;
    Vector2 _zoom;

    if(stretch == true){
        _zoom = Vector2(defaultZoom.x / xRatio, defaultZoom.y / yRatio);
    }
    else{
        _zoom = Vector2(defaultZoom.x / xRatio, defaultZoom.y / xRatio);
    }

    set_zoom(_zoom);
}