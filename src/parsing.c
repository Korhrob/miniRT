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

int	set_id(char *str)
{
	if (!ft_strcmp(str, "A"))
		return (ID_AMBIENT);
	else if (!ft_strcmp(str, "C"))
		return (ID_CAMERA);
	else if (!ft_strcmp(str, "L"))
		return (ID_LIGHT);
	else if (!ft_strcmp(str, "sp"))
		return (ID_SPHERE);
	else if (!ft_strcmp(str, "pl"))
		return (ID_PLANE);
	else if (!ft_strcmp(str, "cy"))
		return (ID_CYLINDER);
	return (NONE);
}

void	set_info(char *line, t_parse *info)
{
	char	**arr;

	if (!line)
		return ;
	arr = ft_split(line, ' ');
	// printf("arr0 %s\narr1 %s\narr2 %s\narr3 %s\narr4 %s\n", arr[0], arr[1], arr[2], arr[3], arr[4]);
	info->id = set_id(arr[0]);
	if (info->id == ID_AMBIENT)
		parse_ambient(arr, info);
	else if (info->id == ID_CAMERA)
		parse_camera(arr, info);
	else if (info->id == ID_LIGHT)
		parse_light(arr, info);
	else if (info->id == ID_SPHERE)
		parse_sphere(arr, info);
	else if (info->id == ID_PLANE)
		parse_plane(arr, info);
	else if (info->id == ID_CYLINDER)
		parse_cylinder(arr, info);
	ft_free_arr(arr);
}
