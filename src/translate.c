#include "minirt.h"

void	translate(t_data *data, t_vec *vec, float x, float y, float z)
{
	*vec = vecsum(*vec, scalar(data->scene.cam.right, x
				* data->scene.cam.half_height * SCALE));
	*vec = vecsum(*vec, scalar(data->scene.cam.up, -y
				* data->scene.cam.half_height * SCALE));
	*vec = vecsum(*vec, scalar(data->scene.cam.ori, z
				* data->scene.cam.half_height * SCALE));
}

void	translate_obj(t_data *data, int x, int y)
{
	void		*obj;
	t_sphere	*to_move;

	obj = data->scene.objs[data->obj_onhand].self;
	to_move = obj;
	translate(data, &to_move->center, x, y, 0);
}

void	translate_z(t_data *data, int keycode, int x, int y)
{
	static int	rate;
	void		*obj;
	t_sphere	*to_move;
	t_hit		hit;

	if (rate == 10)
	{
		data->obj_onhand = project_ray(&data->scene, &hit, x, y);
		if (data->obj_onhand != -1)
		{
			obj = data->scene.objs[data->obj_onhand].self;
			to_move = obj;
			translate(data, &to_move->center, 0, 0, 20.0f * (2 * (keycode == 4)
					- 1));
		}
		rate = 0;
	}
	rate++;
}

void	translate_nobj(t_data *data, int keycode)
{
	float	x;
	float	y;
	float	z;

	x = (2 * (keycode == RIGHT_KEY) - 1) - (2 * (keycode == LEFT_KEY) - 1);
	y = (2 * (keycode == DOWN_KEY) - 1) - (2 * (keycode == UP_KEY) - 1);
	z = (2 * (keycode == W_KEY) - 1) - (2 * (keycode == S_KEY) - 1);
	if (x || y || z)
	{
		if (data->nobj_onhand == -1)
			translate(data, &data->scene.cam.pos, x * 20.0f, y * 20.0f, z
				* 20.0f);
		else
			translate(data, &data->scene.light[data->nobj_onhand].pos, x
				* 20.0f, y * 20.0f, z * 20.0f);
		render_scene(data);
	}
}
