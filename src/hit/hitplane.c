#include "minirt.h"

/**
 * hitplane - Checks if a ray intersects with a plane.
 * @ray: The ray to check for intersection.
 * @hit: Pointer to the hit structure to store intersection details.
 * @self: Pointer to the plane object.
 *
 * This function calculates if a given ray intersects with a plane.
 * If an intersection is found, it updates the hit structure with the
 * intersection point, normal at the intersection, and color of the plane.
 *
 * Returns: 1 if an intersection is found, 0 otherwise.
 */

char	hitplane(t_ray ray, t_hit *hit, void *self)
{
	t_plane	*plane;
	float	denom;

	plane = ((t_obj *)self)->self;
	denom = dot(plane->axis, ray.dir);
	if (fabs(denom) >= EPSILON)
	{
		hit->t = dot(vecsub(plane->center, ray.start), plane->axis) / denom;
		if (hit->t < EPSILON)
			return (0);
		if (denom < 0)
			hit->normal = plane->axis;
		else
			hit->normal = scalar(plane->axis, -1);
		hit->color = ((t_obj *)self)->color;
		if (hit->t >= EPSILON)
			return (1);
	}
	return (0);
}
