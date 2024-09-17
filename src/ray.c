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
#include "args.h"

t_point at(t_ray *ray, double t)
{
	t_vec3	origin = ray->origin;
	t_vec3	dir = v_mul(ray->dir, t);

	return (vv_sum(origin, dir));
}

// put range inside t_ray
static int	iter(t_args *args, t_hit *temp, t_list *this) // t_list *list, t_ray *ray, t_hit *temp_rec, t_range range, int ignore
{
	int		hit;

	hit = FALSE;
	if (args->scene->obj->type == SPHERE)
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

int	ray_hit(t_args *args) // t_ray *ray, t_hit *rec, t_range range, t_scene *scene, int ignore
{
	t_list			*list;
	t_hit			temp_rec;
	int				hit;
	double			closest;

	hit = FALSE;
	closest = args->range.max;
	list = args->scene->objects;
	while (list != NULL)
	{
		args->range = new_range(args->range.min, closest);
		if (iter(args, &temp_rec)) // list, ray, &temp_rec, range, ignore
		{
			hit = TRUE;
			closest = temp_rec.t;
			args->rec->point = vvec3(temp_rec.point);
			args->rec->normal = vvec3(temp_rec.normal);
			args->rec->color = vvec3(temp_rec.color);
			args->rec->t = temp_rec.t;
			args->rec->front = temp_rec.front;
			args->rec->shape_id = temp_rec.shape_id;
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
	t_args		args;
	t_hit		rec;

	args.ray = ray;
	args.scene = scene;
	args.rec = &rec;
	args.range = new_range(0, INFINITY);
	args.ignore_id = -1;

	if (ray_hit(&args)) // ray, &rec, new_range(0, INFINITY), scene, -1
	{

		return (calc_light(&rec, scene));
	}
	return (gradient(0.5 * (ray->dir.y + 1.0)));
}
