#include "minirt.h"

void	solve_quadratic(t_quadratic *quad)
{
	quad->discriminant = quad->b * quad->b - 4 * (quad->a * quad->c);
	if (quad->discriminant >= EPSILON)
	{
		quad->t1 = (quad->b - sqrtf(quad->discriminant)) / (2 * quad->a);
		quad->t2 = (quad->b + sqrtf(quad->discriminant)) / (2 * quad->a);
	}
}
