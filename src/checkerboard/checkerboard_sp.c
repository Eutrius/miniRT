#include "minirt.h"

void	checkerboard_sp(t_hit *hit, t_sphere *sphere, int color)
{
	float	u;
	float	v;
	t_vec	center;

	center = normalize(vecsub(hit->point, sphere->center));
	u = (atan2(center.z, center.x) + M_PI);
	v = acos(center.y);
	hit->color = set_color(u * sphere->radius, v * sphere->radius, color);
}
