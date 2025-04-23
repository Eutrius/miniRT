/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_co.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:00 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:42:48 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calculate_theta(t_hit *hit, t_cone *cone, t_vec apex);

void	checkerboard_co(t_hit *hit, t_cone *cone, int color)
{
	t_vec	apex;
	float	u;
	float	v;

	apex = vecsub(hit->point, cone->center);
	v = veclen(apex);
	u = (calculate_theta(hit, cone, apex) + M_PI) / (2.0 * M_PI);
	hit->color = set_color(u * cone->angle, v, color);
}

static float	calculate_theta(t_hit *hit, t_cone *cone, t_vec apex)
{
	float	proj_dist;
	t_vec	point_on_axis;
	t_vec	radial_vector;
	t_vec	ref_u_dir;

	proj_dist = dot(apex, cone->axis);
	point_on_axis = vecsum(cone->center, scalar(cone->axis, proj_dist));
	radial_vector = vecsub(hit->point, point_on_axis);
	ref_u_dir = get_orthogonal_vector(cone->axis);
	return (atan2(dot(radial_vector, cross(cone->axis, ref_u_dir)),
			dot(radial_vector, ref_u_dir)));
}
