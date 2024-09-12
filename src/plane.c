
#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "vector.h"
#include "shape.h"
#include "plane.h"
#include "color.h"

static void calc_plane(t_ray *ray, t_plane *this, t_pl_calc *calc)
{
	calc->normal = unit_vector(this->orientation);
	calc->denom = vv_dot(calc->normal, ray->dir);
	calc->oc = vv_sub(this->shape.pos, ray->origin);
	calc->t = vv_dot(calc->oc, calc->normal) / calc->denom;
	calc->p = at(ray, calc->t);
	calc->vtp = vv_sub(calc->p, this->shape.pos);
	calc->u = vv_dot(calc->vtp, this->u);
	calc->v = vv_dot(calc->vtp, this->v);
}

static	void	record(t_ray *ray, t_plane *this, t_hit *rec, t_pl_calc *calc)
{
	rec->t = calc->t;
	rec->point = calc->p;
	rec->normal = calc->normal;
	rec->front = vv_dot(ray->dir, rec->normal) < 0;
	if (!rec->front)
		rec->normal = v_mul(rec->normal, -1);
	rec->color = this->shape.color;
	rec->shape_id = this->shape.id;
}

int		hit_plane(t_ray *ray, t_range range, t_plane *this, t_hit *rec)
{
	t_pl_calc	calc;

	calc = (t_pl_calc){ 0 };
	calc_plane(ray, this, &calc);
	if (fabs(calc.denom) < 1e-6)
		return (FALSE);
	if (!in_range_equal(range, calc.t))
		return (FALSE);
	if (fabs(calc.u) <= (this->size.x * 0.5 + 1e-6)
		&& fabs(calc.v) <= (this->size.y * 0.5 + 1e-6))
	{
		record(ray, this, rec, &calc);
		return (TRUE);
	}
	return (FALSE);
}

t_plane	*new_plane(t_point pos, t_vec3 size, t_vec3 orientation, t_color color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->shape.pos = vvec3(pos);
	plane->size = vvec3(size);
	plane->orientation = unit_vector(orientation);
	plane->u = unit_vector(get_perpendicular(orientation));
	plane->v = unit_vector(cross(orientation, plane->u));
	plane->shape.color = vvec3(color);
	plane->hit = hit_plane;
	return (plane);
}
