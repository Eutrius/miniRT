#include "../include/minirt.h"
#include <stdlib.h>

t_vec v0()
{
	t_vec vec;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	vec.w = 1;
	return (vec);
}

t_ray ray(t_vec start, t_vec dir)
{
	t_ray ret;

	ret.dir = dir;
	ret.start = start;
	return (ret);
}
