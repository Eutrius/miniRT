/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:49 by lmoricon          #+#    #+#             */
/*   Updated: 2025/06/05 12:30:36 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_data(t_data *data, t_scene *scene)
{
	mlx_get_screen_size(data->mlx, &data->w, &data->h);
	data->w /= SCREEN_FRACTION;
	data->h /= SCREEN_FRACTION;
	set_camera_axis(scene);
	set_viewport(scene, scene->data->w, scene->data->h);
	data->obj_onhand = -1;
	data->nobj_onhand = -1;
	data->rot_cam = 0;
}

static void	init(int argc, char **argv, t_scene *scene, t_data *data)
{
	char	*filestr;
	int		err;

	ft_memset(scene, 0, sizeof(t_scene));
	scene->data = data;
	data->mlx = mlx_init();
	filestr = readfile(argc, argv);
	err = unmarshal(filestr, scene);
	free(filestr);
	if (err)
	{
		free_scene(scene);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	init_data(data, scene);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init(argc, argv, &data.scene, &data);
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "MiniRT");
	hooks(&data);
	render_scene(&data);
	mlx_loop(data.mlx);
}
