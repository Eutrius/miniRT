#include "minirt.h"
#include <stdio.h>

static void	init(int argc, char **argv, t_scene *scene, t_data *data)
{
	char	*filestr;
	int		err;

	ft_memset(scene, 0, sizeof(t_scene));
	scene->data = data;
	filestr = readfile(argc, argv);
	err = unmarshal(filestr, scene);
	if (err)
		exit(1);
	free(filestr);
	set_camera_axis(scene);
	set_viewport(scene, scene->data->w, scene->data->h);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.mlx = mlx_init();
	mlx_get_screen_size(data.mlx, &data.w, &data.h);
	data.w /= 2;
	data.h /= 2;
	init(argc, argv, &data.scene, &data);
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "MiniRT");
	hooks(&data);
	render_scene(&data);
	mlx_loop(data.mlx);
}
