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
	t_vec		cap_hit_point;
	float		temp;
	float		best_t;
	t_vec		best_normal;
	t_vec		top_center;
	float		top_denom;
	t_vec		bot_center;
	float		bot_denom;

	t_vec hit_point, cp, axis_point;
	float m, epsilon;
	float dot_dir_axis, dot_oc_axis;
	t_vec dir_proj, oc_proj;
	t_vec oc, dir;
	float a, b, c, discriminant;
	float t1, t2, cap_t;
	// Small epsilon for floating-point comparisons
	epsilon = 1e-6f;
	// Extract cylinder object from void pointer
	cyl = ((t_obj *)self)->self;
	// Vector from cylinder center to ray origin
	oc = vecsub(ray.start, cyl->center);
	// Project ray direction and origin vector onto cylinder axis
	dot_dir_axis = dot(ray.dir, cyl->axis);
	dot_oc_axis = dot(oc, cyl->axis);
	dir_proj = scalar(cyl->axis, dot_dir_axis);
	oc_proj = scalar(cyl->axis, dot_oc_axis);
	// Calculate perpendicular components
	dir = vecsub(ray.dir, dir_proj);
	oc = vecsub(oc, oc_proj);
	// Quadratic equation coefficients
	a = dot(dir, dir);
	if (a < epsilon)
		return (0);
	b = 2.0f * dot(oc, dir);
	c = dot(oc, oc) - (cyl->radius * cyl->radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < epsilon)
		return (0);
	// Calculate intersection points
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	// Ensure t1 is the smaller intersection
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	// Check both cylinder body and caps
	best_t = INFINITY;
	int hit_type = 0; // 0: no hit, 1: body, 2: top cap, 3: bottom cap
	// Cylinder body intersection
	if (t1 > epsilon)
	{
		hit_point = vecsum(ray.start, scalar(ray.dir, t1));
		cp = vecsub(hit_point, cyl->center);
		m = dot(cp, cyl->axis);
		if (m >= -cyl->height / 2 && m <= cyl->height / 2)
		{
			best_t = t1;
			axis_point = vecsum(cyl->center, scalar(cyl->axis, m));
			best_normal = normalize(vecsub(hit_point, axis_point));
			hit_type = 1;
		}
	}
	if (best_t == INFINITY && t2 > epsilon)
	{
		hit_point = vecsum(ray.start, scalar(ray.dir, t2));
		cp = vecsub(hit_point, cyl->center);
		m = dot(cp, cyl->axis);
		if (m >= -cyl->height / 2 && m <= cyl->height / 2)
		{
			best_t = t2;
			axis_point = vecsum(cyl->center, scalar(cyl->axis, m));
			best_normal = normalize(vecsub(hit_point, axis_point));
			hit_type = 1;
		}
	}
	// Top cap intersection
	top_center = vecsum(cyl->center, scalar(cyl->axis, cyl->height / 2));
	top_denom = dot(ray.dir, cyl->axis);
	if (fabs(top_denom) > epsilon)
	{
		cap_t = dot(vecsub(top_center, ray.start), cyl->axis) / top_denom;
		if (cap_t > epsilon)
		{
			cap_hit_point = vecsum(ray.start, scalar(ray.dir, cap_t));
			if (veclen(vecsub(cap_hit_point, top_center)) <= cyl->radius)
			{
				if (cap_t < best_t)
				{
					best_t = cap_t;
					best_normal = cyl->axis;
					hit_type = 2;
				}
			}
		}
	}
	// Bottom cap intersection
	bot_center = vecsub(cyl->center, scalar(cyl->axis, cyl->height / 2));
	bot_denom = dot(ray.dir, cyl->axis);
	if (fabs(bot_denom) > epsilon)
	{
		cap_t = dot(vecsub(bot_center, ray.start), cyl->axis) / bot_denom;
		if (cap_t > epsilon)
		{
			cap_hit_point = vecsum(ray.start, scalar(ray.dir, cap_t));
			if (veclen(vecsub(cap_hit_point, bot_center)) <= cyl->radius)
			{
				if (cap_t < best_t)
				{
					best_t = cap_t;
					best_normal = scalar(cyl->axis, -1);
					hit_type = 3;
				}
			}
		}
	}
	// Return hit information
	if (hit_type > 0)
	{
		hit->t = best_t;
		hit->normal = best_normal;
		hit->color = ((t_obj *)self)->color;
		return (1);
	}
	return (0);
}
