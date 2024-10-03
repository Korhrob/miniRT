/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:39:56 by avegis            #+#    #+#             */
/*   Updated: 2024/10/02 18:40:00 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	check_valid(t_parse *info)
{
	if (!info->original)
		return (0);
	info->line = info->original;
	while (*(info->line) == ' ')
		info->line++;
	if (*(info->line) == '\n')
	{
		free (info->original);
		return (0);
	}
	info->line[ft_strlen(info->line) - 1] = 0;
	return (1);
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

int	parse_type(char **arr, t_parse *info)
{
	int	error;

	error = 0;
	if (info->id == ID_AMBIENT)
		error = parse_ambient(arr, info);
	else if (info->id == ID_CAMERA)
		error = parse_camera(arr, info);
	else if (info->id == ID_LIGHT)
		error = parse_light(arr, info);
	else if (info->id == ID_SPHERE)
		error = parse_sphere(arr, info);
	else if (info->id == ID_PLANE)
		error = parse_plane(arr, info);
	else if (info->id == ID_CYLINDER)
		error = parse_cylinder(arr, info);
	else if (info->id == NONE)
		error = 1;
	return (error);
}

int	set_info(t_parse *info)
{
	char	**arr;
	int		error;

	error = 0;
	if (!info->original)
		return (1);
	arr = ft_split(info->original, ' ');
	if (!arr)
		error = 1;
	else
	{
		info->id = set_id(arr[0]);
		error = parse_type(arr, info);
		ft_free_arr(arr);
	}
	if (error == 1)
		free(info->original);
	return (error);
}
