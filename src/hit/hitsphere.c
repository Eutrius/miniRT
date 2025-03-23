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
	t_vec		oc;
	float		a;
	float		b;
	float		c;
	t_vec		hit_point;

	sphere = ((t_obj *)self)->self;
	oc = vecsub(sphere->center, ray.start);
	a = dot(ray.dir, ray.dir);
	b = 2.0f * dot(ray.dir, oc);
	c = dot(oc, oc) - (sphere->radius * sphere->radius);
	if (b * b - 4 * (a * c) >= 0.00001f)
	{
		hit->t = (b - sqrt(b * b - 4 * (a * c))) / (2 * a);
		c = (b + sqrt(b * b - 4 * (a * c))) / (2 * a);
		if (hit->t > c)
			hit->t = c;
		if (hit->t < 0.00001f)
			return (0);
		hit_point = vecsum(ray.start, scalarprod(ray.dir, hit->t));
		hit->normal = normalize(vecsub(hit_point, sphere->center));
		hit->color = ((t_obj *)self)->color;
		return (1);
	}
	return (0);
}
