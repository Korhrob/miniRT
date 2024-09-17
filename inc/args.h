#ifndef ARGS_H
# define ARGS_H

#include "ray.h"
#include "list.h"
#include "hit.h"
#include "range.h"
#include "scene.h"

typedef struct s_args
{
	t_ray	*ray;
	t_hit	*rec;
	t_scene	*scene;
	t_range	range;
	int		ignore_id;
}	t_args;

#endif