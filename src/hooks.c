#include "minirt.h"
#include <X11/keysym.h>

static int	input_event(int keycode, t_data *data);
static int	exit_event(t_data *data);

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_data	*data;
	t_scene	scene;
	t_hit	hit;

	data = param;
	scene = data->scene;
	if (button <= 3)
	{
		data->obj_onhand = project_ray(&scene, &hit, x, y);
		if (data->obj_onhand != -1)
		{
			data->from_x = x;
			data->from_y = y;
		}
	}
	else if (button <= 5)
		translate_z(data, button, x, y);
	return (0);
}

int	mouse_release_hook(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)param;
	data = param;
	if (data->obj_onhand == -1)
		return (0);
	if (button == L_MOUSE)
		translate_obj(data, x - data->from_x, y - data->from_y);
	if (button == R_MOUSE)
		transform(data, x, y);
	data->obj_onhand = -1;
	render_scene(data);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_loop_hook(data->mlx_win, render_scene, data);
	mlx_key_hook(data->mlx_win, input_event, data);
	mlx_hook(data->mlx_win, 17, 0, exit_event, data);
	mlx_hook(data->mlx_win, 4, 1L << 2, mouse_press_hook, data);
	mlx_hook(data->mlx_win, 5, 1L << 3, mouse_release_hook, data);
}

int	render_scene(void *arg)
{
	t_data	*data;

	data = arg;
	mlx_put_image_to_window(data->mlx, data->mlx_win, render(data->scene,
			data->w, data->h, data->mlx), 0, 0);
	return (0);
}

static int	input_event(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		exit_event(data);
	else if (keycode == C_KEY)
		data->nobj_onhand = -1;
	else if (keycode == L_KEY)
		data->nobj_onhand = ((data->nobj_onhand + 1) % data->scene.lightc);
	translate_nobj(data, keycode);
	return (0);
}

static int	exit_event(t_data *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}
