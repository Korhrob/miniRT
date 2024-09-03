#ifndef PLANE_H
# define PLANE_H

#include "shape.h"
#include "vector.h"
#include "ray.h"
#include "hit.h"

typedef struct s_plane
{
	t_shape shape;
	t_vec3	size;
	t_vec3	orientation;
	int(*hit)(t_ray *ray, t_range range, struct s_plane *this, t_hit *rec);
}	t_plane;

int		hit_plane(t_ray *ray, t_range range, t_plane *this, t_hit *rec);
t_plane	*new_plane(t_point pos, t_vec3 size, t_vec3 orientation);

#endif