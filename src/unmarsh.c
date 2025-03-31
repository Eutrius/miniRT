#include "../include/minirt.h"
#include <unistd.h>

static int	unmarshalcamera(char *str, t_scene *scene)
{
	static char	present;
	char		**args;
	int			err;

	err = 0;
	if (present != 0)
		return (write(2, "Error: Too many cameras\n", 25));
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		scene->cam.pos = getcoords(args[1], &err);
		scene->cam.ori = getcoords(args[2], &err);
		if (scene->cam.ori.x < -1.0 || scene->cam.ori.x > 1.0
			|| scene->cam.ori.y < -1.0 || scene->cam.ori.y > 1.0
			|| scene->cam.ori.z < -1.0 || scene->cam.ori.z > 1.0)
			err = write(2,
					"Error: Wrong camera orientation [-1,1][-1,1][-1,1]\n", 51);
		if (!is_float(args[3]))
			err = (write(2, "Error: Fov not a number ([0.0,180.0])\n", 39));
		scene->cam.fov = ft_atof(args[3]);
		if (scene->cam.fov < 0.0 || scene->cam.fov > 180.0)
			err = (write(2, "Error: Wrong FOV, ([0.0,180.0])\n", 33));
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	set_camera_axis(scene);
	set_viewport(scene, scene->data->w, scene->data->h);
	free_matrix(args);
	return (err);
}

static int	unmarshallight(char *str, t_scene *scene)
{
	static char	present;
	char		**args;
	int			err;

	err = 0;
	if (present != 0)
		return (write(2, "Error: Too many lights\n", 24));
	args = ft_split(str, ' ');
	if (args && args[1] && args[2] && args[3])
	{
		scene->light.pos = getcoords(args[1], &err);
		if (!is_float(args[2]))
			err = (write(2, "Light Ratio not a number ([0.0,1.0])\n", 38));
		scene->light.ratio = ft_atof(args[2]);
		if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
			err = (write(2, "Wrong Light Ratio, ([0.0,1.0])\n", 32));
		scene->light.color = getcolor(args[3], &err);
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

static int	unmarshalambient(char *str, t_scene *scene)
{
	static char	present;
	char		**args;
	int			err;

	err = 0;
	if (present != 0)
		return (write(2, "Error: Too many Ambient lights\n", 32));
	args = ft_split(str, ' ');
	if (args && args[1] && args[2])
	{
		if (!is_float(args[1]))
			err = (write(2, "Ambient Ratio not a number ([0.0,1.0])\n", 40));
		scene->amb.ratio = ft_atof(args[1]);
		if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
			err = (write(2, "Wrong Ambient Ratio, ([0.0,1.0])\n", 31));
		scene->amb.color = getcolor(args[2], &err);
	}
	else
		err = write(2, "Error: Wrong Arguments\n", 24);
	free_matrix(args);
	return (err);
}

int	unmarshal(char *file, t_scene *scene)
{
	char	**spl;
	char	*str;
	int		i;
	int		err;

	err = 0;
	i = 0;
	spl = ft_split(file, '\n');
	while (spl[i])
		i++;
	scene->objs = malloc(sizeof(t_obj) * (i - 2));
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
