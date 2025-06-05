/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpnan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:15:05 by jyriarte          #+#    #+#             */
/*   Updated: 2025/05/26 22:16:14 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	process_bump_normal(t_vec normal, t_uv buv)
{
	t_vec	v;
	t_vec	pv;
	t_vec	pu;

	v = normal;
	pu = cross(normal, get_orthogonal_vector(normal));
	pv = cross(normal, pu);
	v = vecsum(v, scalar(pu, buv.v));
	v = vecsum(v, scalar(pv, buv.u));
	v = normalize(v);
	return (v);
}

t_uv	calculate_offset(t_img *img, t_uv uv)
{
	int		x[2];
	int		y[2];
	int		offset[3];
	t_uv	buv;

	x[0] = (int)(uv.u * img->width) % img->width;
	y[0] = (int)((1.0f - uv.v) * img->height) % img->height;
	x[1] = (x[0] + 1) % img->width;
	y[1] = (y[0] + 1) % img->height;
	offset[0] = *((unsigned int *)(img->addr + (y[0] * img->line_length + x[0]
					* (img->bits_per_pixel / 8)))) & 0xff;
	offset[1] = *((unsigned int *)(img->addr + (y[0] * img->line_length + x[1]
					* (img->bits_per_pixel / 8)))) & 0xff;
	offset[2] = *((unsigned int *)(img->addr + (y[1] * img->line_length + x[0]
					* (img->bits_per_pixel / 8)))) & 0xff;
	buv.u = -((float)(offset[0] - offset[1])) / 10.0f;
	buv.v = -((float)(offset[0] - offset[2])) / 10.0f;
	return (buv);
}

void	bumperman(t_obj *obj, t_img *img, t_hit *hit)
{
	t_uv	uv;
	t_uv	buv;

	if (obj->type == SPHERE)
		uv = uv_sphere(hit, (t_sphere *)obj->self);
	else if (obj->type == PLANE)
		uv = uv_plane(hit, (t_plane *)obj->self);
	else if (obj->type == CYLINDER)
		uv = uv_cylinder_body(hit, (t_cylinder *)obj->self);
	else if (obj->type == CONE)
		uv = uv_cone(hit, (t_cone *)obj->self);
	else
		return ;
	buv = calculate_offset(img, uv);
	hit->normal = process_bump_normal(hit->normal, buv);
}

int	textureman(char **args, t_obj *obj, t_data *data)
{
	t_img	*img;

	if (!args[0])
		return (1);
	if (args[1])
		return (0);
	img = ft_calloc(1, sizeof(t_img));
	img->img = mlx_xpm_file_to_image(data->mlx, args[0], &img->width,
			&img->height);
	if (!img->img)
	{
		free(img);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	obj->texture = img;
	return (1);
}
