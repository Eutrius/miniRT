/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_cy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:04 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:41:14 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		wheel_cap(t_hit *hit, t_cylinder *cyl, float dot_normal_axis);
static float	calculate_theta(float x, float y);
static void		checkerboard_body(t_hit *hit, t_cylinder *cyl, int color);
static float	calculate_body_u(t_hit *hit, t_cylinder *cyl,
					t_vec point_on_axis);

void	checkerboard_cy(t_hit *hit, t_cylinder *cyl, int color)
{
	float	axis;

	axis = dot(hit->normal, cyl->axis);
	if (fabs(fabs(axis) - 1) < EPSILON)
	{
		if (wheel_cap(hit, cyl, axis) % 2 == 0)
			hit->color = 0;
		else
			hit->color = color;
	}
	else
		checkerboard_body(hit, cyl, color);
}

static int	wheel_cap(t_hit *hit, t_cylinder *cyl, float dot_normal_axis)
{
	t_vec	center;
	t_vec	vec_hit;
	t_vec	u_dir;
	t_vec	v_dir;

	center = vecsum(cyl->center, scalar(cyl->axis, (2 * (dot_normal_axis > 0)
					- 1) * cyl->height / 2.0));
	vec_hit = vecsub(hit->point, center);
	u_dir = get_orthogonal_vector(cyl->axis);
	v_dir = cross(cyl->axis, u_dir);
	return ((calculate_theta(dot(vec_hit, u_dir), dot(vec_hit, v_dir)) + M_PI)
		* (int)cyl->radius);
}

static void	checkerboard_body(t_hit *hit, t_cylinder *cyl, int color)
{
	t_vec	vec_hit;
	t_vec	point_on_axis;
	float	u;
	float	v;

	vec_hit = vecsub(hit->point, cyl->center);
	v = dot(vec_hit, cyl->axis);
	point_on_axis = vecsum(cyl->center, scalar(cyl->axis, v));
	u = calculate_body_u(hit, cyl, point_on_axis);
	hit->color = set_color(u * (int)cyl->radius, v, color);
}

static float	calculate_body_u(t_hit *hit, t_cylinder *cyl,
		t_vec point_on_axis)
{
	t_vec	u_dir;
	t_vec	v_dir;
	t_vec	radial_vec;

	radial_vec = vecsub(hit->point, point_on_axis);
	u_dir = get_orthogonal_vector(cyl->axis);
	v_dir = cross(cyl->axis, u_dir);
	return (calculate_theta(dot(radial_vec, u_dir), dot(radial_vec, v_dir))
		+ M_PI);
}

static float	calculate_theta(float x, float y)
{
	return (atan2(y, x));
}
