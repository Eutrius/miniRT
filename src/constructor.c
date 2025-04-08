#include "minirt.h"

t_vec	vector(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_ray	ray(t_vec start, t_vec dir)
{
	t_ray	ret;

	ret.dir = dir;
	ret.start = start;
	return (ret);
}

t_ray	ray_per_pixel(t_scene *scene, t_cam *camera, int x, int y)
{
	t_ray	ret;
	float	deltay;
	float	deltax;
	t_vec	pixel_pos;

	deltax = (2.0f * x / scene->data->w - 1.0f) * camera->half_width;
	deltay = (1.0f - 2.0f * y / scene->data->h) * camera->half_height;
	pixel_pos = vecsum(vecsum(camera->pos, camera->forward),
			vecsum(scalar(camera->right, deltax), scalar(camera->up, deltay)));
	ret = ray(camera->pos, normalize(vecsub(pixel_pos, camera->pos)));
	return (ret);
}
