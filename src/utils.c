/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:26:06 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:26:07 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

t_vec3	v_clamp(t_vec3 v)
{
	t_vec3	o;

	o.x = v.x;
	o.y = v.y;
	o.z = v.z;
	if (o.x > 1)
		o.x = 1;
	if (o.y > 1)
		o.y = 1;
	if (o.z > 1)
		o.z = 1;
	if (o.x < 0)
		o.x = 0;
	if (o.y < 0)
		o.y = 0;
	if (o.z < 0)
		o.z = 0;
	return (o);
}
