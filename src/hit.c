#include "../include/minirt.h"
#include <math.h>


/*
	*    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
	*/
char	hitsphere(t_ray ray, t_hit *hit, void *self)
{
	t_sphere	*sphere;
	t_vec 		oc;
	float		a;
	float		h;
	float		c;

	sphere = ((t_obj *)self)->self;
	oc = vecsub(sphere->center, ray.start);
	a = dot(ray.dir, ray.dir);
    h = dot(ray.dir, oc);
	c = dot(oc, oc) - (sphere->radius * sphere->radius);
	/*printf("a=%f,h=%f , c=%f\nDISCR=%f\n", a, h, c, h * h - (a * c));*/
	if (h * h - (a * c) >= 0)
	{
		/*printf("a=%f,h=%f , c=%f\n", a, h, c);*/
		hit->t = (h - sqrt(h * h - (a * c))/ a);
		if (hit->t < 0)
			return (0);
		hit->color = ((t_obj *)self)->color;
		return (1);
	}
	return (0);
}
