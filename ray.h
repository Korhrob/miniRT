#pragma once
#include "vector.h"
#include "color.h"

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

t_color	ray_color(t_ray *ray);
t_point at(t_ray *ray, double t);