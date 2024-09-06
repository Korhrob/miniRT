
#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "vector.h"
#include "ray.h"
#include "shape.h"
#include "sphere.h"
#include "range.h"
#include "hit.h"
#include "color.h"

int	hit_sphere(t_ray *ray, t_range range, t_sphere *this, t_hit *rec)
{
	t_vec3	oc = vv_sub(this->shape.pos, ray->origin);

	double	a = v_len_squared(ray->dir);
	double	h = vv_dot(ray->dir, oc);
	double	c = v_len_squared(oc) - (this->radius * this->radius);

	double	discriminant = h * h - a * c;
	if (discriminant < 0)
		return FALSE;
	
	double	sqrtd = sqrt(discriminant);

	double	root = (h - sqrtd) / a;
	if (!in_range_equal(range, root))
	{
		root = (h + sqrtd) / a;
		if (!in_range_equal(range, root))
			return FALSE;
	}

	rec->t = root;
	rec->point = at(ray, rec->t);
	rec->normal = vv_sub(rec->point, this->shape.pos);
	rec->normal = v_div(rec->normal, this->radius);

	rec->front = vv_dot(ray->dir, rec->normal) < 0;
	if (!rec->front)
		rec->normal = v_mul(rec->normal, -1);

	rec->color = this->shape.color;
	rec->shape_id = this->shape.id;
	
	return TRUE;
}

t_sphere	*new_sphere(t_point pos, double radius, t_color color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return NULL;
	sphere->shape.pos = vvec3(pos);
	sphere->radius = radius;
	sphere->shape.color = vvec3(color);
	sphere->hit = hit_sphere;
	return sphere;
}
