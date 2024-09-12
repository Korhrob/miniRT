
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

static void	sphere_calc(t_ray *ray, t_sphere *this, t_sp_calc *calc)
{
	calc->oc = vv_sub(this->shape.pos, ray->origin);
	calc->a = v_len_squared(ray->dir);
	calc->h = vv_dot(ray->dir, calc->oc);
	calc->c = v_len_squared(calc->oc) - (this->radius * this->radius);
	calc->discriminant = calc->h * calc->h - calc->a * calc->c;
}

static void record(t_ray *ray, t_hit *rec, t_sphere *this, t_sp_calc *calc)
{
	rec->t = calc->root;
	rec->point = at(ray, rec->t);
	rec->normal = vv_sub(rec->point, this->shape.pos);
	rec->normal = v_div(rec->normal, this->radius);
	rec->front = vv_dot(ray->dir, rec->normal) < 0;
	if (!rec->front)
		rec->normal = v_mul(rec->normal, -1);
	rec->color = this->shape.color;
	rec->shape_id = this->shape.id;
}

int	hit_sphere(t_ray *ray, t_range range, t_sphere *this, t_hit *rec)
{
	t_sp_calc	calc;

	calc = (t_sp_calc){ 0 };
	sphere_calc(ray, this, &calc);
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
	record(ray, rec, this, &calc);
	return (TRUE);
}

t_sphere	*new_sphere(t_point pos, double radius, t_color color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->shape.pos = vvec3(pos);
	sphere->radius = radius;
	sphere->shape.color = vvec3(color);
	sphere->hit = hit_sphere;
	return (sphere);
}
