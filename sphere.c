
#include <math.h>
#include "minirt.h"
#include "vector.h"
#include "ray.h"
#include "shape.h"

int	hit_sphere(t_ray *ray, double ray_tmin, double ray_tmax, t_sphere *sphere)
{
	t_vec3	oc = vv_sub(&sphere->shape.position, &ray->origin);
	double	a = v_len(&ray->dir);
	double	h = vv_dot(&ray->dir, &oc);
	double	c = v_len(&oc) - (sphere->radius * sphere->radius);

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

	sphere->shape.rec.t = root;
	sphere->shape.rec.p = at(ray, sphere->shape.rec.t);
	// outward_normal
	// set face normal
	sphere->shape.rec.normal = vv_sub(&sphere->shape.rec.p, &sphere->shape.position);
	sphere->shape.rec.normal = v_div(&sphere->shape.rec.normal, sphere->radius);

	return TRUE;
}