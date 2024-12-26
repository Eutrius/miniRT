#include "../include/minirt.h"
#include <math.h>
#include <stdio.h>


t_scene init_scene(void)
{
   t_scene scene;
   t_sphere *sphere;
   t_sphere *sphere2;

   sphere = malloc(sizeof(t_sphere));
   sphere->center = (t_vec){0, 0, -9, 1};
   sphere->radius = 4;

   sphere2 = malloc(sizeof(t_sphere));
   sphere2->center = (t_vec){1, 2, -10, 1};
   sphere2->radius = 3.5;


   scene.objs = malloc(sizeof(t_obj) * 2);
   scene.objc = 2;
   scene.objs[0] = (t_obj){
       .self = sphere,
       .color = 0xFFccaa,
       .hit = hitsphere
   };
   scene.objs[1] = (t_obj){
       .self = sphere2,
       .color = 0x00FF1a,
       .hit = hitsphere
   };

   scene.cam = (t_cam){
       .pos = (t_vec){0, 0, 0, 1},
       .ori = (t_vec){0, 0, -1, 0},
       .fov = 90
   };

   scene.light = (t_light){
       .pos = (t_vec){0, 5, 0, 1},
       .ratio = 0.7,
       .color = 0xFFFFFF
   };

   scene.amb = (t_amb){
       .ratio = 0.3,
       .color = 0xFFFFFF
   };

   return scene;
}



int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_scene	scene;
	void	*mlx;
	void	*mlx_win;
	int		h;
	int		w;


	scene = init_scene();
	//init scena();
	

	mlx = mlx_init();
	mlx_get_screen_size(mlx, &w, &h);
	mlx_win = mlx_new_window(mlx, w, h, "Hello world!");
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
	printf("cw=%f, ch=%f\n", cw, ch);
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
			/*printf("pp.x=%f pp.y=%f pp.z=%f, deltax=%f, deltay=%f\n", pp.x, pp.y, pp.z, deltax, deltay);*/
			finalhit.color = 0;
			finalhit.t = 0xffffff;
			while (i < scene.objc)
			{
				r = ray(scene.cam.pos, vecsub(pp, scene.cam.pos));
				if (scene.objs[i].hit(r, &hit, &scene.objs[i]))
				{
					if (hit.t < finalhit.t)
						finalhit = hit;
				}
				i++;
			}
			my_mlx_pixel_put(&img, x, y, finalhit.color);
			x--;
		}
		y--;
	}
	printf("done rendering\n");
	return img.img;
}

