/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_man.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:59 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 19:04:04 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	if (mat)
		free(mat);
}

void	free_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->objc)
	{
		if (scene->objs[i].self)
			free(scene->objs[i].self);
		if (scene->objs[i].texture)
		{
			mlx_destroy_image(scene->data->mlx, scene->objs[i].texture->img);
			free(scene->objs[i].texture);
		}
		i++;
	}
	if (scene->objs)
		free(scene->objs);
	if (scene->light)
		free(scene->light);
}
