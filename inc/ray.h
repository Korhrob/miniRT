/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:58 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:34:59 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "color.h"
# include "shape.h"
# include "list.h"
# include "range.h"
# include "hit.h"
# include "scene.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_args
{
	t_ray	*ray;
	t_hit	*rec;
	t_scene	*scene;
	t_range	range;
	int		ignore_id;
}	t_args;

t_point	at(t_ray *ray, double t);
int		ray_hit(t_args *args);
t_color	ray_color(t_ray *ray, t_scene *scene);

#endif
