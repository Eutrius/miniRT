/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerman.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:11 by lmoricon          #+#    #+#             */
/*   Updated: 2025/06/05 12:34:55 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	checkerman(t_hit *hit, t_obj *obj)
{
	if (!obj->checker)
		hit->color = obj->color;
	else
	{
		if (obj->type == PLANE)
			checkerboard_pl(hit, obj->self, obj->color);
		else if (obj->type == SPHERE)
			checkerboard_sp(hit, obj->self, obj->color);
		else if (obj->type == CYLINDER)
			checkerboard_cy(hit, obj->self, obj->color);
		else if (obj->type == CONE)
			checkerboard_co(hit, obj->self, obj->color);
	}
}

void	checkerboard_pl(t_hit *hit, t_plane *plane, int color)
{
	t_vec	u_vec;
	t_vec	v_vec;
	t_vec	center;
	t_uv	uv;

	center = vecsub(hit->point, plane->center);
	u_vec = get_orthogonal_vector(plane->axis);
	v_vec = cross(plane->axis, u_vec);
	uv.u = dot(center, u_vec);
	uv.v = dot(center, v_vec);
	hit->color = set_color(uv.u, uv.v, color);
}

void	checkerboard_sp(t_hit *hit, t_sphere *sphere, int color)
{
	t_uv	uv;
	float	scale;

	scale = 3 * sphere->radius;
	uv = uv_sphere(hit, sphere);
	hit->color = set_color(uv.u * scale, uv.v * scale, color);
}

void	checkerboard_cy(t_hit *hit, t_cylinder *cyl, int color)
{
	float	axis;
	t_uv	uv;
	int		theta;

	axis = dot(hit->normal, cyl->axis);
	if (fabs(fabs(axis) - 1) < EPSILON)
	{
		uv = uv_cylinder_cap(hit, cyl, axis);
		theta = (atan2(uv.v, uv.u) + M_PI) * (int)cyl->radius;
		if (theta % 2 == 0)
			hit->color = 0;
		else
			hit->color = color;
	}
	else
	{
		uv = uv_cylinder_body(hit, cyl);
		hit->color = set_color(uv.u * cyl->radius, uv.v * cyl->height, color);
	}
}

void	checkerboard_co(t_hit *hit, t_cone *cone, int color)
{
	t_vec	apex;
	t_uv	uv;

	apex = vecsub(hit->point, cone->center);
	uv.u = (calculate_theta(hit, cone, apex) + M_PI) / (2.0 * M_PI);
	uv.v = veclen(apex);
	hit->color = set_color(uv.u * cone->angle, uv.v, color);
}
