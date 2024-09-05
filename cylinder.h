#ifndef CYLINDER_H
# define CYLINDER_H

#include "shape.h"
#include "ray.h"
#include "range.h"
#include "hit.h"
#include "color.h"
#include "plane.h"

typedef struct s_cylinder
{
	t_shape shape;
	t_vec3	orientation;
	int		length;
	double	radius;
	t_plane	*top;
	t_plane	*bot;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	int(*hit)(t_ray *ray, t_range range, struct s_cylinder *this, t_hit *rec);
}	t_cylinder;

int			hit_cylinder(t_ray *ray, t_range range, t_cylinder *this, t_hit *rec);
t_cylinder	*new_cylinder(t_point pos, double radius, double length, t_vec3 orientation, t_color color);

#endif