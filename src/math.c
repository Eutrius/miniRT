#include "../include/minirt.h"

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

t_vec	vecsum(t_vec a, t_vec b)
{
	t_vec	r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return (r);
}

t_vec	vecsub(t_vec a, t_vec b)
{
	t_vec	r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return (r);
}

float	veclen(t_vec a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	scalar(t_vec a, float b)
{
	t_vec	r;

	r.x = a.x * b;
	r.y = a.y * b;
	r.z = a.z * b;
	return (r);
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec	r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return (r);
}
