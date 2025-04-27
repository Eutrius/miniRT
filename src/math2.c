/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:57 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 19:00:55 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return ;
	}
	quad->t1 = 0;
	quad->t1 = 0;
}

float	point_distance(int x1, int y1, int x2, int y2)
{
	int	x;
	int	y;

	x = x1 - x2;
	y = y1 - y2;
	return (sqrt(x * x + y * y));
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
