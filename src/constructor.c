#include "../include/minirt.h"

t_vec	vector(float x, float y, float z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_ray	ray(t_vec start, t_vec dir)
{
	t_ray	ret;

	ret.dir = dir;
	ret.start = start;
	return (ret);
}
