/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:11 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:41:13 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_orthogonal_vector(t_vec axis)
{
	t_vec	ortho;

	if (fabs(axis.y) < 0.9)
		ortho = cross(axis, (t_vec){0.0, 1.0, 0.0});
	else
		ortho = cross(axis, (t_vec){1.0, 0.0, 0.0});
	if (veclen(ortho) < 1e-9)
	{
		if (fabs(axis.y) >= 0.9)
			ortho = (t_vec){0.0, 0.0, 2 * (axis.y > 0) - 1};
		else
			ortho = (t_vec){0.0, 1.0, 0.0};
	}
	return (normalize(ortho));
}

int	set_color(float u, float v, int color)
{
	int	check_pattern;

	check_pattern = (int)floor(u) + (int)floor(v);
	if (check_pattern % 2 == 0)
		return (0);
	else
		return (color);
}
