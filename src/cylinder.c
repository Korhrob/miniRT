/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:24:34 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:24:35 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "vector.h"
#include "ray.h"
#include "shape.h"
#include "range.h"
#include "hit.h"
#include "color.h"
#include "cylinder.h"

static void	calc_cylinder(t_ray *ray, t_cylinder *this, t_cl_calc *calc)
{
	calc->oc = vv_sub(this->shape.pos, ray->origin);
	calc->a = v_len_squared(ray->dir) - pow(vv_dot(ray->dir, this->w), 2);
	calc->h = vv_dot(ray->dir, calc->oc)
		- vv_dot(ray->dir, this->w)
		* vv_dot(calc->oc, this->w);
	calc->c = vv_dot(calc->oc, calc->oc)
		- pow(vv_dot(calc->oc, this->w), 2)
		- (this->radius * this->radius);
	calc->discriminant = (calc->h * calc->h) - (calc->a * calc->c);
}

static void	record(t_ray *ray, t_hit *rec, t_cylinder *this)
{
	t_vec3	projection;
	t_vec3	normal_vec;

	projection = v_mul(this->w,
			vv_dot(vv_sub(rec->point, this->shape.pos), this->w));
	normal_vec = vv_sub(vv_sub(rec->point, this->shape.pos), projection);
	rec->normal = unit_vector(normal_vec);
	rec->front = vv_dot(ray->dir, rec->normal) < 0;
	if (!rec->front)
		rec->normal = v_mul(rec->normal, -1);
	rec->color = this->shape.color;
	rec->shape_id = this->shape.id;
}

int	hit_cylinder(t_ray *ray, t_range range, t_cylinder *this, t_hit *rec)
{
	t_cl_calc	calc;
	double		y;

	calc = (t_cl_calc){0};
	calc_cylinder(ray, this, &calc);
	if (calc.discriminant < 0)
		return (FALSE);
	calc.discriminant = sqrt(calc.discriminant);
	calc.root = (calc.h - calc.discriminant) / calc.a;
	if (!in_range_equal(range, calc.root))
	{
		calc.root = (calc.h + calc.discriminant) / calc.a;
		if (!in_range_equal(range, calc.root))
			return (FALSE);
	}
	rec->t = calc.root;
	rec->point = at(ray, rec->t);
	y = vv_dot(rec->point, this->w) - vv_dot(this->shape.pos, this->w);
	if (y < -(this->length / 2.0) || y > (this->length / 2.0))
		return (FALSE);
	record(ray, rec, this);
	return (TRUE);
}

// caps are treated as planes, but discarded if they dont fall within the radius
int	hit_cylinder_cap(t_ray *ray, t_range range, t_plane *this, t_hit *rec)
{
	t_vec3	vtp;

	if (hit_plane(ray, range, this, rec))
	{
		vtp = vv_sub(rec->point, this->shape.pos);
		if (vv_dot(vtp, vtp) <= (this->radius * this->radius))
			return (TRUE);
	}
	return (FALSE);
}

// size.x = radius, size.y = length
t_cylinder	*new_cylinder(t_point pos, t_vec3 size,
	t_vec3 orientation, t_color color)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->shape.pos = vvec3(pos);
	cylinder->shape.color = vvec3(color);
	cylinder->orientation = vvec3(orientation);
	cylinder->radius = size.x / 2;
	cylinder->length = size.y;
	cylinder->hit = hit_cylinder;
	cylinder->u = unit_vector(get_perpendicular(orientation));
	cylinder->v = unit_vector(cross(orientation, cylinder->u));
	cylinder->w = cross(cylinder->u, cylinder->v);
	add_caps(cylinder);
	if (!cylinder->top || !cylinder->bot)
	{
		free_cylinder(cylinder);
		return (NULL);
	}
	return (cylinder);
}
