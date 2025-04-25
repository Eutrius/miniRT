/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:42:11 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:43:22 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <X11/keysym.h>

static void	translate(t_data *data, t_vec *vec, t_vec by);

void	translate_obj(t_data *data, int x, int y)
{
	t_sphere	*to_move;

	to_move = data->scene.objs[data->obj_onhand].self;
	translate(data, &to_move->center, vector(x, y, 0));
}

void	translate_z(t_data *data, int keycode, int x, int y)
{
	static int	rate;
	void		*obj;
	t_sphere	*to_move;
	t_hit		hit;

	if (rate == SCROLL_RATE)
	{
		data->obj_onhand = project_ray(&data->scene, &hit, x, y);
		if (data->obj_onhand != -1)
		{
			obj = data->scene.objs[data->obj_onhand].self;
			to_move = obj;
			translate(data, &to_move->center, vector(0, 0, NOBJ_SPEED * (2
						* (keycode == 4) - 1)));
		}
		rate = 0;
	}
	rate++;
}

void	translate_nobj(t_data *data, int keycode)
{
	t_vec	by;

	by.x = (2 * (keycode == XK_Right) - 1) - (2 * (keycode == XK_Left) - 1);
	by.y = (2 * (keycode == XK_Down) - 1) - (2 * (keycode == XK_Up) - 1);
	by.z = (2 * (keycode == XK_w) - 1) - (2 * (keycode == XK_s) - 1);
	if (by.x || by.y || by.z)
	{
		if (data->nobj_onhand == -1)
			translate(data, &data->scene.cam.pos, scalar(by, NOBJ_SPEED));
		else
			translate(data, &data->scene.light[data->nobj_onhand].pos,
				scalar(by, NOBJ_SPEED));
		render_scene(data);
	}
}

static void	translate(t_data *data, t_vec *vec, t_vec by)
{
	*vec = vecsum(*vec, scalar(data->scene.cam.right, by.x
				* data->scene.cam.half_height * SCALE));
	*vec = vecsum(*vec, scalar(data->scene.cam.up, -by.y
				* data->scene.cam.half_height * SCALE));
	*vec = vecsum(*vec, scalar(data->scene.cam.forward, by.z
				* data->scene.cam.half_height * SCALE));
}
