#include <Godot.hpp>
#include <Camera2D.hpp>
#include <Vector2.hpp>
#include <Node2D.hpp>
#include <Math.hpp>

using namespace godot;
class DynamicCamera : public Camera2D
{
    private:
        GODOT_CLASS(DynamicCamera, Camera2D)


    public:
        static void _register_methods();
        void _physics_process(const double p_delta);
        void _init();
        void _ready();

        bool fixedZoom = true;
        bool stretch = false;
        int cameraTolerance = 100;
        int cameraSpeed = 1;
        Vector2 defaultWindowSize;
        Vector2 defaultZoom;
        void onWindowSizeChanged();
};