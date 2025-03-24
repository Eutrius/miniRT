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

char	hitcylinder(t_ray ray, t_hit *hit, void *self)
{
	t_cylinder	*cyl;
	t_vec		hit_point;
	float		m;
	float		dot_dir_axis;
	float		dot_oc_axis;
	t_vec		dir_proj;
	t_vec		oc_proj;
	float		temp;
	t_vec		cp;
	t_vec		axis_point;

	t_vec oc, dir;
	float a, b, c, discriminant;
	float t1, t2, t_min;
	cyl = ((t_obj *)self)->self;
	// Vector from cylinder center to ray origin
	oc = vecsub(ray.start, cyl->center);
	// Calculate quadratic equation coefficients
	dot_dir_axis = dot(ray.dir, cyl->axis);
	dot_oc_axis = dot(oc, cyl->axis);
	// These are the projections of the ray direction and oc onto the cylinder axis
	dir_proj = scalar(cyl->axis, dot_dir_axis);
	oc_proj = scalar(cyl->axis, dot_oc_axis);
	// Components perpendicular to the axis
	dir = vecsub(ray.dir, dir_proj);
	oc = vecsub(oc, oc_proj);
	// Standard quadratic equation coefficients
	a = dot(dir, dir);
	// Check if ray is parallel to cylinder axis
	if (a < 0.00001f)
		return (0);
	b = 2.0f * dot(oc, dir);
	c = dot(oc, oc) - (cyl->radius * cyl->radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0.00001f)
		return (0);
	// Calculate intersection points
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	// Find closest valid intersection
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	// Check if both intersections are behind the ray
	if (t2 < 0.00001f)
		return (0);
	// Use t1 if it's valid, otherwise use t2
	t_min = (t1 > 0.00001f) ? t1 : t2;
	// Check if intersection is within cylinder height
	hit_point = vecsum(ray.start, scalar(ray.dir, t_min));
	cp = vecsub(hit_point, cyl->center);
	m = dot(cp, cyl->axis);
	if (m < -cyl->height / 2 || m > cyl->height / 2)
	{
		// Try the other intersection point
		if (t1 > 0.00001f && t1 < t2)
			t_min = t2;
		else
			return (0);
		hit_point = vecsum(ray.start, scalar(ray.dir, t_min));
		cp = vecsub(hit_point, cyl->center);
		m = dot(cp, cyl->axis);
		if (m < -cyl->height / 2 || m > cyl->height / 2)
			return (0);
	}
	// Valid intersection found
	hit->t = t_min;
	// Calculate normal at hit point
	axis_point = vecsum(cyl->center, scalar(cyl->axis, m));
	hit->normal = normalize(vecsub(hit_point, axis_point));
	hit->color = ((t_obj *)self)->color;
	return (1);
}
