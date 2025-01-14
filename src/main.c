#include "../include/minirt.h"

static	void init(int argc, char **argv, t_scene *scene)
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

int main(int argc, char **argv)
{
	t_scene	scene;
	void	*mlx;
	void	*mlx_win;
	int		h;
	int		w;

	init(argc, argv, &scene);
	mlx = mlx_init();
	mlx_get_screen_size(mlx, &w, &h);
	mlx_win = mlx_new_window(mlx, w, h, "MiniRT");

	mlx_put_image_to_window(mlx, mlx_win, render(scene, w, h, mlx), 0, 0);
	mlx_loop(mlx);
}



