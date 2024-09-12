
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
    calc->h = vv_dot(ray->dir, calc->oc) - vv_dot(ray->dir, this->w) * vv_dot(calc->oc, this->w); 
    calc->c = vv_dot(calc->oc, calc->oc) - pow(vv_dot(calc->oc, this->w), 2) - (this->radius * this->radius);
	calc->discriminant = (calc->h * calc->h) - (calc->a * calc->c);
}

static void	record(t_ray *ray, t_hit *rec, t_cylinder *this, t_cl_calc *calc)
{
	t_vec3	projection;
	t_vec3	normal_vec;

	projection = v_mul(this->w, vv_dot(vv_sub(rec->point, this->shape.pos), this->w));
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

	calc = (t_cl_calc){ 0 };
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
	record(ray, rec, this, &calc);
	return (TRUE);
}

// caps are treated as planes, but discarded if they dont fall within the radius
int hit_cylinder_cap(t_ray *ray, t_range range, t_plane *this, t_hit *rec)
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
	cylinder->bot = new_plane(vv_sub(pos, offset), v_mul(vec3(radius, radius, radius), 2), v_mul(orientation, -1), color);
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
