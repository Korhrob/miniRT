/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:25:27 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:25:30 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "range.h"

t_range	new_range(double min, double max)
{
	t_range	range;

	range.min = min;
	range.max = max;
	return (range);
}

double	range_size(t_range range)
{
	return (range.max - range.min);
}

// x >= min && x <= max
int	in_range_equal(t_range range, double x)
{
	return (x >= range.min && x <= range.max);
}

// x > min && x < max
int	in_range(t_range range, double x)
{
	return (x > range.min && x < range.max);
}
