#ifndef EXCLUDE_SCRIPTING

#include "scripting/cameras-module.h"
#include "cameras/cameras.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct CameraLibrary
    {
        Camera perspective(
            const Point3D& eye,
            const Point3D& look_at,
            const Vector3D& up,
            double distance,
            double aspect_ratio) const
        {
            return cameras::perspective(eye, look_at, up, distance, aspect_ratio);
        }

        Camera perspective_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(Point3D, eye);
            ARGUMENT(Point3D, look_at);
            OPTIONAL_ARGUMENT(Vector3D, up, Vector3D(0, 1, 0));
            OPTIONAL_ARGUMENT(double, distance, 1);
            OPTIONAL_ARGUMENT(double, aspect_ratio, 1);
            END_ARGUMENTS();

            return cameras::perspective(eye, look_at, up, distance, aspect_ratio);
        }

		Camera depth_of_field(const Point3D& eye, const Point3D& look_at, const Vector3D& up, double distance, double aspect_ratio, double eye_size, Sampler sampler) const {
			return cameras::depth_of_field_perspective(eye, look_at, up, distance, aspect_ratio, eye_size, sampler);
		}

		Camera depth_of_field_by_map(const std::map<std::string, Boxed_Value>& argument_map) const {

			START_ARGUMENTS(argument_map);
			ARGUMENT(Point3D, eye);
			ARGUMENT(Point3D, look_at);
			OPTIONAL_ARGUMENT(Vector3D, up, Vector3D(0, 1, 0));
			OPTIONAL_ARGUMENT(double,distance,1);
			OPTIONAL_ARGUMENT(double, aspect_ratio, 1);
			OPTIONAL_ARGUMENT(double, eye_size, 2);
			OPTIONAL_ARGUMENT(Sampler, eye_sampler, samplers::random(2));
			END_ARGUMENTS();
		}

		Camera fisheye(const Point3D& eye, const Point3D& lookat, const Vector3D& up,  math::Angle horizontal,  math::Angle vertical) const{
			return cameras::fisheye(eye, lookat, up, horizontal, vertical);
		}
		 Camera fisheye_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(Point3D, eye);
            ARGUMENT(Point3D, look_at);
            OPTIONAL_ARGUMENT(Vector3D, up, Vector3D(0, 1, 0));
            OPTIONAL_ARGUMENT(math::Angle, horizontal_angle,Angle::degrees(360));
            OPTIONAL_ARGUMENT(math::Angle, vertical_angle,Angle::degrees(360));
            END_ARGUMENTS();

            return cameras::fisheye(eye, look_at, up, horizontal_angle, vertical_angle);
        }

    };
}

ModulePtr raytracer::scripting::_private_::create_cameras_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Camera>(*module, "Camera");

    auto camera_library = std::make_shared<CameraLibrary>();
    module->add_global_const(chaiscript::const_var(camera_library), "Cameras");

#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&CameraLibrary::INTERNAL), #EXTERNAL); module->add(fun(&CameraLibrary::INTERNAL ## _by_map), #EXTERNAL)
#   define BIND(NAME)                      BIND_AS(NAME, NAME)
    BIND(perspective);
	BIND(fisheye);
	BIND(depth_of_field);
#   undef BIND
#   undef BIND_AS

    return module;
}

#endif
