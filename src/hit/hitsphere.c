#include "minirt.h"

/**
 * hitsphere - Checks if a ray intersects with a sphere.
 * @ray: The ray to check for intersection.
 * @hit: Pointer to the hit structure to store intersection details.
 * @self: Pointer to the sphere object.
 *
 * This function calculates if a given ray intersects with a sphere.
 * If an intersection is found, it updates the hit structure with the
 * intersection point, normal at the intersection, and color of the sphere.
 *
 * Returns: 1 if an intersection is found, 0 otherwise.
 */

char	hitsphere(t_ray ray, t_hit *hit, void *self)
{
	t_sphere	*sphere;
	t_quadratic	quad;
	t_vec		oc;
	t_vec		hit_point;

	sphere = ((t_obj *)self)->self;
	oc = vecsub(sphere->center, ray.start);
	quad.a = dot(ray.dir, ray.dir);
	quad.b = 2.0f * dot(ray.dir, oc);
	quad.c = dot(oc, oc) - (sphere->radius * sphere->radius);
	solve_quadratic(&quad);
	if (quad.discriminant >= EPSILON)
	{
		if (quad.t1 > quad.t2)
			hit->t = quad.t2;
		else
			hit->t = quad.t1;
		if (hit->t < EPSILON)
			return (0);
		hit_point = vecsum(ray.start, scalar(ray.dir, hit->t));
		hit->normal = normalize(vecsub(hit_point, sphere->center));
		hit->color = ((t_obj *)self)->color;
		return (1);
	}
	return (0);
}

/*char	hitcylinder(t_ray ray, t_hit *hit, void *self)*/
/*{*/
/*	t_cylinder	*cyl;*/
/*	t_vec		base;*/
/*	t_vec		oc;*/
/*	float		ray_par;*/
/*	t_vec		ray_per;*/
/*	float		oc_par;*/
/*	t_vec		oc_per;*/
/*	t_quadratic	quad;*/
/*	t_vec		hit_point;*/
/*	t_vec		center;*/
/*	float		par;*/
/**/
/*	cyl = ((t_obj *)self)->self;*/
/*	cyl->axis = normalize(cyl->axis);*/
/*	base = vecsub(cyl->center, scalar(cyl->axis, cyl->height * 0.5f));*/
/*	oc = vecsub(base, ray.start);*/
/*	ray_par = dot(ray.dir, cyl->axis);*/
/*	oc_par = dot(oc, cyl->axis);*/
/*	ray_per = vecsub(ray.dir, scalar(cyl->axis, ray_par));*/
/*	oc_per = vecsub(oc, scalar(cyl->axis, oc_par));*/
/*	quad.a = dot(ray_per, ray_per);*/
/*	quad.b = 2.0f * dot(ray_per, oc_per);*/
/*	quad.c = dot(oc_per, oc_per) - cyl->radius * cyl->radius;*/
/*	solve_quadratic(&quad);*/
/*	if (quad.discriminant <= EPSILON)*/
/*		return (0);*/
/*	if (quad.t1 < EPSILON && quad.t2 < EPSILON)*/
/*		return (0);*/
/*	if (quad.t1 > quad.t2)*/
/*		hit->t = quad.t2;*/
/*	else*/
/*		hit->t = quad.t1;*/
/*	hit_point = vecsum(ray.start, scalar(ray.dir, hit->t));*/
/*	center = vecsub(hit_point, cyl->center);*/
/*	par = dot(center, cyl->axis);*/
/*	hit->normal = normalize(vecsub(center, scalar(cyl->axis, par)));*/
/*	if (dot(ray.dir, hit->normal) > 0)*/
/*		hit->normal = scalar(hit->normal, -1);*/
/*	hit->color = ((t_obj *)self)->color;*/
/*	return (1);*/
/*}*/
