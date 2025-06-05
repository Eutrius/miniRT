/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:15:05 by jyriarte          #+#    #+#             */
/*   Updated: 2025/05/26 22:16:14 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	process_bump_normal(t_vec n, float bu, float bv)
{
	t_vec	v;
	t_vec	pu;
	t_vec	pv;

	v = n;
	pu = cross(n, get_orthogonal_vector(n));
	pv = cross(n, pu);
	v = vecsum(v, scalar(pu, bv));
	v = vecsum(v, scalar(pv, bu));
	v = normalize(v);
	return (v);
}

void	bump_normal(t_obj *obj, t_img *img, t_hit *hit)
{
	int		x[2];
	int		y[2];
	t_uv	map;

	int b0, b1, b2;
	float uv[2], bu, bv;
	if (obj->type == SPHERE)
		map = uv_sphere(hit, (t_sphere *)obj->self);
	else if (obj->type == PLANE)
		map = uv_plane(hit, (t_plane *)obj->self);
	else if (obj->type == CYLINDER)
		map = uv_cylinder_body(hit, (t_cylinder *)obj->self);
	else if (obj->type == CONE)
		map = uv_cone(hit, (t_cone *)obj->self);
	else
		return ;
	uv[0] = map.u;
	uv[1] = map.v;
	x[0] = (int)(uv[0] * img->width) % img->width;
	y[0] = (int)((1.0f - uv[1]) * img->height) % img->height;
	x[1] = (x[0] + 1) % img->width;
	y[1] = (y[0] + 1) % img->height;
	b0 = *((unsigned int *)(img->addr + (y[0] * img->line_length + x[0]
					* (img->bits_per_pixel / 8)))) & 0xff;
	b1 = *((unsigned int *)(img->addr + (y[0] * img->line_length + x[1]
					* (img->bits_per_pixel / 8)))) & 0xff;
	b2 = *((unsigned int *)(img->addr + (y[1] * img->line_length + x[0]
					* (img->bits_per_pixel / 8)))) & 0xff;
	bu = -((float)(b0 - b1)) / 10.0f;
	bv = -((float)(b0 - b2)) / 10.0f;
	hit->normal = process_bump_normal(hit->normal, bu, bv);
}

int	textureman(char **args, t_obj *obj, t_data *data)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	img->img = mlx_xpm_file_to_image(data->mlx, args[0], &img->width,
			&img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	obj->texture = img;
	return (1);
}
