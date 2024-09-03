
#include <stdlib.h>
#include <math.h>
#include "minirt.h"
#include "plane.h"

int		hit_plane(t_ray *ray, t_range range, t_plane *this, t_hit *rec)
{
	return FALSE;
}

t_plane	*new_plane(t_point pos, t_vec3 size, t_vec3 orientation)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return NULL;
	plane->shape.type = PLANE;
	plane->shape.pos.x = pos.x;
	plane->shape.pos.y = pos.y;
	plane->shape.pos.z = pos.z;
	// size
	// orientation
	plane->hit = hit_plane;
	return plane;
}