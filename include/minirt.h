/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:04:02 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/29 18:04:04 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define EPSILON 0.00001f
# define SCALE 0.05f
# define MIN_PROP 1.0f
# define SCROLL_RATE 10
# define NOBJ_SPEED 20.0f
# define L_MOUSE 1
# define M_MOUSE 2
# define R_MOUSE 3
# define SHINYNESS 0.9f
# define ROUGHNESS 0.5f

typedef struct s_data	t_data;

typedef enum e_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE
}						t_obj_type;

typedef struct s_vec
{
	float				x;
	float				y;
	float				z;
}						t_vec;

typedef struct s_ambient
{
	float				ratio;
	int					color;
}						t_amb;

typedef struct s_camera
{
	t_vec				pos;
	t_vec				forward;
	t_vec				up;
	t_vec				right;
	float				aspect_ratio;
	float				half_height;
	float				half_width;
	float				fov;
}						t_cam;

typedef struct s_light
{
	t_vec				pos;
	float				ratio;
	int					color;
}						t_light;

typedef struct s_hit
{
	t_vec				normal;
	int					color;
	float				t;
	t_vec				point;
}						t_hit;

typedef struct s_ray
{
	t_vec				start;
	t_vec				dir;
}						t_ray;

typedef struct s_quadratic
{
	float				a;
	float				b;
	float				c;
	float				discriminant;
	float				t1;
	float				t2;
}						t_quadratic;

typedef struct s_object
{
	void				*self;
	t_obj_type			type;
	int					color;
	float				rough;
	int					bump;
	int					checker;
	char				(*hit)(t_ray ray, t_hit *hit, void *self);
}						t_obj;

typedef struct s_sphere
{
	t_vec				center;
	float				radius;
}						t_sphere;

typedef struct s_plane
{
	t_vec				center;
	t_vec				axis;
}						t_plane;

typedef struct s_cylinder
{
	t_vec				center;
	t_vec				axis;
	float				radius;
	float				height;
}						t_cylinder;

typedef struct s_cone
{
	t_vec				center;
	t_vec				axis;
	float				angle;
}						t_cone;

typedef struct s_scene
{
	t_obj				*objs;
	int					objc;
	t_light				*light;
	int					lightc;
	t_amb				amb;
	t_cam				cam;
	t_data				*data;

}						t_scene;

typedef struct s_mlximg
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_img;

typedef struct s_data
{
	t_scene				scene;
	void				*mlx;
	void				*mlx_win;
	int					h;
	int					w;
	int					obj_onhand;
	int					from_x;
	int					from_y;
	int					nobj_onhand;
	int					rot_cam;

}						t_data;

/*rendering*/

void					pixel(t_img *data, int x, int y, int color);
void					*render(t_scene scene, int w, int h, void *mlx);
void					lightman(t_scene scene, t_ray r, t_hit *hit);
void					bump(t_hit *hit);

/*RAYTRACING*/
char					hitsphere(t_ray ray, t_hit *hit, void *self);
char					hitcylinder(t_ray ray, t_hit *hit, void *self);
char					hitcone(t_ray ray, t_hit *hit, void *self);
char					hitplane(t_ray ray, t_hit *hit, void *self);

/*unmarshal*/
char					*readfile(int argc, char **argv);
int						unmarshal(char *str, t_scene *scene);
int						unmarshalobject(char *str, t_scene *scene);
int						getcolor(char *str, int *err);
t_vec					getcoords(char *str, int *err);
int						get_cone(t_scene *scene, char **args, t_cone *self,
							int i);
int						get_cy(t_scene *scene, char **args, t_cylinder *self,
							int i);

// utils
char					is_float(char *str);
t_ray					ray(t_vec start, t_vec dir);
t_ray					ray_per_pixel(t_scene *scene, t_cam *camera, int x,
							int y);
t_vec					vector(float x, float y, float z);
t_vec					vecsum(t_vec a, t_vec b);
float					veclen(t_vec a);
t_vec					vecsub(t_vec a, t_vec b);
float					dot(t_vec a, t_vec b);
t_vec					scalar(t_vec a, float b);
t_vec					cross(t_vec a, t_vec b);
t_vec					normalize(t_vec v);
void					quadratic(t_quadratic *quad);
int						coloradd(int colora, int colorb);
int						colormult(int color, float multiplier);
int						clamp(int val);
float					point_distance(int x1, int y1, int x2, int y2);
char					is_normal(t_vec vec);
t_vec					negate(t_vec v);

// memory
void					free_matrix(char **mat);
void					free_scene(t_scene *scene);

// debug
void					print_vec(const t_vec *vec);
void					print_ambient(const t_amb *amb);
void					print_camera(const t_cam *cam);
void					print_light(const t_light *light);
void					print_hit(const t_hit *hit);
void					print_ray(const t_ray *ray);
void					print_object(const t_obj *obj);
void					print_sphere(const t_sphere *sphere);
void					print_plane(const t_plane *plane);
void					print_cylinder(const t_cylinder *cylinder);
void					print_scene(const t_scene *scene);

void					hooks(t_data *data);
void					set_camera_axis(t_scene *scene);
void					set_viewport(t_scene *scene, int w, int h);
void					translate_obj(t_data *data, int x, int y);
void					translate_nobj(t_data *data, int keycode);
void					translate_z(t_data *data, int button, int x, int y);
void					transform(t_data *data, int x, int y);
int						render_scene(void *arg);
int						project_ray(t_scene *scene, t_hit *hit, int x, int y);
void					rotate_obj(t_data *data, int x, int y);
void					rotate_camera(t_data *data, int x, int y);

// checkerboard

void					checkerman(t_hit *hit, t_obj *obj);
void					checkerboard_sp(t_hit *hit, t_sphere *sphere,
							int color);
void					checkerboard_pl(t_hit *hit, t_plane *plane, int color);
void					checkerboard_co(t_hit *hit, t_cone *cone, int color);
void					checkerboard_cy(t_hit *hit, t_cylinder *cyl, int color);
t_vec					get_orthogonal_vector(t_vec axis);
int						set_color(float u, float v, int color);
void					select_camera(t_data *data);
void					select_lights(t_data *data);
void					select_rotate_camera(t_data *data);
void					toggle_bump(t_data *data);
void					toggle_checker(t_data *data);

#endif
