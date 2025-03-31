
#include "minirt.h"

int	translate(t_data *data, int x, int y)
{
	t_scene	scene;
	t_ray	r;
	float	camw;
	float	camh;
	t_hit	hit;
	t_hit	finalhit;
	int		i;
	float	deltax;
	float	deltay;
	t_vec	pp;
	int		obj_index;
	float	aspect_ratio;

	scene = data->scene;
	aspect_ratio = (float)data->w / data->h;
	camw = tan((scene.cam.fov * (3.14 / 180)) / 2);
	camh = camw / (((float)data->w / (float)data->h));
	deltax = (camw * 2) / data->w;
	deltay = (camh * 2) / data->h;
	pp = vecsum(scene.cam.ori, scene.cam.pos);
	pp.x = pp.x - camw + (x * deltax) + (deltax / 2);
	pp.y = pp.y + camh - (y * deltay) + (deltay / 2);
	r = ray(scene.cam.pos, normalize(vecsub(pp, scene.cam.pos)));
	i = 0;
	finalhit.t = INFINITY;
	while (i < scene.objc)
	{
		if (scene.objs[i].hit(r, &hit, &scene.objs[i]))
		{
			if (hit.t < finalhit.t)
			{
				finalhit = hit;
				obj_index = i;
			}
		}
		i++;
	}
	return (i);
}
