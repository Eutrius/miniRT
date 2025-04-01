#include "minirt.h"

static void	transform_sphere(t_data *data, t_sphere *sphere, float fov_factor,
				int x, int y);
static void	vec_to_camera_point(t_data *data, t_vec v, float *x, float *y);

void	transform(t_data *data, int x, int y)
{
	t_obj	*obj;
	float	fov_factor;

	obj = &data->scene.objs[data->obj_onhand];
	fov_factor = (1.0f / (data->scene.cam.fov * 0.5f));
	if (obj->type == SPHERE)
		transform_sphere(data, (t_sphere *)obj->self, fov_factor, x, y);
}

static void	transform_sphere(t_data *data, t_sphere *sphere, float fov_factor,
		int x, int y)
{
	float	from_dist;
	float	to_dist;
	float	sphere_x;
	float	sphere_y;

	vec_to_camera_point(data, sphere->center, &sphere_x, &sphere_y);
	from_dist = point_distance(data->from_x, data->from_y, sphere_x, sphere_y);
	to_dist = point_distance(x, y, sphere_x, sphere_y);
	if (from_dist > to_dist)
	{
		sphere->radius = sphere->radius - point_distance(x, y, data->from_x,
				l data->from_y) * fov_factor;
		(void)fov_factor;
	}
	else
		sphere->radius = sphere->radius + point_distance(x, y, data->from_x,
				data->from_y) * fov_factor;
	print_sphere(sphere);
}

static void	vec_to_camera_point(t_data *data, t_vec v, float *x, float *y)
{
	float	fov_factor;
	float	screen_x;
	float	screen_y;

	fov_factor = (1.0f / (data->scene.cam.fov * 0.5f));
	screen_x = fov_factor * data->scene.cam.aspect_ratio * (v.x / v.z);
	screen_y = fov_factor * (v.y / v.z);
	*x = (screen_x + 1.0f) * 0.5f * data->w;
	*y = (1.0f - screen_y) * 0.5f * data->h;
}
