#include "minirt.h"

void	translate(t_data *data, int x, int y)
{
	void		*obj;
	t_sphere	*to_move;
	t_cone		*cone;

	obj = data->scene.objs[data->obj_onhand].self;
	to_move = obj;
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.right, x
				* data->scene.cam.half_height * SCALE));
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.up, -y
				* data->scene.cam.half_height * SCALE));
	if (data->scene.objs[data->obj_onhand].type == CONE)
	{
		cone = obj;
		print_vec(&cone->center);
		print_vec(&cone->axis);
		printf("%f\n", cone->angle);
	}
}
