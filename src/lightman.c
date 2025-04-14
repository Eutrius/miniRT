#include "minirt.h"


static int	is_hit_closer_than_light(t_ray ray, t_hit hit, t_light light)
{
	t_vec	hit_point;
	t_vec	to_hit;
	t_vec	to_light;

	hit_point = vecsum(ray.start, scalar(ray.dir, hit.t));
	to_hit = vecsub(hit_point, ray.start);
	to_light = vecsub(light.pos, ray.start);
	return (dot(to_hit, to_hit)) < (dot(to_light, to_light));
}

void	ambient(t_hit *h, t_amb ambient)
{
	h->color = coloradd(h->color, colormult(ambient.color, ambient.ratio));
}

void diffuse(t_hit *h, t_light light, t_ray lightray)
{
	float	intensity;

	intensity = dot(h->normal, lightray.dir);
	if (intensity < 0)
		return ;
	h->color = coloradd(h->color, colormult(light.color,
	light.ratio * intensity));

}

void specular(t_hit *h, t_light light, t_ray lightray, float shininess)
{
	t_vec reflected_ray;
    t_vec view_dir;
    float dot_product;
    float intensity;

    reflected_ray = vecsub(scalar(h->normal, 2 * dot(lightray.dir, h->normal)), lightray.dir);
    view_dir = normalize(vecsub(h->point, lightray.start));
    dot_product = dot(reflected_ray, view_dir);
    if (dot_product > 0) {
        intensity = powf(dot_product, shininess);
        h->color = coloradd(h->color, colormult(light.color, light.ratio * intensity));
    }
}

void lightman(t_scene scene, t_ray r, t_hit *hit)
{
    t_hit ph;
    int i;
    int l;
    t_ray lightray;
    t_light curr_light;
    char in_shadow;

    l = -1;
    lightray.start = vecsum(r.start, scalar(r.dir, hit->t - 0.0001f));
    while (++l < scene.lightc)
    {
        i = -1;
        in_shadow = 0;
        curr_light = scene.light[l];
        lightray.dir = normalize(vecsub(curr_light.pos, lightray.start));
        while (++i < scene.objc && in_shadow == 0)
        {
            if (scene.objs[i].hit(lightray, &ph, &scene.objs[i]))
            {
                if (is_hit_closer_than_light(lightray, ph, curr_light))
                    in_shadow = 1;
            }
        }
        if (!in_shadow)
        {
            diffuse(hit, curr_light, lightray);
            specular(hit, curr_light, lightray, SHINYNESS);
        }
    }
    ambient(hit, scene.amb);
}
