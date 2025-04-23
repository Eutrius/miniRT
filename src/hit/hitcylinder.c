/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitcylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:21 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:42:34 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * hitcylinder - Checks if a ray intersects with a cylinder.
 * @ray: The ray to check for intersection.
 * @hit: Pointer to the hit structure to store intersection details.
 * @self: Pointer to the cylinder object.
 *
 * This function calculates if a given ray intersects with a cylinder.
 * If an intersection is found, it updates the hit structure with the
 * intersection point, normal at the intersection, and color of the cylinder.
 *
 * Returns: 1 if an intersection is found, 0 otherwise.
 */

static int	hit_cap(t_ray ray, t_hit *hit, t_cylinder *cyl, t_vec (*f)(t_vec,
					t_vec));
static void	calculat_coeff(t_ray ray, t_cylinder *cyl, t_quadratic *quad);
static int	hit_body(t_ray ray, t_cylinder *cyl, t_hit *hit, float t);

char	hitcylinder(t_ray ray, t_hit *hit, void *self)
{
	t_cylinder	*cyl;
	t_quadratic	quad;

	cyl = ((t_obj *)self)->self;
	calculat_coeff(ray, cyl, &quad);
	if (quad.discriminant < 0)
		return (0);
	hit->t = INFINITY;
	if (hit_body(ray, cyl, hit, quad.t1) | hit_body(ray, cyl, hit,
			quad.t2) | hit_cap(ray, hit, cyl, vecsum) | hit_cap(ray, hit, cyl,
			vecsub))
	{
		checkerboard_cy(hit, cyl, ((t_obj *)self)->color);
		return (1);
	}
	return (0);
}

static void	calculat_coeff(t_ray ray, t_cylinder *cyl, t_quadratic *quad)
{
	t_vec	oc;
	t_vec	dir_proj;
	t_vec	oc_proj;
	t_vec	dir;

	oc = vecsub(ray.start, cyl->center);
	dir_proj = scalar(cyl->axis, dot(ray.dir, cyl->axis));
	oc_proj = scalar(cyl->axis, dot(oc, cyl->axis));
	dir = vecsub(ray.dir, dir_proj);
	oc = vecsub(oc, oc_proj);
	quad->a = dot(dir, dir);
	quad->b = 2.0f * dot(oc, dir);
	quad->c = dot(oc, oc) - (cyl->radius * cyl->radius);
	quadratic(quad);
}

static int	hit_body(t_ray ray, t_cylinder *cyl, t_hit *hit, float t)
{
	t_vec	hit_point;
	t_vec	axis_point;
	float	center_proj;
	t_vec	center_point;

	if (t >= EPSILON)
	{
		hit_point = vecsum(ray.start, scalar(ray.dir, t));
		center_point = vecsub(hit_point, cyl->center);
		center_proj = dot(center_point, cyl->axis);
		if (center_proj >= -cyl->height / 2 && center_proj <= cyl->height / 2)
		{
			if (t < hit->t)
			{
				hit->t = t;
				hit->point = hit_point;
				axis_point = vecsum(cyl->center, scalar(cyl->axis,
							center_proj));
				hit->normal = normalize(vecsub(hit_point, axis_point));
				bump(hit);
				return (1);
			}
		}
	}
	return (0);
}

static int	hit_cap(t_ray ray, t_hit *hit, t_cylinder *cyl, t_vec (*f)(t_vec,
			t_vec))
{
	t_vec	hit_point;
	t_vec	center;
	float	denom;
	float	t;

	center = f(cyl->center, scalar(cyl->axis, cyl->height / 2));
	denom = dot(ray.dir, cyl->axis);
	if (fabs(denom) < EPSILON)
		return (0);
	t = dot(vecsub(center, ray.start), cyl->axis) / denom;
	if (t >= EPSILON)
	{
		hit_point = vecsum(ray.start, scalar(ray.dir, t));
		if (veclen(vecsub(hit_point, center)) <= cyl->radius)
		{
			if (t < hit->t)
			{
				hit->point = hit_point;
				hit->t = t;
				hit->normal = scalar(cyl->axis, 2 * (f == vecsub) - 1);
				return (1);
			}
		}
	}
	return (0);
}
