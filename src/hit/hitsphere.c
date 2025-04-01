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

static void	calculat_coeff(t_ray ray, t_sphere *sphere, t_quadratic *quad);

char	hitsphere(t_ray ray, t_hit *hit, void *self)
{
	t_sphere	*sphere;
	t_quadratic	quad;
	t_vec		hit_point;

	sphere = ((t_obj *)self)->self;
	calculat_coeff(ray, sphere, &quad);
	if (quad.discriminant > 0)
	{
		if (quad.t1 > quad.t2 && quad.t2 >= EPSILON)
			hit->t = quad.t2;
		else if (quad.t1 >= EPSILON)
			hit->t = quad.t1;
		else
			return (0);
		hit_point = vecsum(ray.start, scalar(ray.dir, hit->t));
		hit->normal = normalize(vecsub(hit_point, sphere->center));
		hit->color = ((t_obj *)self)->color;
		return (1);
	}
	return (0);
}

static void	calculat_coeff(t_ray ray, t_sphere *sphere, t_quadratic *quad)
{
	t_vec	oc;

	oc = vecsub(ray.start, sphere->center);
	quad->a = dot(ray.dir, ray.dir);
	quad->b = 2.0f * dot(ray.dir, oc);
	quad->c = dot(oc, oc) - (sphere->radius * sphere->radius);
	quadratic(quad);
}
