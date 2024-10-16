/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:33:58 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:33:59 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANGE_H
# define RANGE_H

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

t_range	new_range(double min, double max);
double	range_size(t_range range);
int		in_range_equal(t_range range, double x);
int		in_range(t_range range, double x);

#endif
