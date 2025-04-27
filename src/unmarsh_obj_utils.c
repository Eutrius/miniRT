/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmarsh_obj_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:07:22 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/27 11:51:03 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_cone(t_scene *scene, char **args, t_cone *self, int index)
{
	int	err;

	err = 0;
	self->center = getcoords(args[1], &err);
	self->axis = getcoords(args[2], &err);
	if (is_normal(self->axis) == 0)
		return (write(2, "Error: Normal is not normal :)\n", 32));
	self->angle = ft_atof(args[3]);
	if (self->angle < 0.0)
		return (write(2, "Error: cone angle cannot be negative\n", 38));
	scene->objs[index].self = self;
	scene->objs[index].type = CONE;
	scene->objs[index].hit = hitcone;
	scene->objs[index].color = getcolor(args[4], &err);
	return (err);
}

int	get_cy(t_scene *scene, char **args, t_cylinder *self, int index)
{
	int	err;

	err = 0;
	self->center = getcoords(args[1], &err);
	self->axis = getcoords(args[2], &err);
	if (is_normal(self->axis) == 0)
		return (write(2, "Error: Normal is not normal :)\n", 32));
	self->radius = ft_atof(args[3]) / 2;
	self->height = ft_atof(args[4]);
	if (self->radius < 0.0)
		return (write(2, "Error: cylinder diameter cannot be negative\n", 44));
	self->radius = ft_atof(args[3]) / 2;
	scene->objs[index].self = self;
	scene->objs[index].type = CYLINDER;
	scene->objs[index].hit = hitcylinder;
	scene->objs[index].color = getcolor(args[5], &err);
	return (err);
}
