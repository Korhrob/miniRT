#include <math.h>
#include <stddef.h>
#include "ray.h"
#include "vector.h"
#include "color.h"
#include "shape.h"
#include "sphere.h"
#include "list.h"

const double infinity = 1.7976931348623157E+308;
const double pi = 3.1415926535897932385;

t_point at(t_ray *ray, double t)
{
	t_vec3	origin = ray->origin;
	t_vec3	dir = v_mul(ray->dir, t);

	return (vv_sum(origin, dir));
}

// // OLD
// static double	hit_shape(t_point *center, double radius, t_ray *r)
// {
// 	t_vec3	oc = vv_sub(center, &r->origin);
// 	double	a = v_len(&r->dir);
// 	double	h = vv_dot(&r->dir, &oc);
// 	double	c = v_len(&oc) - (radius * radius);
// 	double	disc = (h * h) - (a * c);

// 	if (disc < 0)
// 		return (-1.0);
// 	return ((h - sqrt(disc)) / a);
// }

t_color	ray_color(t_ray *ray, t_list *list)
{
	t_hit		rec;

	while (list != NULL)
	{
		// temp conversion to sphere, should check enum type
		t_sphere *shape = list->data; 
		if (shape->hit(ray, 0, infinity, shape, &rec))
		{
			t_color	color = vv_sum(rec.normal, vec3(1, 1, 1));
			return v_mul(color, 0.5);
		}
		list = list->next;
	}

	// GRADIENT
	// t_vec3	unit_direction = unit_vector(&ray->dir);
	// double	a = 0.5 * (unit_direction.y + 1.0);

	// t_color	color_a = { 0.2, 0.4, 1.0 };
	// color_a = v_mul(&color_a, 1.0 - a);

	// t_color	color_b = { 0.5, 0.7, 1.0 };
	// color_b = v_mul(&color_b, a);

	// return ((t_color)vv_sum(&color_a, &color_b));
	return (vec3(0, 0, 0));
}