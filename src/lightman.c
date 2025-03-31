#include "minirt.h"


static int	is_hit_closer_than_light(t_ray ray, t_hit hit, t_light light)
{
	t_vec	hit_point;
	t_vec	to_hit;
	t_vec	to_light;

	hit_point = vecsum(ray.start, scalar(ray.dir, hit.t));
	to_hit = vecsub(hit_point, ray.start);
	to_light = vecsub(light.pos, ray.start);
	return (dot(to_hit, to_hit)) < (dot(to_light, to_light));
}



void	lightman(t_scene scene, t_ray r, t_hit *hit)
{
	t_hit	ph;
	int		i;
	int		l;
	float	intensity;
	t_ray	lightray;
	t_light	curr_light;

	i = -1;
	l = -1;
	lightray.start = vecsum(r.start, scalar(r.dir, hit->t - 0.0001f));
	while (++l < scene.lightc)
	{
		curr_light = scene.light[l];
		lightray.dir = normalize(vecsub(curr_light.pos, lightray.start));
		while (++i < scene.objc)
		{
			if (scene.objs[i].hit(lightray, &ph, &scene.objs[i]))
				if (is_hit_closer_than_light(lightray, ph, curr_light))
					continue ;
			intensity = dot(hit->normal, lightray.dir);
			if (intensity < 0)
				return ;
			hit->color = coloradd(hit->color, colormult(curr_light.color,
			curr_light.ratio * intensity));
		}
		l++;
	}
}
