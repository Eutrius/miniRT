/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:47 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 19:28:23 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_hit_closer_than_light(t_ray ray, t_hit hit, t_light light)
{
	t_vec	hit_point;
	t_vec	to_hit;
	t_vec	to_light;

	hit_point = vecsum(ray.start, scalar(ray.dir, hit.t));
	to_hit = vecsub(hit_point, ray.start);
	to_light = vecsub(light.pos, ray.start);
	return ((dot(to_hit, to_hit)) < (dot(to_light, to_light)));
}

void	ambient(t_hit *h, t_amb ambient)
{
	h->color = coloradd(h->color, colormult(ambient.color, ambient.ratio));
}

int	diffuse(t_hit *h, t_light light, t_ray lightray)
{
	float	intensity;

	intensity = dot(h->normal, lightray.dir);
	if (intensity < 0)
		return (1);
	h->color = coloradd(h->color, colormult(light.color,
				light.ratio * intensity));
	return (1);
}

void	specular(t_hit *h, t_light light, t_ray lightray, float shininess)
{
	t_vec	reflected_ray;
	t_vec	view_dir;
	float	dot_product;
	float	intensity;

	reflected_ray = vecsub(scalar(h->normal, 2
				* dot(lightray.dir, h->normal)), lightray.dir);
	view_dir = normalize(vecsub(h->point, lightray.start));
	dot_product = dot(reflected_ray, view_dir);
	if (dot_product > 0)
	{
		intensity = powf(dot_product, shininess);
		h->color = coloradd(h->color, colormult(light.color,
					light.ratio * intensity));
	}
}

/*
sorry, norminette, i[1] is the light index, i[0] is the object index, i[2] is the
collision flag >:
*/
void	lightman(t_scene scene, t_ray r, t_hit *hit)
{
	t_hit	ph;
	int		i[3];
	t_ray	lightray;
	t_light	curr_light;

	i[1] = -1;
	lightray.start = vecsum(r.start, scalar(r.dir, hit->t - 0.0001f));
	while (++i[1] < scene.lightc)
	{
		i[0] = -1;
		i[2] = 0;
		curr_light = scene.light[i[1]];
		lightray.dir = normalize(vecsub(curr_light.pos, lightray.start));
		while (++i[0] < scene.objc && i[2] == 0)
		{
			if ((scene.objs[i[0]].hit(lightray, &ph, &scene.objs[i[0]]))
				&& is_hit_closer_than_light(lightray, ph, curr_light))
				i[2] = 1;
		}
		if (!i[2] && diffuse(hit, curr_light, lightray))
			specular(hit, curr_light, lightray, SHINYNESS);
	}
	ambient(hit, scene.amb);
}
