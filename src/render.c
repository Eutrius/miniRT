#include "minirt.h"
#include <stdio.h>

void	*render(t_scene scene, int w, int h, void *mlx)
{
	t_img	img;
	int		y;
	int		x;
	t_ray	r;
	t_hit	hit;
	t_hit	finalhit;
	int		i;

	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	y = h;
	while (y >= 0)
	{
		x = w;
		while (x >= 0)
		{
			i = 0;
			finalhit.color = 0;
			finalhit.t = 0xffffff;
			r = ray_per_pixel(&scene, &scene.cam, x, y);
			while (i < scene.objc)
			{
				if (scene.objs[i].hit(r, &hit, &scene.objs[i]))
					if (hit.t < finalhit.t)
						finalhit = hit;
				i++;
			}
			if (finalhit.color != 0)
				lightman(scene, r, &finalhit);
			pixel(&img, x, y, finalhit.color);
			x--;
		}
		y--;
	}
	printf("done rendering\n");
	return (img.img);
}

int	clamp(int val)
{
	if (val < 0)
		val = 0;
	if (val > 255)
		val = 255;
	return (val);
}

int	colormult(int color, float multiplier)
{
	int	rgba[3];
	int	ret[3];

	rgba[0] = (color >> 16) & 0xff;
	rgba[1] = (color >> 8) & 0xff;
	rgba[2] = color & 0xff;
	ret[0] = clamp((int)(rgba[0] * multiplier));
	ret[1] = clamp((int)(rgba[1] * multiplier));
	ret[2] = clamp((int)(rgba[2] * multiplier));
	return ((ret[0] << 16) | (ret[1] << 8) | ret[2]);
}

int	coloradd(int colora, int colorb)
{
	int	rgba[3];
	int	rgbb[3];
	int	ret[3];

	rgba[0] = (colora >> 16) & 0xff;
	rgba[1] = (colora >> 8) & 0xff;
	rgba[2] = colora & 0xff;
	rgbb[0] = (colorb >> 16) & 0xff;
	rgbb[1] = (colorb >> 8) & 0xff;
	rgbb[2] = colorb & 0xff;
	ret[0] = clamp(rgba[0] + rgbb[0]);
	ret[1] = clamp(rgba[1] + rgbb[1]);
	ret[2] = clamp(rgba[2] + rgbb[2]);
	return ((ret[0] << 16) | (ret[1] << 8) | ret[2]);
}
