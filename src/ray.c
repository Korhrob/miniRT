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

t_point	at(t_ray *ray, double t)
{
	t_vec3	origin;
	t_vec3	dir;

	origin = ray->origin;
	dir = v_mul(ray->dir, t);
	return (vv_sum(origin, dir));
}

// put range inside t_ray
static int	iter(t_args *args, t_hit *temp, t_list *this)
{
	int		hit;

	hit = FALSE;
	if (this->type == SPHERE)
	{
		if (this->d.sphere->hit(args->ray, args->range, this->d.sphere, temp))
			hit = (this->d.sphere->shape.id != args->ignore_id);
	}
	else if (this->type == PLANE || this->type == CYLINDER_CAP)
	{
		if (this->d.plane->hit(args->ray, args->range, this->d.plane, temp))
			hit = (this->d.plane->shape.id != args->ignore_id);
	}
	else if (this->type == CYLINDER)
	{
		if (this->d.cylinder->hit(
				args->ray, args->range, this->d.cylinder, temp))
			hit = (this->d.cylinder->shape.id != args->ignore_id);
	}
	return (hit);
}

int	ray_hit(t_args *args)
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
		if (iter(args, &temp_rec, list))
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

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_args	args;
	t_hit	rec;

	args.ray = ray;
	args.scene = scene;
	args.rec = &rec;
	args.range = new_range(0, INFINITY);
	args.ignore_id = -1;
	if (ray_hit(&args))
		return (calc_light(&rec, scene));
	return (vec3(0, 0, 0));
}
