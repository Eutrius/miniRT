#include "minirt.h"
#include <X11/keysym.h>

static int	render_scene(void *arg);
static int	input_event(int keycode, t_data *data);
static int	exit_event(t_data *data);

int	mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("Mouse move at (%d, %d)\n", x, y);
	return (0);
}

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_data	*data;
	t_ray	ray;
	int		i;
	t_scene	scene;
	t_hit	hit;
	t_hit	finalhit;

	i = 0;
	data = param;
	scene = data->scene;
	if (button == 1)
	{
		ray = ray_per_pixel(&scene, &scene.cam, x, y);
		finalhit.t = 0xffffff;
		while (i < scene.objc)
		{
			if (scene.objs[i].hit(ray, &hit, &scene.objs[i]))
				if (hit.t < finalhit.t)
				{
					finalhit = hit;
					printf("hit");
					data->obj_onhand = i;
					data->from_x = x;
					data->from_y = y;
				}
			i++;
		}
	}
	printf("Mouse pressed: Button %d at (%d, %d)\n", button, x, y);
	return (0);
}

int	mouse_release_hook(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)param;
	data = param;
	if (button == 1)
	{
		translate(data, x - data->from_x, y - data->from_y);
	}
	printf("Mouse released: Button %d at (%d, %d)\n", button, x, y);
	return (0);
}
void	hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, render_scene, data);
	mlx_key_hook(data->mlx_win, input_event, data);
	mlx_hook(data->mlx_win, 17, 0, exit_event, data);
	mlx_hook(data->mlx_win, 6, 0, mouse_move, data);
	mlx_hook(data->mlx_win, 4, 1L << 2, mouse_press_hook, data);
	mlx_hook(data->mlx_win, 5, 1L << 3, mouse_release_hook, data);
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
