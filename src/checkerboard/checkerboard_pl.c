#include "minirt.h"

void	checkerboard_pl(t_hit *hit, t_plane *plane, int color)
{
	t_vec	u;
	t_vec	v;
	t_vec	center;

	u = get_orthogonal_vector(plane->axis);
	v = cross(plane->axis, u);
	center = vecsub(hit->point, plane->center);
	hit->color = set_color(dot(center, u), dot(center, v), color);
}
