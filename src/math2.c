#include "minirt.h"

t_vec	normalize(t_vec v)
{
	float	length;
	t_vec	r;

	length = veclen(v);
	r.x = v.x / length;
	r.y = v.y / length;
	r.z = v.z / length;
	return (r);
}

void	quadratic(t_quadratic *quad)
{
	quad->discriminant = quad->b * quad->b - 4 * (quad->a * quad->c);
	if (quad->discriminant >= EPSILON)
	{
		quad->t1 = (-quad->b - sqrtf(quad->discriminant)) / (2 * quad->a);
		quad->t2 = (-quad->b + sqrtf(quad->discriminant)) / (2 * quad->a);
	}
}

float	point_distance(int x1, int y1, int x2, int y2)
{
	int	x;
	int	y;

	x = x1 - x2;
	y = y1 - y2;
	return (sqrt(x * x + y * y));
}
