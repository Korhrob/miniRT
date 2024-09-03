#ifndef SHAPE_H
# define SHAPE_H

#include "minirt.h"
#include "vector.h"
#include "ray.h"

typedef	struct s_shape
{
	t_point			pos; // position
	enum e_shape	type;
}	t_shape;

typedef struct s_cylinder
{
	t_shape shape;
	// orientation
	int		length;
	double	radius;
	//int(*hit);
}	t_cylinder;

#endif