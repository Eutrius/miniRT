
#include "minirt.h"

int	translate(t_data *data, int x, int y)
{
	void		*obj;
	t_sphere	*to_move;

	obj = data->scene.objs[data->obj_onhand].self;
	to_move = obj;
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.right, x
				/ 100.0));
	to_move->center = vecsum(to_move->center, scalar(data->scene.cam.up, y
				/ 100.0));
	print_sphere(data->scene.objs[data->obj_onhand].self);
	return (0);
}
