#include "../include/minirt.h"
#include <math.h>

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
char hitsphere(t_ray ray, t_hit *hit, void *self)
{
    t_sphere *sphere;
    t_vec oc;
    float a;
    float h;
    float c;

    sphere = ((t_obj *)self)->self;
    oc = vecsub(sphere->center, ray.start);
    a = dot(ray.dir, ray.dir);
    h = dot(ray.dir, oc);
    c = dot(oc, oc) - (sphere->radius * sphere->radius);
    if (h * h - (a * c) >= 0.00001f)
    {
        hit->t = (h - sqrt(h * h - (a * c))) / a;
        c = (h + sqrt(h * h - (a * c))) / a;
        if (hit->t > c)
            hit->t = c;
        if (hit->t < 0.00001f)
            return (0);
        t_vec hit_point = vecsum(ray.start, scalarprod(ray.dir, hit->t));
        hit->normal = normalize(vecsub(hit_point, sphere->center));
        hit->color = ((t_obj *)self)->color;
        return (1);
    }
    return (0);
}

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
char hitplane(t_ray ray, t_hit *hit, void *self)
{
    t_plane *plane;
    float denom;

    plane = ((t_obj *)self)->self;
    denom = dot(plane->normal, ray.dir);
    if (fabs(denom) > 0.00001f)
    {
        hit->t = dot(vecsub(plane->coord, ray.start), plane->normal) / denom;
        if (hit->t < 0.00001f)
            return (0);
        if (denom < 0)
            hit->normal = plane->normal;
        else 
            hit->normal = scalarprod(plane->normal, -1);
        hit->color = ((t_obj *)self)->color;
        if (hit->t >= 0.00001f)
            return 1;
    }
    return 0;
}

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
char hitcylinder(t_ray ray, t_hit *hit, void *self)
{
    t_cylinder *cylinder;
    t_vec oc;
    float a, b, c;
    float discriminant;
    float t1, t2;
    float m1, m2;
    t_vec hit_point;

    cylinder = ((t_obj *)self)->self;
    float half_height = cylinder->maxm / 2.0f;
    float dv = dot(ray.dir, cylinder->axis);
    float xv = dot(oc, cylinder->axis);
    oc = vecsub(ray.start, cylinder->center);
    a = dot(ray.dir, ray.dir) - dv * dv;
    b = 2 * (dot(ray.dir, oc) - dv * xv);
    c = dot(oc, oc) - xv * xv - cylinder->radius * cylinder->radius;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0.0001f)
        return 0;
    discriminant = sqrt(discriminant);
    t1 = (-b - discriminant) / (2 * a);
    t2 = (-b + discriminant) / (2 * a);
    m1 = dv * t1 + xv;
    m2 = dv * t2 + xv;
    if (m1 >= -half_height && m1 <= half_height)
        hit->t = t1;
    else if (m2 >= -half_height && m2 <= half_height)
        hit->t = t2;
    else
        return 0;
    if (hit->t < 0.00001f)
        return 0;
    hit_point = vecsum(ray.start, scalarprod(ray.dir, hit->t));
    t_vec m_vector = scalarprod(cylinder->axis, dv * hit->t + xv);
    hit->normal = normalize(vecsub(vecsub(hit_point, cylinder->center), m_vector));
    hit->color = ((t_obj *)self)->color;
    return 1;
}
