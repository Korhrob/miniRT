/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:27:42 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:27:43 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

// vec3.xyz + vec3.xyz
t_vec3	vv_sum(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.x + b.x);
	o.y = (a.y + b.y);
	o.z = (a.z + b.z);
	return (o);
}

// vec3.xyz - vec3.xyz
t_vec3	vv_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.x - b.x);
	o.y = (a.y - b.y);
	o.z = (a.z - b.z);
	return (o);
}

// vec3.xyz * vec3.xyz
t_vec3	vv_mul(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.x * b.x);
	o.y = (a.y * b.y);
	o.z = (a.z * b.z);
	return (o);
}

// (vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z)
double	vv_dot(t_vec3 a, t_vec3 b)
{
	double	dot;

	dot = (a.x * b.x)
		+ (a.y * b.y)
		+ (a.z * b.z);
	return (dot);
}
