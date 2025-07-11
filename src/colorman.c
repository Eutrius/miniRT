/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:24:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/06/05 12:24:53 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
