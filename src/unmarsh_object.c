#include "minirt.h"
#include <stdio.h>
#include <unistd.h>

static int	unmarshalsphere(char *str, t_scene *scene)
{
	char		**args;
	t_sphere	*self;
	int			err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		self = ft_calloc(sizeof(t_sphere), 1);
		self->center = getcoords(args[1], &err);
		self->radius = ft_atof(args[2]);
		if (self->radius < 0.0)
			err = write(2, "Error: sphere diameter cannot be negative\n", 43);
		scene->objs[scene->objc - 1].self = self;
		scene->objs[scene->objc - 1].type = SPHERE;
		scene->objs[scene->objc - 1].hit = hitsphere;
		scene->objs[scene->objc - 1].color = getcolor(args[3], &err);
		scene->objc--;
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}
static int	unmarshalplane(char *str, t_scene *scene)
{
	char	**args;
	t_plane	*self;
	int		err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		self = ft_calloc(sizeof(t_plane), 1);
		self->center = getcoords(args[1], &err);
		self->axis = getcoords(args[2], &err);
		if (self->axis.y < -1.0 || self->axis.y > 1.0 || self->axis.x <
			-1.0 || self->axis.x > 1.0 || self->axis.z < -1.0
			|| self->axis.z > 1.0)
			err = write(2, "Error: Normal is not normal :)\n", 32);
		scene->objs[scene->objc - 1].self = self;
		scene->objs[scene->objc - 1].type = PLANE;
		scene->objs[scene->objc - 1].hit = hitplane;
		scene->objs[scene->objc - 1].color = getcolor(args[3], &err);
		scene->objc--;
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

static int	unmarshalcylinder(char *str, t_scene *scene)
{
	char		**args;
	t_cylinder	*self;
	int			err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3] && args[4] && args[5])
	{
		self = ft_calloc(sizeof(t_cylinder), 1);
		self->center = getcoords(args[1], &err);
		self->axis = getcoords(args[2], &err);
		if (self->axis.x < -1.0 || self->axis.x > 1.0 || self->axis.y < -1.0
			|| self->axis.y > 1.0 || self->axis.z < -1.0 || self->axis.z > 1.0)
			err = write(2, "Error: Normal is not normal :)\n", 32);
		self->axis = normalize(self->axis);
		self->radius = ft_atof(args[3]) / 2;
		self->height = ft_atof(args[4]);
		if (self->radius < 0.0)
			err = write(2, "Error: cylinder diameter cannot be negative\n", 44);
		self->radius = ft_atof(args[3]) / 2;
		scene->objs[scene->objc - 1].self = self;
		scene->objs[scene->objc - 1].type = CYLINDER;
		scene->objs[scene->objc - 1].hit = hitcylinder;
		scene->objs[scene->objc - 1].color = getcolor(args[5], &err);
		scene->objc--;
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

static int	unmarshalcone(char *str, t_scene *scene)
{
	char	**args;
	t_cone	*self;
	int		err;

	err = 0;
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3] && args[4])
	{
		self = ft_calloc(sizeof(t_cone), 1);
		self->center = getcoords(args[1], &err);
		self->axis = getcoords(args[2], &err);
		if (self->axis.x < -1.0 || self->axis.x > 1.0 || self->axis.y < -1.0
			|| self->axis.y > 1.0 || self->axis.z < -1.0 || self->axis.z > 1.0)
			err = write(2, "Error: Normal is not normal :)\n", 32);
		self->axis = normalize(self->axis);
		self->angle = ft_atof(args[3]);
		if (self->angle < 0.0)
			err = write(2, "Error: cone angle cannot be negative\n", 38);
		scene->objs[scene->objc - 1].self = self;
		scene->objs[scene->objc - 1].type = CONE;
		scene->objs[scene->objc - 1].hit = hitcone;
		scene->objs[scene->objc - 1].color = getcolor(args[4], &err);
		scene->objc--;
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

int	unmarshalobject(char *str, t_scene *scene)
{
	int	err;

	err = 0;
	if (!ft_strncmp(str, "sp ", 3))
		err = unmarshalsphere(str, scene);
	if (!ft_strncmp(str, "pl ", 3))
		err = unmarshalplane(str, scene);
	if (!ft_strncmp(str, "cy ", 3))
		err = unmarshalcylinder(str, scene);
	if (!ft_strncmp(str, "co ", 3))
		err = unmarshalcone(str, scene);
	return (err);
}
