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

const double infinity = 1.7976931348623157E+308;
const double pi = 3.1415926535897932385;

t_point at(t_ray *ray, double t)
{
	t_vec3	origin = ray->origin;
	t_vec3	dir = v_mul(ray->dir, t);

	return (vv_sum(origin, dir));
}

int	ray_hit(t_ray *ray, t_hit *rec, t_range range, t_list *list)
{
	t_hit	temp_rec;
	int		hit = FALSE;
	double	closest = range.max;

	while (list != NULL)
	{
		// temp conversion to sphere, should check enum type
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
				rec->shape = shape;
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

t_color	ray_color(t_ray *ray, t_list *list)
{
	t_hit		rec;

	if (ray_hit(ray, &rec, new_range(0, infinity), list))
	{
		t_color	color = vv_sum(rec.normal, vec3(1, 1, 1));
		return v_mul(color, 0.5);
	}

	t_vec3	unit_direction = unit_vector(ray->dir);
	double	a = 0.5 * (unit_direction.y + 1.0);

	t_color	color_a = { 1.0, 1.0, 1.0 };
	color_a = v_mul(color_a, 1.0 - a);

	t_color	color_b = { 0.5, 0.7, 1.0 };
	color_b = v_mul(color_b, a);

	return ((t_color)vv_sum(color_a, color_b));
	//return (vec3(0, 0, 0));
}