#include "libft.h"

static void	check_sign(const char *str, int *sign, int *i)
{
	*sign = 1;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
}

#include <stdio.h>

double	ft_strtod(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		i;

	i = 0;
	result = 0.0;
	fraction = 1.0;
	check_sign(str, &sign, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			fraction /= 10.0;
			result += (str[i] - '0') * fraction;
			i++;
		}
	}
	return (result * sign);
}
