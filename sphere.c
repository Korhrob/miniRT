
#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "vector.h"
#include "ray.h"
#include "shape.h"
#include "sphere.h"

int	hit_sphere(t_ray *ray, double ray_tmin, double ray_tmax, t_sphere *this, t_hit *rec)
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
	if (root <= ray_tmin || root > ray_tmax)
	{
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || root > ray_tmax)
			return FALSE;
	}

	rec->t = root;
	rec->point = at(ray, rec->t);
	rec->normal = vv_sub(rec->point, this->shape.pos);
	rec->normal = v_div(rec->normal, this->radius);

	rec->front = vv_dot(ray->dir, rec->normal) < 0;
	if (!rec->front)
		rec->normal = v_mul(rec->normal, -1);

	return TRUE;
}

t_sphere	*new_sphere(t_point pos, double radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return NULL;
	sphere->shape.type = SPHERE;
	sphere->shape.pos.x = pos.x;
	sphere->shape.pos.y = pos.y;
	sphere->shape.pos.z = pos.z;
	sphere->radius = radius;
	sphere->hit = hit_sphere;
	return sphere;
}
