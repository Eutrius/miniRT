/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:47 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/27 13:24:08 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_hit_closer_than_light(t_ray lightray, t_hit hit, t_light light)
{
	float	dist_to_hit;
	float	dist_to_light;

	dist_to_light = veclen(vecsub(light.pos, lightray.start));
	dist_to_hit = hit.t;
	return (dist_to_hit > 0.001f && dist_to_hit < dist_to_light);
}

void	ambient(t_hit *h, t_amb ambient)
{
	h->color = coloradd(h->color, colormult(ambient.color, ambient.ratio));
}

int	diffuse(t_hit *h, t_light light, t_ray lightray)
{
	float	intensity;
	float	distance;
	float	attenuation;

	distance = veclen(vecsub(light.pos, lightray.start));
	attenuation = 1.0f / (1.0f + 0.1f * distance + 0.01f * distance * distance);
	intensity = dot(h->normal, lightray.dir);
	if (intensity < 0)
		return (1);
	h->color = coloradd(h->color, colormult(light.color, light.ratio * intensity
				* attenuation));
	return (1);
}

void	specular(t_hit *h, t_light light, t_ray lightray, t_ray og)
{
	t_vec	reflected_ray;
	t_vec	view_dir;
	float	dot_product;
	float	intensity;
	float	distance;
	float	attenuation;

	distance = veclen(vecsub(light.pos, lightray.start));
	attenuation = 1.0f / (1.0f + 0.1f * distance + 0.01f * distance * distance);
	reflected_ray = vecsub(scalar(h->normal, 2 * dot(lightray.dir, h->normal)),
			lightray.dir);
	view_dir = normalize(negate(og.dir));
	dot_product = dot(reflected_ray, view_dir);
	if (dot_product > 0)
	{
		intensity = powf(dot_product, SHINYNESS);
		h->color = coloradd(h->color, colormult(light.color, light.ratio
					* intensity * attenuation));
	}
}

/*
sorry, norminette, i[1] is the light index, i[0] is the object index,
	i[2] is the
collision flag >:
*/
void	lightman(t_scene scene, t_ray r, t_hit *hit)
{
	t_hit	ph;
	int		i[3];
	t_ray	lightray;
	t_light	curr_light;

	i[1] = -1;
	lightray.start = vecsum(r.start, scalar(r.dir, hit->t));
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
			{
				i[2] = 1;
			}
		}
		if (i[2] == 0 && diffuse(hit, curr_light, lightray))
			specular(hit, curr_light, lightray, r);
	}
	ambient(hit, scene.amb);
}
