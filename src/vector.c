/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:27:42 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:27:43 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	o;

	o.x = x;
	o.y = y;
	o.z = z;
	return (o);
}

t_vec3	vvec3(t_vec3 v)
{
	t_vec3	o;

	o.x = v.x;
	o.y = v.y;
	o.z = v.z;
	return (o);
}

// vec.xyz * t
t_vec3	v_mul(t_vec3 v, double t)
{
	t_vec3	o;

	o.x = (v.x * t);
	o.y = (v.y * t);
	o.z = (v.z * t);
	return (o);
}

// vec.xyz * (1/t)
t_vec3	v_div(t_vec3 v, double t)
{
	t_vec3	o;

	if (t == 0)
	{
		o.x = 0;
		o.y = 0;
		o.z = 0;
		return (o);
	}
	o.x = v.x * (1 / t);
	o.y = v.y * (1 / t);
	o.z = v.z * (1 / t);
	return (o);
}
