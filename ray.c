#include "ray.h"
#include <math.h>
#include "vector.h"
#include "color.h"

t_point at(t_ray *ray, double t)
{
	t_vec3	origin = ray->origin;
	t_vec3	dir = v_mul(&ray->dir, t);

	return (vv_sum(&origin, &dir));
}

static double	hit_sphere(t_point *center, double radius, t_ray *r)
{
	t_vec3	oc = vv_sub(center, &r->origin);
	double	a = v_len(&r->dir);
	double	h = vv_dot(&r->dir, &oc);
	double	c = v_len(&oc) - (radius * radius);
	double	disc = (h * h) - (a * c);

	if (disc < 0)
		return (-1.0);
	return ((h - sqrt(disc)) / a);
}

t_color	ray_color(t_ray *ray)
{
	t_point	sphere_a = { 0, 0, -1 };
	double	t = hit_sphere(&sphere_a, 0.5, ray);
	if (t > 0.0)
	{
		t_vec3	a = at(ray, t);
		t_vec3	b = { 0, 0, -1 };
		t_vec3	c = vv_sub(&a, &b);
		t_vec3	n = unit_vector(&c);
		t_color	col = { n.x + 1, n.y + 1, n.z + 1 };
		return ((t_color)v_mul(&col, 0.5));
	}

	t_vec3	unit_direction = unit_vector(&ray->dir);
	double	a = 0.5 * (unit_direction.y + 1.0);

	t_color	color_a = { 0.2, 0.4, 1.0 };
	color_a = v_mul(&color_a, 1.0 - a);

	t_color	color_b = { 0.5, 0.7, 1.0 };
	color_b = v_mul(&color_b, a);

	return ((t_color)vv_sum(&color_a, &color_b));
}