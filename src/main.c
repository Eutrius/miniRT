#include "../include/minirt.h"
#include <math.h>
#include <stdio.h>


static	void init(int argc, char **argv, t_scene *scene)
{
	char	*filestr;
	int		err;

	ft_memset(scene, 0, sizeof(t_scene));
	filestr = readfile(argc, argv);
	err = unmarshal(filestr, scene);
	free(filestr);
	if (err)
	{

		exit(1);
	}
}

int main(int argc, char **argv)
{
	t_scene	scene;
	void	*mlx;
	void	*mlx_win;
	int		h;
	int		w;

	init(argc, argv, &scene);
	exit(0);
	mlx = mlx_init();
	mlx_get_screen_size(mlx, &w, &h);
	mlx_win = mlx_new_window(mlx, w, h, "MiniRT");

	mlx_put_image_to_window(mlx, mlx_win, render(scene, w, h, mlx), 0, 0);
	mlx_loop(mlx);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	*render(t_scene scene, int w, int h, void *mlx)
{
	t_img	img;
	int		y;
	int		x;
	t_ray	r;
	float	cw;
	float	ch;
	t_hit	hit;
	t_hit	finalhit;
	int		i;
	float	deltax;
	float	deltay;

	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	cw = tan((scene.cam.fov * (3.14 / 180)) / 2);
	ch = cw / (((float)w / (float)h));
	deltax = (cw * 2) / w;
	deltay = (ch * 2) / h;
	y =	h;
	while (y >= 0)
	{
		x = w;
		while (x >= 0)
		{
			i = 0;
			t_vec pp = vecsum(scene.cam.ori, scene.cam.pos);
			pp.x = pp.x - cw + (x * deltax) + (deltax / 2);
			pp.y = pp.y + ch - (y * deltay) + (deltay / 2);
			finalhit.color = 0;
			finalhit.t = 0xffffff;
			r = ray(scene.cam.pos, vecsub(pp, scene.cam.pos));
			while (i < scene.objc)
			{
				if (scene.objs[i].hit(r, &hit, &scene.objs[i]))
					if (hit.t < finalhit.t)
						finalhit = hit;
				i++;
			}
			my_mlx_pixel_put(&img, x, y, finalhit.color);
			x--;
		}
		y--;
	}
	return img.img;
}

