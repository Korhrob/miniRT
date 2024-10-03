/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:52 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:34:52 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "shape.h"
# include "vector.h"
# include "ray.h"
# include "hit.h"
# include "color.h"

typedef struct s_pl_calc
{
	t_vec3	normal;
	t_vec3	oc;
	t_vec3	vtp;
	t_point	p;
	double	denom;
	double	t;
	double	u;
	double	v;
}	t_pl_calc;

typedef struct s_plane	t_plane;

struct s_plane
{
	t_shape	shape;
	t_vec3	size;
	t_vec3	orientation;
	t_vec3	u;
	t_vec3	v;
	double	radius;
	int		(*hit)(t_ray *ray, t_range range, t_plane *this, t_hit *rec);
};

int		hit_plane(t_ray *ray, t_range range, t_plane *this, t_hit *rec);
t_plane	*new_plane(t_point pos, t_vec3 size, t_vec3 orientation, t_color color);

#endif
