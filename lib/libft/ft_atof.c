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

float ft_atof(const char *str)
{
    int i = 0;
    int sign = 1;
    float ret = 0.0;

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
