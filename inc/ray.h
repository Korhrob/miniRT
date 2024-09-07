#ifndef RAY_H
# define RAY_H

#include "vector.h"
#include "color.h"
#include "shape.h"
#include "list.h"
#include "range.h"
#include "hit.h"
#include "scene.h"

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

t_point	at(t_ray *ray, double t);
int		ray_hit(t_ray *ray, t_hit *rec, t_range range, t_scene *scene, int ignore);
t_color	ray_color(t_ray *ray, t_scene *scene);

#endif