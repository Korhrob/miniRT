#ifndef SPHERE_H
# define SPHERE_H

#include "shape.h"
#include "ray.h"
#include "range.h"
#include "hit.h"

typedef struct s_sphere
{
	t_shape shape;
	double	radius;
	int		(*hit)(t_ray *ray, t_range range, struct s_sphere *this, t_hit *rec);
}	t_sphere;

int			hit_sphere(t_ray *ray, t_range range, t_sphere *this, t_hit *rec);
t_sphere	*new_sphere(t_point pos, double radius);

#endif