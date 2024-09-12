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

int	ray_hit(t_ray *ray, t_hit *rec, t_range range, t_scene *scene, int ignore)
{
	t_shape_type	base;
	t_list			*list;
	t_hit			temp_rec;
	int				hit = FALSE;
	int				thit;
	double			closest = range.max;

	list = scene->objects;
	while (list != NULL)
	{
		thit = FALSE;
		if (list->type == SPHERE)
		{
			base.sphere = list->d.sphere;
			if (base.sphere->hit(ray, new_range(range.min, closest), base.sphere, &temp_rec))
				thit = (base.sphere->shape.id != ignore); //  && temp_rec.front
		}
		else if (list->type == PLANE || list->type == CYLINDER_CAP)
		{
			base.plane = list->d.plane;
			if (base.plane->hit(ray, new_range(range.min, closest), base.plane, &temp_rec))
				thit = (base.plane->shape.id != ignore); //  && temp_rec.front
		}
		else if (list->type == CYLINDER)
		{
			base.cylinder = list->d.cylinder;
			if (base.cylinder->hit(ray, new_range(range.min, closest), base.cylinder, &temp_rec))
				thit = (base.cylinder->shape.id != ignore); // && temp_rec.front
		}
		if (thit)
		{
			hit = TRUE;
			closest = temp_rec.t;
			rec->point = vvec3(temp_rec.point); // maybe dangerous
			rec->normal = vvec3(temp_rec.normal); // maybe dangerous
			rec->color = vvec3(temp_rec.color); // maybe dangerous
			rec->t = temp_rec.t;
			rec->front = temp_rec.front;
			rec->shape_id = temp_rec.shape_id;
		}
		list = list->next;
	}
	return hit;
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
	//return (vec3(0, 0, 0));
}