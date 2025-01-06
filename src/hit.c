#include "../include/minirt.h"
#include <math.h>


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
	if (h * h - (a * c) >= 0)
	{
		hit->t = (h - sqrt(h * h - (a * c))/ a);
		if (hit->t < 0)
			return (0);
		hit->color = ((t_obj *)self)->color;
		return (1);
	}
	return (0);
}

char	hitplane(t_ray ray, t_hit *hit, void *self)
{
	t_plane	*plane;
	float denom;

	plane = ((t_obj *)self)->self;
	denom = dot(plane->normal, ray.dir);
	if (fabs(denom) > 0.000001f)
	{
    	hit->t = dot(vecsub(plane->coord, ray.start), plane->normal) / denom;
    if (hit->t >= 0)
			return 1;
	}
	return 0;
}
/**/
/**/
/*char	hitcone(t_ray ray, t_hit *hit, void *self)*/
/*{*/
/**/
/*	return (0);*/
/*}*/
/**/
/**/
/*char	hitcylinder(t_ray ray, t_hit *hit, void *self)*/
/*{*/
/**/
/*	return (0);*/
/*}*/
