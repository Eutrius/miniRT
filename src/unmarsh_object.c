/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmarsh_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:42:13 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 19:14:53 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <unistd.h>

static int	unmarshalsphere(char *str, t_scene *scene)
{
	char		**args;
	t_sphere	*self;
	int			err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		self = ft_calloc(sizeof(t_sphere), 1);
		self->center = getcoords(args[1], &err);
		self->radius = ft_atof(args[2]);
		if (self->radius < 0.0)
			err = write(2, "Error: sphere diameter cannot be negative\n", 43);
		scene->objs[scene->objc - 1].self = self;
		scene->objs[scene->objc - 1].type = SPHERE;
		scene->objs[scene->objc - 1].hit = hitsphere;
		scene->objs[scene->objc - 1].color = getcolor(args[3], &err);
		scene->objc--;
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

static int	unmarshalplane(char *str, t_scene *scene)
{
	char	**args;
	t_plane	*self;
	int		err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		self = ft_calloc(sizeof(t_plane), 1);
		self->center = getcoords(args[1], &err);
		self->axis = getcoords(args[2], &err);
		if (is_normal(self->axis) == 0)
			err = write(2, "Error: Normal is not normal :)\n", 32);
		scene->objs[scene->objc - 1].self = self;
		scene->objs[scene->objc - 1].type = PLANE;
		scene->objs[scene->objc - 1].hit = hitplane;
		scene->objs[scene->objc - 1].color = getcolor(args[3], &err);
		scene->objc--;
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	if (err)
		free(self);
	free_matrix(args);
	return (err);
}

static int	unmarshalcylinder(char *str, t_scene *scene)
{
	char		**args;
	t_cylinder	*self;
	int			err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3] && args[4] && args[5])
	{
		self = ft_calloc(sizeof(t_cylinder), 1);
		err = get_cy(scene, args, self);
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	if (err)
		free(self);
	free_matrix(args);
	return (err);
}

static int	unmarshalcone(char *str, t_scene *scene)
{
	char	**args;
	t_cone	*self;
	int		err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3] && args[4])
	{
		self = ft_calloc(sizeof(t_cone), 1);
		err = get_cone(scene, args, self);
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	if (err)
		free(self);
	free_matrix(args);
	return (err);
}

int	unmarshalobject(char *str, t_scene *scene)
{
	int	err;

	err = 0;
	if (!ft_strncmp(str, "sp ", 3))
		err = unmarshalsphere(str, scene);
	if (!ft_strncmp(str, "pl ", 3))
		err = unmarshalplane(str, scene);
	if (!ft_strncmp(str, "cy ", 3))
		err = unmarshalcylinder(str, scene);
	if (!ft_strncmp(str, "co ", 3))
		err = unmarshalcone(str, scene);
	return (err);
}
