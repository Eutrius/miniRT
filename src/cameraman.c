#include "minirt.h"

void	set_camera_axis(t_scene *scene)
{
	t_vec	world_up;

	if (fabs(scene->cam.forward.y) > 0.99f)
		world_up = vector(0, 0, 1);
	else
		world_up = vector(0, 1, 0);
	scene->cam.right = normalize(cross(world_up, scene->cam.forward));
	scene->cam.up = cross(scene->cam.forward, scene->cam.right);
}

void	set_viewport(t_scene *scene, int w, int h)
{
	scene->cam.aspect_ratio = (float)w / h;
	scene->cam.half_height = tanf((scene->cam.fov * M_PI / 180.0f) * 0.5f);
	scene->cam.half_width = scene->cam.aspect_ratio * scene->cam.half_height;
}
