/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:49 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/29 12:52:26 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		exit(1);
	}
	mlx_get_screen_size(data->mlx, &data->w, &data->h);
	data->w /= 2;
	data->h /= 2;
	set_camera_axis(scene);
	set_viewport(scene, scene->data->w, scene->data->h);
	data->obj_onhand = -1;
	data->nobj_onhand = -1;
	data->rot_cam = 0;
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

int	clamp(int val)
{
	if (val < 0)
		val = 0;
	if (val > 255)
		val = 255;
	return (val);
}

int	colormult(int color, float multiplier)
{
	int	rgba[3];
	int	ret[3];

	rgba[0] = (color >> 16) & 0xff;
	rgba[1] = (color >> 8) & 0xff;
	rgba[2] = color & 0xff;
	ret[0] = clamp((int)(rgba[0] * multiplier));
	ret[1] = clamp((int)(rgba[1] * multiplier));
	ret[2] = clamp((int)(rgba[2] * multiplier));
	return ((ret[0] << 16) | (ret[1] << 8) | ret[2]);
}

int	coloradd(int colora, int colorb)
{
	int	rgba[3];
	int	rgbb[3];
	int	ret[3];

	rgba[0] = (colora >> 16) & 0xff;
	rgba[1] = (colora >> 8) & 0xff;
	rgba[2] = colora & 0xff;
	rgbb[0] = (colorb >> 16) & 0xff;
	rgbb[1] = (colorb >> 8) & 0xff;
	rgbb[2] = colorb & 0xff;
	ret[0] = clamp(rgba[0] + rgbb[0]);
	ret[1] = clamp(rgba[1] + rgbb[1]);
	ret[2] = clamp(rgba[2] + rgbb[2]);
	return ((ret[0] << 16) | (ret[1] << 8) | ret[2]);
}
