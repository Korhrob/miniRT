/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:25:02 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:25:04 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "light.h"
#include "vector.h"
#include "color.h"
#include "hit.h"
#include "ray.h"
#include "utils.h"

static t_color	calc_ambient(t_hit *rec, t_scene *scene)
{
	t_color	ambient;

	ambient = vv_mul(rec->color, scene->ambient.color);
	ambient = vv_sum(ambient, scene->ambient.color);
	ambient = v_mul(ambient, scene->ambient.strength);
	ambient = v_clamp(ambient);
	return (ambient);
}

static t_color	calc_diffuse(t_hit *rec, t_scene *scene)
{
	t_color	diffuse;
	t_vec3	dir;
	double	i;

	dir = unit_vector(vv_sub(scene->light.pos, rec->point));
	i = max(0, vv_dot(rec->normal, dir)) * scene->light.strength;
	diffuse = v_mul(rec->color, i);
	return (diffuse);
}

static t_color	calc_shadow(t_hit *rec, t_scene *scene,
		t_color ambient, t_color diffuse)
{
	t_ray	s_ray;
	t_args	args;
	double	l_dist;

	l_dist = v_len(vv_sub(rec->point, scene->light.pos));
	args.range = new_range(0, l_dist);
	args.ignore_id = rec->shape_id;
	args.scene = scene;
	args.rec = rec;
	s_ray.origin = rec->point;
	s_ray.dir = unit_vector(vv_sub(scene->light.pos, rec->point));
	args.ray = &s_ray;
	if (ray_hit(&args))
		return (ambient);
	return (diffuse);
}

t_color	calc_light(t_hit *rec, t_scene *scene)
{
	t_color	color;
	t_color	ambient;
	t_color	diffuse;

	ambient = calc_ambient(rec, scene);
	diffuse = calc_diffuse(rec, scene);
	diffuse = vv_sum(ambient, diffuse);
	diffuse = v_clamp(diffuse);
	color = calc_shadow(rec, scene, ambient, diffuse);
	return (color);
}
