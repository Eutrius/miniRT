/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:33:05 by jyriarte          #+#    #+#             */
/*   Updated: 2025/06/04 20:51:46 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	calculate_theta(t_hit *hit, t_cone *cone, t_vec apex)
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

float	calculate_body_u(t_hit *hit, t_cylinder *cyl, t_vec point_on_axis)
{
	t_vec	u_dir;
	t_vec	v_dir;
	t_vec	radial_vec;

	radial_vec = vecsub(hit->point, point_on_axis);
	u_dir = get_orthogonal_vector(cyl->axis);
	v_dir = cross(cyl->axis, u_dir);
	return (atan2(dot(radial_vec, u_dir), dot(radial_vec, v_dir)) + M_PI);
}
