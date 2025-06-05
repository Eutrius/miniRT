/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvman.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:33:31 by jyriarte          #+#    #+#             */
/*   Updated: 2025/06/04 20:54:15 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv	uv_sphere(t_hit *hit, t_sphere *sphere)
{
	t_uv	uv;
	t_vec	center;

	float theta, phi;
	center = normalize(vecsub(hit->point, sphere->center));
	theta = atan2(center.z, center.x);
	phi = acos(center.y);
	uv.u = (theta + M_PI) / (2.0 * M_PI);
	uv.v = phi / M_PI;
	return (uv);
}

t_uv	uv_plane(t_hit *hit, t_plane *plane)
{
	t_uv	uv;
	t_vec	u_vec;
	t_vec	v_vec;
	t_vec	center;
	float	scale;

	scale = 1.0;
	center = vecsub(hit->point, plane->center);
	u_vec = get_orthogonal_vector(plane->axis);
	v_vec = cross(plane->axis, u_vec);
	uv.u = fmod(dot(center, u_vec) * scale + 1000.0, 1.0);
	uv.v = fmod(dot(center, v_vec) * scale + 1000.0, 1.0);
	if (uv.u < 0)
		uv.u += 1.0;
	if (uv.v < 0)
		uv.v += 1.0;
	return (uv);
}

t_uv	uv_cylinder_body(t_hit *hit, t_cylinder *cylinder)
{
	t_vec	vec_hit;
	t_vec	point_on_axis;
	t_uv	uv;
	float	theta;

	vec_hit = vecsub(hit->point, cylinder->center);
	uv.v = dot(vec_hit, cylinder->axis);
	uv.v = (uv.v + cylinder->height / 2.0) / cylinder->height;
	uv.v = fmax(0.0, fmin(1.0, uv.v));
	point_on_axis = vecsum(cylinder->center, scalar(cylinder->axis, dot(vec_hit,
					cylinder->axis)));
	theta = calculate_body_u(hit, cylinder, point_on_axis);
	uv.u = fmod(theta / (2.0 * M_PI) + 1.0, 1.0);
	if (uv.u < 0)
		uv.u += 1.0;
	return (uv);
}

t_uv	uv_cylinder_cap(t_hit *hit, t_cylinder *cylinder, float axis)
{
	t_vec	center;
	t_uv	uv;
	t_vec	vec_hit;
	t_vec	u;

	center = vecsum(cylinder->center, scalar(cylinder->axis, (2 * (axis > 0)
					- 1) * cylinder->height / 2.0));
	vec_hit = vecsub(hit->point, center);
	u = get_orthogonal_vector(cylinder->axis);
	uv.u = dot(vec_hit, u);
	uv.v = dot(vec_hit, cross(cylinder->axis, u));
	return (uv);
}

t_uv	uv_cone(t_hit *hit, t_cone *cone)
{
	t_vec	apex;
	t_uv	uv;
	float	theta;
	float	dist_from_apex;

	apex = vecsub(hit->point, cone->center);
	theta = calculate_theta(hit, cone, apex);
	uv.u = fmod((theta + M_PI) / (2.0 * M_PI), 1.0);
	if (uv.u < 0)
		uv.u += 1.0;
	dist_from_apex = dot(apex, cone->axis);
	uv.v = fmod(fabs(dist_from_apex), 1.0);
	return (uv);
}
