/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:27:42 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:27:43 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	v_len(t_vec3 v)
{
	return (sqrt(v_len_squared(v)));
}

double	v_len_squared(t_vec3 v)
{
	double	len_squared;

	len_squared = (v.x * v.x)
		+ (v.y * v.y)
		+ (v.z * v.z);
	return (len_squared);
}

//	vec3.xyz / vec3 len
t_vec3	unit_vector(t_vec3 v)
{
	t_vec3	o;

	o = v_div(v, v_len(v));
	return (o);
}

t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.y * b.z - a.z * b.y);
	o.y = (a.z * b.x - a.x * b.z);
	o.z = (a.x * b.y - a.y * b.x);
	return (o);
}

