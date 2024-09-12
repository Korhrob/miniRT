#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "ray.h"
#include "vector.h"
#include "color.h"
#include "shape.h"
#include "sphere.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"
#include "list.h"
#include "range.h"
#include "hit.h"
#include "light.h"
#include "scene.h"

t_point at(t_ray *ray, double t)
{
	t_vec3	origin = ray->origin;
	t_vec3	dir = v_mul(ray->dir, t);

	return (vv_sum(origin, dir));
}

// put range inside t_ray
static int	iter(t_list *list, t_ray *ray, t_hit *temp_rec, t_range range, int ignore)
{
	int		hit;

	hit = FALSE;
	if (list->type == SPHERE)
	{
		if (list->d.sphere->hit(ray, range, list->d.sphere, temp_rec))
			hit = (list->d.sphere->shape.id != ignore); // && temp_rec.front
	}
	else if (list->type == PLANE || list->type == CYLINDER_CAP)
	{
		if (list->d.plane->hit(ray, range, list->d.plane, temp_rec))
			hit = (list->d.plane->shape.id != ignore); // && temp_rec.front
	}
	else if (list->type == CYLINDER)
	{
		if (list->d.cylinder->hit(ray, range, list->d.cylinder, temp_rec))
			hit = (list->d.cylinder->shape.id != ignore); // && temp_rec.front
	}
	return (hit);
}

int	ray_hit(t_ray *ray, t_hit *rec, t_range range, t_scene *scene, int ignore)
{
	t_list			*list;
	t_hit			temp_rec;
	int				hit;
	double			closest;

	hit = FALSE;
	closest = range.max;
	list = scene->objects;
	while (list != NULL)
	{
		range = new_range(range.min, closest);
		if (iter(list, ray, &temp_rec, range, ignore))
		{
			hit = TRUE;
			closest = temp_rec.t;
			rec->point = vvec3(temp_rec.point);
			rec->normal = vvec3(temp_rec.normal);
			rec->color = vvec3(temp_rec.color);
			rec->t = temp_rec.t;
			rec->front = temp_rec.front;
			rec->shape_id = temp_rec.shape_id;
		}
		list = list->next;
	}
	return (hit);
}

static t_color	gradient(double a)
{
	t_color	color_a = { 1.0, 1.0, 1.0 };
	color_a = v_mul(color_a, 1.0 - a);

	t_color	color_b = { 0.5, 0.7, 1.0 };
	color_b = v_mul(color_b, a);

	return ((t_color)vv_sum(color_a, color_b));
}

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_hit		rec;

	if (ray_hit(ray, &rec, new_range(0, INFINITY), scene, -1))
		return (calc_light(&rec, scene));
	return (gradient(0.5 * (ray->dir.y + 1.0)));
}
