/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:42:04 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/29 18:38:35 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int	render_scene(void *arg)
{
	t_data	*data;
	void	*img;

	data = arg;
	img = render(data->scene, data->w, data->h, data->mlx);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
	return (0);
}

void	*render(t_scene scene, int w, int h, void *mlx)
{
	t_img	img;
	int		y;
	int		x;
	t_hit	hit;

	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	y = h;
	while (y >= 0)
	{
		x = w;
		while (x >= 0)
		{
			project_ray(&scene, &hit, x, y);
			if (hit.color != 0)
				lightman(scene, ray_per_pixel(&scene, &scene.cam, x, y), &hit);
			pixel(&img, x, y, hit.color);
			x--;
		}
		y--;
	}
	return (img.img);
}

int	project_ray(t_scene *scene, t_hit *hit, int x, int y)
{
	t_ray	ray;
	t_hit	final_hit;
	int		hit_index;
	int		i;

	i = 0;
	final_hit.color = 0;
	final_hit.t = 0xffffff;
	hit_index = -1;
	ray = ray_per_pixel(scene, &scene->cam, x, y);
	while (i < scene->objc)
	{
		if (scene->objs[i].hit(ray, hit, &scene->objs[i]))
		{
			if (hit->t < final_hit.t)
			{
				final_hit = *hit;
				hit_index = i;
			}
		}
		i++;
	}
	*hit = final_hit;
	return (hit_index);
}
