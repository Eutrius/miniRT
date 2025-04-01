#include "minirt.h"

void	translate(t_data *data, int x, int y)
{
	void		*obj;
	t_sphere	*to_move;

	obj = data->scene.objs[data->obj_onhand].self;
	to_move = obj;
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.right, x
				* data->scene.cam.half_height * SCALE));
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.up, -y
				* data->scene.cam.half_height * SCALE));
}

void	translate_z(t_data *data, int button, int x, int y)
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
			data->from_x = x;
			data->from_y = y;
			obj = data->scene.objs[data->obj_onhand].self;
			to_move = obj;
			to_move->center = vecsum(to_move->center,
					scalar(data->scene.cam.ori, 2.0f
						* data->scene.cam.half_height * (2 * (button == 4)
							- 1)));
		}
		rate = 0;
	}
	rate++;
}
