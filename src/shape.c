/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:25:52 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:25:52 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "shape.h"
#include "vector.h"
#include "ray.h"

t_vec3	get_perpendicular(t_vec3 vec)
{
	if (fabs(vec.x) > fabs(vec.y) && fabs(vec.x) > fabs(vec.z))
		return (cross(vec, vec3(0, 1, 0)));
	return (cross(vec, vec3(1, 0, 0)));
}
