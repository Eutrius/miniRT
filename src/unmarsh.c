#include "../include/minirt.h"


static int	unmarshalcamera(char *str, t_scene *scene)
{
	static char	present;
	if (present != 0)
		return (1);
	return (0);
}

static int	unmarshallight(char *str, t_scene *scene)
{
	static char	present;
	if (present != 0)
		return (1);
	return (0);
}


static int	unmarshalambient(char *str, t_scene *scene)
{
	static char	present;
	if (present != 0)
		return (1);
	return (0);
}

int	unmarshal(char *file, t_scene *scene)
{
	char	**spl;
	char	*str;
	int		i;
	int		err;

	spl = ft_split(file, '\n');
	err = 0;
	while (spl[i]) 
		i++;
	scene->objs = malloc(sizeof(t_obj) * i - 3);
	while (--i >= 0 && err == 0)
	{
		str = spl[i];
		if (ft_strchr(str, 'A'))
			err = unmarshalambient(str, scene);
		else if (ft_strchr(str, 'L'))
			err = unmarshallight(str, scene);
		else if (ft_strchr(str, 'C'))
			err = unmarshalcamera(str, scene);
		else
		 	err = unmarshalobject(str, scene);
	}
	return (err);
}

