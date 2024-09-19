#include "parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int create_vector(char *str, t_vec3 *out)
{
	char	**d_arr;

	d_arr = ft_split(str, ',');
	if (!d_arr)
		return (1);
	out->x = ft_strtod(d_arr[0]);
	out->y = ft_strtod(d_arr[1]);
	out->z = ft_strtod(d_arr[2]);
	ft_free_arr(d_arr);
	return (0);
}

int	parse_ambient(char **arr, t_parse *info)
{
	info->v1 = ft_strtod(arr[1]);
	if (create_vector(arr[2], &info->color) == 1)
		return (1);
	if (arr[3])
		return (1);
	return (0);
}

int	parse_camera(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos) == 1)
		return (1);
	if (create_vector(arr[2], &info->orien) == 1)
		return (1);
	info->v1 = ft_strtod(arr[3]);
	if (arr[4])
		return (1);
	return (0);
}

int	parse_light(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos) == 1)
		return (1);
	info->v1 = ft_strtod(arr[2]);
	if (create_vector(arr[3], &info->color) == 1)
		return (1);
	if (arr[4])
		return (1);
	return (0);
}

int	parse_sphere(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos) == 1)
		return (1);
	info->v1 = ft_strtod(arr[2]);
	if (create_vector(arr[3], &info->color) == 1)
		return (1);
	if (arr[4])
		return (1);
	return (0);
}

int	parse_plane(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos) == 1)
		return (1);
	if (create_vector(arr[2], &info->orien) == 1)
		return (1);
	if (create_vector(arr[3], &info->color) == 1)
		return (1);
	if (arr[4])
		return (1);
	return (0);
}

int	parse_cylinder(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos) == 1)
		return (1);
	if (create_vector(arr[2], &info->orien) == 1)
		return (1);
	info->v1 = ft_strtod(arr[3]);
	info->v2 = ft_strtod(arr[4]);
	if (create_vector(arr[5], &info->color) == 1)
		return (1);
	if (arr[6])
		return (1);
	return (0);
}
