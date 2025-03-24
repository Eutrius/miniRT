#include "../include/minirt.h"
#include <stdio.h>

void	lightman(t_scene scene, t_ray r, t_hit *hit);
int		coloradd(int colora, int colorb);
int		colormult(int color, float multiplier);
int		is_hit_closer_than_light(t_ray ray, t_hit hit, t_light light);

void	*render(t_scene scene, int w, int h, void *mlx)
{
	t_img	img;
	int		y;
	int		x;
	t_ray	r;
	float	camw;
	float	camh;
	t_hit	hit;
	t_hit	finalhit;
	int		i;
	float	deltax;
	float	deltay;
	t_vec	pp;

	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	camw = tan((scene.cam.fov * (3.14 / 180)) / 2);
	camh = camw / (((float)w / (float)h));
	deltax = (camw * 2) / w;
	deltay = (camh * 2) / h;
	y = h;
	while (y >= 0)
	{
		x = w;
		while (x >= 0)
		{
			i = 0;
			pp = vecsum(scene.cam.ori, scene.cam.pos);
			pp.x = pp.x - camw + (x * deltax) + (deltax / 2);
			pp.y = pp.y + camh - (y * deltay) + (deltay / 2);
			finalhit.color = 0;
			finalhit.t = 0xffffff;
			r = ray(scene.cam.pos, normalize(vecsub(pp, scene.cam.pos)));
			while (i < scene.objc)
			{
				if (scene.objs[i].hit(r, &hit, &scene.objs[i]))
					if (hit.t < finalhit.t)
						finalhit = hit;
				i++;
			}
			if (finalhit.color != 0)
			{
				finalhit.color = coloradd(finalhit.color,
						colormult(scene.amb.color, scene.amb.ratio));
				lightman(scene, r, &finalhit);
			}
			pixel(&img, x, y, finalhit.color);
			x--;
		}
		y--;
	}
	printf("done rendering\n");
	return (img.img);
}
void	lightman(t_scene scene, t_ray r, t_hit *hit)
{
	t_hit	ph;
	int		i;
	float	intensity;
	t_ray	lightray;

	i = -1;
	lightray.start = vecsum(r.start, scalar(r.dir, hit->t - 0.0001f));
	lightray.dir = normalize(vecsub(scene.light.pos, lightray.start));
	while (++i < scene.objc)
	{
		if (scene.objs[i].hit(lightray, &ph, &scene.objs[i]))
			if (is_hit_closer_than_light(lightray, ph, scene.light))
				return ;
	}
	intensity = dot(hit->normal, lightray.dir);
	if (intensity < 0)
		return ;
	hit->color = coloradd(hit->color, colormult(scene.light.color,
				scene.light.ratio * intensity));
}

int	is_hit_closer_than_light(t_ray ray, t_hit hit, t_light light)
{
	t_vec	hit_point;
	t_vec	to_hit;
	t_vec	to_light;

	hit_point = vecsum(ray.start, scalar(ray.dir, hit.t));
	to_hit = vecsub(hit_point, ray.start);
	to_light = vecsub(light.pos, ray.start);
	return (dot(to_hit, to_hit)) < (dot(to_light, to_light));
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
