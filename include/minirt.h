#ifndef MINIRT_H
 #define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include <fcntl.h>
#include <math.h>

typedef struct	s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_ambient
{
	float	ratio;
	int		color;
}	t_amb;

typedef struct	s_camera
{
	t_vec	pos;
	t_vec	ori;
	float	fov;
} t_cam;

typedef struct s_light
{
	t_vec	pos;
	float	ratio;
	int		color;
}	t_light;


typedef struct s_hit
{
	t_vec	normal;
	int		color;
	float	t;
}	t_hit;

typedef struct s_ray
{
	t_vec	start;
	t_vec	dir;
}	t_ray;

typedef struct s_object
{
	void	*self;
	int		color;
  	char 	(*hit)(t_ray ray, t_hit *hit, void *self);
}	t_obj;

typedef struct s_sphere
{
	t_vec	center;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec coord;
	t_vec normal;
}	t_plane;


typedef struct s_cylinder
{
	t_vec 	center;
	float	radius;
	float	maxm;
	t_vec	axis;
}	t_cylinder;



typedef struct s_scene
{
	t_obj	*objs;
	int		objc;
	t_light	light;
	t_amb	amb;
	t_cam	cam;

}	t_scene;

typedef struct	s_mlximg {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;


/*rendering*/

void	pixel(t_img *data, int x, int y, int color);
void	*render(t_scene scene, int w, int h, void *mlx);

/*RAYTRACING*/
char	hitsphere(t_ray ray, t_hit *hit, void *self);
char	hitcylinder(t_ray ray, t_hit *hit, void *self);
char	hitcone(t_ray ray, t_hit *hit, void *self);
char	hitplane(t_ray ray, t_hit *hit, void *self);

/*unmarshal*/
char	*readfile(int argc, char **argv);
int		unmarshal(char *str, t_scene *scene);
int		unmarshalobject(char *str, t_scene *scene);
int		getcolor(char *str, int *err);
t_vec getcoords(char *str, int *err);

//utils
char	is_float(char *str);
t_vec vecsum(t_vec a, t_vec b);
t_ray ray(t_vec start, t_vec dir);
t_vec vecsub(t_vec a, t_vec b);
float	dot(t_vec a, t_vec b);
t_vec vector(float x, float y, float z);
t_vec scalarprod(t_vec a, float b);
t_vec normalize(t_vec v);

//memory
void	free_matrix(char **mat);

//debug
void print_vec(const t_vec *vec);
void print_ambient(const t_amb *amb);
void print_camera(const t_cam *cam);
void print_light(const t_light *light);
void print_hit(const t_hit *hit);
void print_ray(const t_ray *ray);
void print_object(const t_obj *obj);
void print_sphere(const t_sphere *sphere);
void print_plane(const t_plane *plane);
void print_cylinder(const t_cylinder *cylinder);
void print_scene(const t_scene *scene);

#endif
