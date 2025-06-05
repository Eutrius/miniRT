/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitcone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:19 by lmoricon          #+#    #+#             */
/*   Updated: 2025/06/05 12:28:04 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		calculate_coeff(t_ray ray, t_cone *cone, t_quadratic *quad);
static t_vec	calculate_normal(t_vec hit_point, t_cone *cone);

char	hitcone(t_ray ray, t_hit *hit, void *self)
{
	t_cone		*cone;
	t_quadratic	quad;
	t_obj		*obj;

	obj = self;
	cone = obj->self;
	calculate_coeff(ray, cone, &quad);
	if (quad.discriminant >= EPSILON)
	{
		if (quad.t1 >= EPSILON && (quad.t1 < quad.t2 || quad.t2 < EPSILON))
			hit->t = quad.t1;
		else if (quad.t2 >= EPSILON)
			hit->t = quad.t2;
		else
			return (0);
		hit->point = vecsum(ray.start, scalar(ray.dir, hit->t));
		hit->normal = calculate_normal(hit->point, cone);
		if (obj->bump && obj->texture)
			bumperman(obj, obj->texture, hit);
		checkerman(hit, self);
		return (1);
	}
	return (0);
}

static t_vec	calculate_normal(t_vec hit_point, t_cone *cone)
{
	float	m;
	t_vec	axis_point;
	t_vec	perp_dir;
	t_vec	normal;

	m = dot(vecsub(hit_point, cone->center), cone->axis);
	axis_point = vecsum(cone->center, scalar(cone->axis, m));
	perp_dir = vecsub(hit_point, axis_point);
	normal = vecsum(scalar(perp_dir, cosf(cone->angle * (M_PI / 180.0f))),
			scalar(cone->axis, sinf(cone->angle * (M_PI / 180.0f))));
	return (normalize(normal));
}

static void	calculate_coeff(t_ray ray, t_cone *cone, t_quadratic *quad)
{
	t_vec	oc;
	float	axis_dir;
	float	axis_oc;
	float	angle;

	oc = vecsub(ray.start, cone->center);
	axis_dir = dot(cone->axis, ray.dir);
	axis_oc = dot(cone->axis, oc);
	angle = tanf(cone->angle * (M_PI / 180.0f)) * tanf(cone->angle * (M_PI
				/ 180.0f));
	quad->a = dot(ray.dir, ray.dir) - (1 + angle) * axis_dir * axis_dir;
	quad->b = 2.0f * (dot(oc, ray.dir) - (1 + angle) * axis_dir * axis_oc);
	quad->c = dot(oc, oc) - (1 + angle) * axis_oc * axis_oc;
	quadratic(quad);
}
