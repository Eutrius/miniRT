
#include "../include/minirt.h"


static int	unmarshalsphere(char *str, t_scene *scene)
{
	return (0);
}
static int	unmarshalplane(char *str, t_scene *scene)
{
	return (0);
}
static int	unmarshalcylinder(char *str, t_scene *scene)
{
	return (0);
}
static int	unmarshalcone(char *str, t_scene *scene)
{
	return (0);
}

int	unmarshalobject(char *str, t_scene *scene)
{
	if (!ft_strncmp(str, "sp ", 3))
		unmarshalsphere(str, scene);
	if (!ft_strncmp(str, "pl ", 3))
		unmarshalplane(str, scene);
	if (!ft_strncmp(str, "cy ", 3))
		unmarshalcylinder(str, scene);
	if (!ft_strncmp(str, "cn ", 3))
		unmarshalcone(str, scene);
	return (0);
}
