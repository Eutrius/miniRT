#include "minirt.h"
#include <stdio.h>

// Function implementations
void	print_vec(const t_vec *vec)
{
	printf("VECTOR: x: %f, y: %f, z: %f\n", vec->x, vec->y, vec->z);
}

void	print_ambient(const t_amb *amb)
{
	printf("AMBIENT: ratio: %f, color: %d\n", amb->ratio, amb->color);
}

void	print_camera(const t_cam *cam)
{
	printf("CAMERA: pos: ");
	print_vec(&cam->pos);
	printf("CAMERA: ori: ");
	print_vec(&cam->forward);
	printf("CAMERA: fov: %f\n", cam->fov);
}

void	print_light(const t_light *light)
{
	printf("LIGHT: pos: ");
	print_vec(&light->pos);
	printf("LIGHT: ratio: %f, color: %d\n", light->ratio, light->color);
}

void	print_hit(const t_hit *hit)
{
	printf("HIT: normal: ");
	print_vec(&hit->normal);
	printf("HIT: color: %d, t: %f\n", hit->color, hit->t);
}

void	print_ray(const t_ray *ray)
{
	printf("RAY: start: ");
	print_vec(&ray->start);
	printf("RAY: dir: ");
	print_vec(&ray->dir);
}

void	print_object(const t_obj *obj)
{
	printf("OBJECT: self: %p, color: %d, hit: %p\n", obj->self, obj->color,
		obj->hit);
}

void	print_sphere(const t_sphere *sphere)
{
	printf("SPHERE: center: ");
	print_vec(&sphere->center);
	printf("SPHERE: radius: %f\n", sphere->radius);
}

void	print_plane(const t_plane *plane)
{
	printf("PLANE: coord: ");
	print_vec(&plane->center);
	printf("PLANE: normal: ");
	print_vec(&plane->axis);
}

void	print_cylinder(const t_cylinder *cylinder)
{
	printf("CYLINDER: center: ");
	print_vec(&cylinder->center);
	printf("CYLINDER: radius: %f, maxm: %f, axis: ", cylinder->radius,
		cylinder->height);
	print_vec(&cylinder->axis);
}

void	print_scene(const t_scene *scene)
{
	printf("SCENE: objs: %p, objc: %d\n", scene->objs, scene->objc);
	printf("SCENE: light: ");
	for (int i = 0; i < scene->lightc; i++)
		print_light(&scene->light[i]);
	printf("SCENE: amb: ");
	print_ambient(&scene->amb);
	printf("SCENE: cam: ");
	print_camera(&scene->cam);
}
