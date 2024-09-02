#ifndef SPHERE_H
# define SPHERE_H

#include "shape.h"
#include "ray.h"

typedef struct s_sphere
{
	t_shape shape;
	double	radius;
	int		(*hit)(t_ray *ray, double ray_tmin, double ray_tmax, struct s_sphere *this, t_hit *rec);
}	t_sphere;

int			hit_sphere(t_ray *ray, double ray_tmin, double ray_tmax, t_sphere *this, t_hit *rec);
t_sphere	*new_sphere(t_point pos, double radius);

#endif