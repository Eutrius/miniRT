/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:51:13 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/29 12:51:43 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	decimal(const char *str, float *ret)
{
	int		i;
	float	decimalfac;

	i = 0;
	decimalfac = 1.0;
	while (ft_isdigit(str[i]))
	{
		decimalfac /= 10;
		*ret += (str[i] - '0') * decimalfac;
		i++;
	}
}

float	ft_atof(const char *str)
{
	int		i;
	int		sign;
	float	ret;

	i = 0;
	sign = 1;
	ret = 0.0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	decimal(str + i, &ret);
	return (ret * sign);
}
