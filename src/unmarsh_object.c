
#include "../include/minirt.h"
#include <stdio.h>
#include <unistd.h>

static int	unmarshalsphere(char *str, t_scene *scene)
{
	char		**args;
	t_sphere	*self;
	int			err;

	err = 0;
	args = ft_split(str, ' ');
	self = ft_calloc(sizeof(t_sphere), 1);
	self->center = getcoords(args[1], &err);
	self->radius = ft_atof(args[2]);
	if (self->radius < 0.0)
		err = write(2, "Error: sphere diameter cannot be negative\n", 43);
	scene->objs[scene->objc].self = self; 
	scene->objs[scene->objc].hit = hitsphere; 
	scene->objs[scene->objc].color = getcolor(args[3], &err); 
	scene->objc++;
	free_matrix(args);
	return (err);
}
static int	unmarshalplane(char *str, t_scene *scene)
{
	char		**args;
	t_plane		*self;
	int			err;

	err = 0;
	args = ft_split(str, ' ');
	self = ft_calloc(sizeof(t_plane), 1);
	self->coord = getcoords(args[1], &err);
	self->normal = getcoords(args[2], &err);
	if (self->normal.y < -1.0 || self->normal.y > 1.0 
		|| self->normal.x < -1.0 || self->normal.x > 1.0
		|| self->normal.z < -1.0 || self->normal.z > 1.0)
		err = write(2, "Error: Normal is not normal :)\n", 32);
	scene->objs[scene->objc].self = self; 
	scene->objs[scene->objc].hit = hitplane; 
	scene->objs[scene->objc].color = getcolor(args[3], &err); 
	printf("plane color:%d\n", getcolor(args[3], &err));
	scene->objc++;
	free_matrix(args);
	return (err);
}
/*static int	unmarshalcylinder(char *str, t_scene *scene)*/
/*{*/
/*	return (0);*/
/*}*/
/*static int	unmarshalcone(char *str, t_scene *scene)*/
/*{*/
/*	return (0);*/
/*}*/

int	unmarshalobject(char *str, t_scene *scene)
{
	int	err;

	err = 0;
	if (!ft_strncmp(str, "sp ", 3))
		err = unmarshalsphere(str, scene);
	if (!ft_strncmp(str, "pl ", 3))
		err = unmarshalplane(str, scene);
	/*if (!ft_strncmp(str, "cy ", 3))*/
	/*	unmarshalcylinder(str, scene);*/
	/*if (!ft_strncmp(str, "cn ", 3))*/
	/*	unmarshalcone(str, scene);*/
	return (err);
}
