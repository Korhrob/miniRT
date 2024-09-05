
#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "vector.h"
#include "shape.h"
#include "plane.h"
#include "color.h"

int		hit_plane(t_ray *ray, t_range range, t_plane *this, t_hit *rec)
{
	t_vec3	normal = unit_vector(this->orientation);
	double	denom = vv_dot(normal, ray->dir);

	// 1e-6 epsilon
	if (fabs(denom) > 1e-6)
	{
		t_vec3	oc = vv_sub(this->shape.pos, ray->origin);
		double	t = vv_dot(oc, normal) / denom;

		if (!in_range_equal(range, t))
			return FALSE;

		t_point	p = at(ray, t);
		t_vec3	vtp = vv_sub(p, this->shape.pos);

		double	proj_u = vv_dot(vtp, this->u);
		double	proj_v = vv_dot(vtp, this->v);

		if (fabs(proj_u) <= (this->size.x * 0.5 + 1e-6)
			&& fabs(proj_v) <= (this->size.y * 0.5 + 1e-6))
		{
			rec->t = t;
			rec->point = p;
			rec->normal = normal;
			
			rec->front = vv_dot(ray->dir, rec->normal) < 0;
			if (!rec->front)
				rec->normal = v_mul(rec->normal, -1);

			return (TRUE);
		}
	}
	return (FALSE);
}

t_plane	*new_plane(t_point pos, t_vec3 size, t_vec3 orientation, t_color color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return NULL;
	plane->shape.pos = vvec3(pos);
	plane->size = vvec3(size);
	plane->orientation = unit_vector(orientation);
	plane->u = unit_vector(get_perpendicular(orientation));
	plane->v = unit_vector(cross(orientation, plane->u));
	plane->shape.color = vvec3(color);
	plane->hit = hit_plane;
	return plane;
}