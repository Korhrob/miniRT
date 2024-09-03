#ifndef HIT_H
# define HIT_H

#include "vector.h"

typedef struct s_hit_record
{
	t_point	point;
	t_vec3	normal;
	double	t;
	int		front;
	void	*shape;
}	t_hit;

#endif