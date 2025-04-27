/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmarsh_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:42:15 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/27 11:57:07 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	getcoords(char *str, int *err)
{
	t_vec	ret;
	char	**coord;

	ret = vector(0, 0, 0);
	coord = ft_split(str, ',');
	if (!is_float(coord[0]) || !is_float(coord[1]) || !is_float(coord[2]))
		*err = write(2, "Error: Wrong Coords format, (f.f,f.f,f.f)\n", 43);
	ret.x = ft_atof(coord[0]);
	ret.y = ft_atof(coord[1]);
	ret.z = ft_atof(coord[2]);
	free_matrix(coord);
	return (ret);
}

int	getcolor(char *str, int *err)
{
	unsigned int	ret;
	int				cur;
	char			**rgb;
	int				i;

	i = 0;
	ret = 0;
	rgb = ft_split(str, ',');
	while (rgb[i] && *err == 0)
	{
		cur = ft_atof(rgb[i]);
		if (!is_float(rgb[i]) || cur > 255 || cur < 0)
			*err = write(2, "Error: Wrong format, (0-255,0-255,0-255)\n", 41);
		ret = ret << 8;
		ret = cur | ret;
		i++;
	}
	free_matrix(rgb);
	return (ret);
}
