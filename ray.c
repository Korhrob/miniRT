#include <math.h>
#include <stddef.h>

#include "ray.h"
#include "vector.h"
#include "color.h"
#include "shape.h"
#include "sphere.h"
#include "plane.h"
#include "list.h"
#include "range.h"
#include "hit.h"
#include "light.h"
#include "scene.h"

static double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

static double	step(double val, double step)
{
	if (val > step)
		return (1);
	return (0);
}

static double smoothstep(double val, t_range range)
{
	if (val > range.min)
	{
		// 
	}
	return (0);
}

t_point at(t_ray *ray, double t)
{
	t_vec3	origin = ray->origin;
	t_vec3	dir = v_mul(ray->dir, t);

	return (vv_sum(origin, dir));
}

int	ray_hit(t_ray *ray, t_hit *rec, t_range range, t_scene *scene)
{
	t_list	*list;
	t_hit	temp_rec;
	int		hit = FALSE;
	double	closest = range.max;

	list = scene->objects;
	while (list != NULL)
	{
		if (list->type == SPHERE)
		{
			t_sphere *shape = list->data; 
			if (shape->hit(ray, new_range(range.min, closest), shape, &temp_rec))
			{
				hit = TRUE;
				closest = temp_rec.t;
				rec->point = temp_rec.point;
				rec->normal = temp_rec.normal;
				rec->t = temp_rec.t;
				rec->front = temp_rec.front;
				rec->shape = (void *)&shape->shape;
			}
		}
		else if (list->type == PLANE)
		{
			t_plane	*shape = list->data;
			
		}
		// else if (list->type == CYLINDER) {}

		list = list->next;
	}
	return hit;
}

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_hit		rec;

	if (ray_hit(ray, &rec, new_range(0, INFINITY), scene))
	{
		// move to lighting calculation

		// normal to color
		// t_color	color = vv_sum(rec.normal, vec3(1, 1, 1));
		// return v_mul(color, 0.5);

		// surface color
		t_shape	*shape = (t_shape*)rec.shape;
		t_color	color = shape->color;

		// ambient light
		t_color	ambient;
		ambient = vv_mul(color, scene->ambient.color);
		ambient = v_mul(ambient, scene->ambient.strength);

		// point light
		// light direction L = v_len(Ls - P)
		// diffuse max(0,vv_dot(normal, L)) * i * color
		t_color	diffuse;
		t_vec3	l = unit_vector(vv_sub(scene->light.pos, rec.point));
		double	i = max(0, vv_dot(rec.normal, l)) * scene->light.strength;
		diffuse = v_mul(color, i);

		// convert to half lambert (extra)

		color = vv_sum(ambient, diffuse);

		// spot (fake specular)
		//
		//
		//

		// shadow

		return (color);

	}

	double	a = 0.5 * (ray->dir.y + 1.0);

	t_color	color_a = { 1.0, 1.0, 1.0 };
	color_a = v_mul(color_a, 1.0 - a);

	t_color	color_b = { 0.5, 0.7, 1.0 };
	color_b = v_mul(color_b, a);

	return ((t_color)vv_sum(color_a, color_b));
	//return (vec3(0, 0, 0));
}