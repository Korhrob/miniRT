#ifndef HIT_H
# define HIT_H

#include "vector.h"

typedef struct s_hit_record
{
	t_point	point;
	t_vec3	normal;
	t_color	color;
	double	t;
	int		front;
	int		shape_id;
}	t_hit;

#endif