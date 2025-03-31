#include "minirt.h"

int	translate(t_data *data, int x, int y)
{
	void		*obj;
	t_sphere	*to_move;
	float		fov_factor;

	obj = data->scene.objs[data->obj_onhand].self;
	to_move = obj;
	fov_factor = (1.0f / (data->scene.cam.fov * 0.5f));
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.right, x
				* fov_factor));
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.up, -y
				* fov_factor));
	return (0);
}
