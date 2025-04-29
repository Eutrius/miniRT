/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:42:09 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:43:20 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	vec_to_camera_point(t_data *data, t_vec v, float *x, float *y);
static void	transform_sphere(t_data *data, t_sphere *sphere, int x, int y);
static void	transform_cylinder(t_data *data, t_cylinder *cylinder, int x,
				int y);
static void	transform_cone(t_data *data, t_cone *cone, int x, int y);

void	transform(t_data *data, int x, int y)
{
	t_obj	*obj;

	obj = &data->scene.objs[data->obj_onhand];
	if (obj->type == SPHERE)
		transform_sphere(data, (t_sphere *)obj->self, x, y);
	else if (obj->type == CYLINDER)
		transform_cylinder(data, (t_cylinder *)obj->self, x, y);
	else if (obj->type == CONE)
		transform_cone(data, (t_cone *)obj->self, x, y);
}

static void	transform_sphere(t_data *data, t_sphere *sphere, int x, int y)
{
	float	from_dist;
	float	to_dist;
	float	sphere_x;
	float	sphere_y;

	vec_to_camera_point(data, sphere->center, &sphere_x, &sphere_y);
	from_dist = point_distance(data->from_x, data->from_y, sphere_x, sphere_y);
	to_dist = point_distance(x, y, sphere_x, sphere_y);
	sphere->radius += ((point_distance(x, y, data->from_x, data->from_y)
				* (data->scene.cam.half_height) * SCALE) * (2
				* (from_dist < to_dist) - 1));
	sphere->radius = fmax(sphere->radius, MIN_PROP);
}

static void	transform_cylinder(t_data *data, t_cylinder *cylinder, int x, int y)
{
	float	from_dist;
	float	to_dist;
	float	cyl_x;
	float	cyl_y;

	vec_to_camera_point(data, cylinder->center, &cyl_x, &cyl_y);
	from_dist = point_distance(data->from_x, data->from_y, cyl_x, cyl_y);
	to_dist = point_distance(x, y, cyl_x, cyl_y);
	cylinder->radius += fabs((x - data->from_x) * SCALE) * (2
			* (from_dist < to_dist) - 1);
	cylinder->height += fabs((y - data->from_y) * SCALE) * (2
			* (from_dist < to_dist) - 1);
	cylinder->radius = fmax(cylinder->radius, MIN_PROP);
	cylinder->height = fmax(cylinder->height, MIN_PROP);
}

static void	transform_cone(t_data *data, t_cone *cone, int x, int y)
{
	float	from_dist;
	float	to_dist;
	float	cone_x;
	float	cone_y;

	vec_to_camera_point(data, cone->center, &cone_x, &cone_y);
	from_dist = point_distance(data->from_x, data->from_y, cone_x, cone_y);
	to_dist = point_distance(x, y, cone_x, cone_y);
	cone->angle += fabs((x - data->from_x) * SCALE) * (2 * (from_dist < to_dist)
			- 1);
	cone->angle = fmax(cone->angle, MIN_PROP);
}

static void	vec_to_camera_point(t_data *data, t_vec v, float *x, float *y)
{
	float	screen_x;
	float	screen_y;
	t_vec	proj_dir;

	v = vecsub(v, data->scene.cam.pos);
	proj_dir.x = dot(v, data->scene.cam.right);
	proj_dir.y = dot(v, data->scene.cam.up);
	proj_dir.z = dot(v, data->scene.cam.forward);
	if (proj_dir.z <= 0)
	{
		*x = data->w * 0.5f;
		*y = data->h * 0.5f;
	}
	screen_x = proj_dir.x / (proj_dir.z * data->scene.cam.half_width);
	screen_y = proj_dir.y / (proj_dir.z * data->scene.cam.half_height);
	*x = ((screen_x + 1.0f) * 0.5f) * data->w;
	*y = ((1.0f - screen_y) * 0.5f) * data->h;
}
