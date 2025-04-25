/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:47:33 by jyriarte          #+#    #+#             */
/*   Updated: 2025/04/25 13:44:06 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_camera(t_data *data)
{
	if (data->nobj_onhand != -1)
	{
		data->nobj_onhand = -1;
		printf("select camera to move\n");
	}
}

void	select_lights(t_data *data)
{
	static int	current_light;

	if (data->scene.lightc > 0)
	{
		if (data->nobj_onhand == -1)
			data->nobj_onhand = current_light;
		else
		{
			data->nobj_onhand = ((data->nobj_onhand + 1) % data->scene.lightc);
			current_light = data->nobj_onhand;
		}
		printf("selct light %i to move\n", data->nobj_onhand);
	}
}

void	select_rotate_camera(t_data *data)
{
	data->rot_cam = (data->rot_cam == 0);
	printf("toggle rotate camera %i\n", data->rot_cam);
}

void	toggle_bump(t_data *data)
{
	if (data->obj_onhand == -1)
		return ;
	data->scene.objs[data->obj_onhand].bump ^= 1;
	render_scene(data);
}

void	toggle_checker(t_data *data)
{
	if (data->obj_onhand == -1)
		return ;
	data->scene.objs[data->obj_onhand].checker ^= 1;
	render_scene(data);
}
