/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmarsh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:42:17 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:59:55 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <unistd.h>

static int	unmarshalcamera(char *str, t_scene *scene)
{
	static char	present;
	char		**args;
	int			err;

	err = 0;
	if (present != 0)
		return (write(2, "Error: Too many cameras\n", 25));
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		scene->cam.pos = getcoords(args[1], &err);
		scene->cam.forward = getcoords(args[2], &err);
		if (is_normal(scene->cam.forward) == 0)
			err = write(2,
					"Error: Wrong camera orientation [-1,1][-1,1][-1,1]\n", 51);
		if (!is_float(args[3]))
			err = (write(2, "Error: Fov not a number ([0.0,180.0])\n", 39));
		scene->cam.fov = ft_atof(args[3]);
		if (scene->cam.fov < 0.0 || scene->cam.fov > 180.0)
			err = (write(2, "Error: Wrong FOV, ([0.0,180.0])\n", 33));
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

static int	unmarshallight(char *str, t_scene *scene)
{
	char	**args;
	int		err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		scene->light[scene->lightc - 1].pos = getcoords(args[1], &err);
		if (!is_float(args[2]))
			err = (write(2, "Light Ratio not a number ([0.0,1.0])\n", 38));
		scene->light[scene->lightc - 1].ratio = ft_atof(args[2]);
		if (scene->light[scene->lightc - 1].ratio < 0.0
			|| scene->light[scene->lightc - 1].ratio > 1.0)
			err = (write(2, "Wrong Light Ratio, ([0.0,1.0])\n", 32));
		scene->light[scene->lightc].color = getcolor(args[3], &err);
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	scene->lightc--;
	return (err);
}

static int	unmarshalambient(char *str, t_scene *scene)
{
	static char	present;
	char		**args;
	int			err;

	err = 0;
	if (present != 0)
		return (write(2, "Error: Too many Ambient lights\n", 32));
	args = ft_split(str, ' ');
	if (args && args[1] && args[2])
	{
		if (!is_float(args[1]))
			err = (write(2, "Ambient Ratio not a number ([0.0,1.0])\n", 40));
		scene->amb.ratio = ft_atof(args[1]);
		if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
			err = (write(2, "Wrong Ambient Ratio, ([0.0,1.0])\n", 31));
		scene->amb.color = getcolor(args[2], &err);
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

/* in the int array counts the firct is the objc and the second is the lightc
 * norme reasons */
int	malloc_objs(t_scene *scene, char **spl, int *counts)
{
	int		err;
	int		i;
	char	*str;

	err = 0;
	i = 0;
	ft_memset(counts, 0, sizeof(int) * 2);
	while (spl[i])
	{
		str = spl[i];
		if (ft_strchr(str, 'L'))
			counts[1]++;
		else if (!ft_strchr(str, 'A') && !ft_strchr(str, 'C'))
			counts[0]++;
		i++;
	}
	scene->objs = ft_calloc(sizeof(t_obj), (counts[0] + 1));
	scene->light = ft_calloc(sizeof(t_light), (counts[1] + 1));
	scene->objc = counts[0];
	scene->lightc = counts[1];
	if (scene->objs == 0 || scene->light == 0)
		err = write(2, "Error: Malloc on objects or lights\n", 36);
	return (err);
}

/*
sorry i had to create the 3 array counts for norminette, counts[2] is the error
*/
int	unmarshal(char *file, t_scene *scene)
{
	char	**spl;
	char	*str;
	int		i;
	int		counts[3];

	counts[2] = 0;
	i = -1;
	spl = ft_split(file, '\n');
	counts[2] = malloc_objs(scene, spl, counts);
	while (spl[++i] != 0 && counts[2] == 0)
	{
		str = spl[i];
		if (ft_strchr(str, 'A'))
			counts[2] = unmarshalambient(str, scene);
		else if (ft_strchr(str, 'L'))
			counts[2] = unmarshallight(str, scene);
		else if (ft_strchr(str, 'C'))
			counts[2] = unmarshalcamera(str, scene);
		else
			counts[2] = unmarshalobject(str, scene);
	}
	scene->objc = counts[0];
	scene->lightc = counts[1];
	free_matrix(spl);
	return (counts[2]);
}
