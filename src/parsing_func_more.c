/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:47:29 by avegis            #+#    #+#             */
/*   Updated: 2024/10/02 18:47:30 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../libft/libft.h"
#include <stdio.h>

int	parse_light(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos, 1) == 1)
		return (1);
	if (!ft_isdouble_str(arr[2]))
		return (1);
	info->v1 = ft_strtod(arr[2]);
	if (info->v1 < 0 || info->v1 > 1)
		return (1);
	if (create_vector(arr[3], &info->color, 255) == 1)
		return (1);
	if (check_range(&info->color, 0, 1))
		return (1);
	if (arr[4])
		return (1);
	return (0);
}

int	parse_sphere(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos, 1) == 1)
		return (1);
	if (!ft_isdouble_str(arr[2]))
		return (1);
	info->v1 = ft_strtod(arr[2]);
	if (create_vector(arr[3], &info->color, 255) == 1)
		return (1);
	if (check_range(&info->color, 0, 1))
		return (1);
	if (arr[4])
		return (1);
	return (0);
}

int	parse_plane(char **arr, t_parse *info)
{
	if (create_vector(arr[1], &info->pos, 1) == 1)
		return (1);
	if (create_vector(arr[2], &info->orien, 1) == 1)
		return (1);
	if (check_range(&info->orien, -1, 1))
		return (1);
	if (create_vector(arr[3], &info->color, 255) == 1)
		return (1);
	if (check_range(&info->color, 0, 1))
		return (1);
	if (arr[4])
		return (1);
	return (0);
}

int	parse_cylinder(char **arr, t_parse *info)
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
	if (!ft_isdouble_str(arr[4]))
		return (1);
	info->v2 = ft_strtod(arr[4]);
	if (create_vector(arr[5], &info->color, 255) == 1)
		return (1);
	if (check_range(&info->color, 0, 1))
		return (1);
	if (arr[6])
		return (1);
	return (0);
}
