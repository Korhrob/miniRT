/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:42:46 by avegis            #+#    #+#             */
/*   Updated: 2024/10/02 18:42:48 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	check_range(t_vec3 *vector, double min, double max)
{
	if (vector->x < min || vector->x > max)
		return (1);
	if (vector->y < min || vector->y > max)
		return (1);
	if (vector->z < min || vector->z > max)
		return (1);
	return (0);
}

int	create_vector(char *str, t_vec3 *out, double multi)
{
	char	**d_arr;
	int		error;

	error = 0;
	d_arr = ft_split(str, ',');
	if (!d_arr)
		return (1);
	if (!ft_isdouble_str(d_arr[0]))
		error = 1;
	if (!ft_isdouble_str(d_arr[1]))
		error = 1;
	if (!ft_isdouble_str(d_arr[2]))
		error = 1;
	out->x = ft_strtod(d_arr[0]) / multi;
	out->y = ft_strtod(d_arr[1]) / multi;
	out->z = ft_strtod(d_arr[2]) / multi;
	ft_free_arr(d_arr);
	if (error == 1)
		return (1);
	return (0);
}

int	parse_ambient(char **arr, t_parse *info)
{
	if (!ft_isdouble_str(arr[1]))
		return (1);
	info->v1 = ft_strtod(arr[1]);
	if (info->v1 < 0 || info->v1 > 1)
		return (1);
	if (create_vector(arr[2], &info->color, 255) == 1)
		return (1);
	if (check_range(&info->color, 0, 1))
		return (1);
	if (arr[3])
		return (1);
	return (0);
}

int	parse_camera(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos, 1) == 1)
		return (1);
	if (create_vector(arr[2], &info->orien, 1) == 1)
		return (1);
	if (check_range(&info->orien, -1, 1))
		return (1);
	if (!ft_isdouble_str(arr[3]))
		return (1);
	info->v1 = ft_strtod(arr[3]);
	if (info->v1 < 0 || info->v1 > 180)
		return (1);
	if (arr[4])
		return (1);
	return (0);
}
