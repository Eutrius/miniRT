#include "../include/minirt.h"

static void	init(int argc, char **argv, t_scene *scene)
{
	char	*filestr;
	int		err;

	ft_memset(scene, 0, sizeof(t_scene));
	filestr = readfile(argc, argv);
	err = unmarshal(filestr, scene);
	free(filestr);
	if (err)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init(argc, argv, &data.scene);
	data.mlx = mlx_init();
	mlx_get_screen_size(data.mlx, &data.w, &data.h);
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "MiniRT");
	hooks(&data);
	mlx_loop(data.mlx);
}
