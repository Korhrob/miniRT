#include "parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	check_valid(char *line)
{
	if (!line)
		return (1);
	while (*line == ' ')
		line++;
	if (*line == '\n')
		return (1);
	printf("Identifier = [%c%c]", *line, *(line+1));
	return (0);
}

int	count_form(char *str)
{
	int i;

	i = 0;
	while (str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

int	set_id(char *str)
{
	if (ft_strcmp(str, "A"))
		return (AMBIENT);
	else if (ft_strcmp(str, "C"))
		return (CAMERA);
	else if (ft_strcmp(str, "L"))
		return (LIGHT);
	else if (ft_strcmp(str, "sp"))
		return (SPHERE);
	else if (ft_strcmp(str, "pl"))
		return (PLANE);
	else if (ft_strcmp(str, "cy"))
		return (CYLINDER);
	return (NONE);
}

void	set_info(char *line, t_parse *info)
{
	char	**arr;
	char	**n_arr;
	int		i;

	if (!line)
		return ;
	i = 0;
	arr = ft_split(line, ' ');
	info->id = set_id(arr[i]);
	i++;
	n_arr = ft_split(arr[i], ',');
	info->pos = vec3(ft_atoi(n_arr[0]), ft_atoi(n_arr[1]), ft_atoi(n_arr[2]));
	i++;
	n_arr = ft_split(arr[i], ',');
	info->pos = vec3(ft_atoi(n_arr[0]), ft_atoi(n_arr[1]), ft_atoi(n_arr[2]));
}
