
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

int	hit_cylinder(t_ray *ray, t_range range, t_cylinder *this, t_hit *rec)
{
	//t_vec3	oc = vv_sub(ray->origin, this->shape.pos); // incorrect
	t_vec3	oc = vv_sub(this->shape.pos, ray->origin); // correct

    double a = v_len_squared(ray->dir) - pow(vv_dot(ray->dir, this->w), 2);
    double h = vv_dot(ray->dir, oc) - vv_dot(ray->dir, this->w) * vv_dot(oc, this->w); 
    double c = vv_dot(oc, oc) - pow(vv_dot(oc, this->w), 2) - (this->radius * this->radius);
	double	discriminant = (h * h) - (a * c);
	if (discriminant < 0)
		return (FALSE);


	double	sqrtd = sqrt(discriminant);
	double	root = (h - sqrtd) / a;
	if (!in_range_equal(range, root))
	{
		root = (h + sqrtd) / a;
		if (!in_range_equal(range, root))
			return (FALSE);
	}

	rec->t = root;
	rec->point = at(ray, rec->t);

	double	y = vv_dot(rec->point, this->w) - vv_dot(this->shape.pos, this->w);

	if (y < -(this->length / 2.0) || y > (this->length / 2.0))
		return (FALSE);

	// t_vec3	n = vv_sub(oc, v_mul(this->w, vv_dot(oc, this->w)));
	// rec->normal = unit_vector(n);

	t_vec3	projection = v_mul(this->w, vv_dot(vv_sub(rec->point, this->shape.pos), this->w));
	t_vec3	normal_vec = vv_sub(vv_sub(rec->point, this->shape.pos), projection);

	rec->normal = unit_vector(normal_vec);
	rec->front = vv_dot(ray->dir, rec->normal) < 0;
	if (!rec->front)
		rec->normal = v_mul(rec->normal, -1);

	return (TRUE);
}

// caps are treated as planes, but discarded if they dont fall within the radius
int hit_cylinder_cap(t_ray *ray, t_range range, t_plane *this, t_hit *rec)
{
	if (hit_plane(ray, range, this, rec))
	{
		t_vec3	vtp = vv_sub(rec->point, this->shape.pos);
		if (vv_dot(vtp, vtp) <= (this->radius * this->radius))
			return (TRUE);
	}
	return (FALSE);
}

t_cylinder	*new_cylinder(t_point pos, double radius, double length, t_vec3 orientation, t_color color)
{
	t_cylinder *cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->shape.pos = vvec3(pos);
	cylinder->orientation = vvec3(orientation);
	cylinder->radius = radius;
	cylinder->length = length;
	cylinder->shape.color = vvec3(color);
	cylinder->hit = hit_cylinder;

	cylinder->u = unit_vector(get_perpendicular(orientation));
	cylinder->v = unit_vector(cross(orientation, cylinder->u));
	cylinder->w = cross(cylinder->u, cylinder->v);

	t_vec3 offset = v_mul(unit_vector(orientation), length / 2.0);
	cylinder->top = new_plane(vv_sum(pos, offset), v_mul(vec3(radius, radius, radius), 2), orientation, color);
	cylinder->top->radius = radius;
	cylinder->top->hit = hit_cylinder_cap;
	cylinder->bot = new_plane(vv_sub(pos, offset), v_mul(vec3(radius, radius, radius), 2), orientation, color);
	cylinder->bot->radius = radius;
	cylinder->bot->hit = hit_cylinder_cap;

	if (!cylinder->top || !cylinder->bot)
	{
		if (cylinder->top)
			free(cylinder->top);
		if (cylinder->bot)
			free(cylinder->bot);
		free(cylinder);
		return (NULL);
	}

	return (cylinder);
}