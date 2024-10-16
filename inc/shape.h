/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:12 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:34:13 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include <math.h>
# include "minirt.h"
# include "vector.h"
# include "ray.h"
# include "color.h"

typedef struct s_shape
{
	t_point			pos;
	t_color			color;
	int				id;
}	t_shape;

t_vec3	get_perpendicular(t_vec3 vec);

#endif
