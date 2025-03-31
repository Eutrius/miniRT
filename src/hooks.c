#include "minirt.h"
#include <X11/keysym.h>

static int	render_scene(void *arg);
static int	input_event(int keycode, t_data *data);
static int	exit_event(t_data *data);

int	mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	printf("Mouse button %d pressed at (%d, %d)\n", button, x, y);
	return (0);
}
int	mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("Mouse move at (%d, %d)\n", x, y);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, render_scene, data);
	mlx_key_hook(data->mlx_win, input_event, data);
	mlx_mouse_hook(data->mlx_win, mouse_hook, data);
	mlx_hook(data->mlx_win, 17, 0, exit_event, data);
	mlx_hook(data->mlx_win, 6, 0, mouse_move, data);
}

static int	render_scene(void *arg)
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
	return (0);
}

static int	exit_event(t_data *data)
{
	(void)data;
	exit(EXIT_SUCCESS);
}
