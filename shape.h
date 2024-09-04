#ifndef SHAPE_H
# define SHAPE_H

#include "minirt.h"
#include "vector.h"
#include "ray.h"
#include "color.h"

typedef	struct s_shape
{
	t_point			pos; // position
	t_color			color;
	int				id;
}	t_shape;

typedef struct s_generic_shape
{
	t_shape			*data;
}	t_generic;


typedef struct s_cylinder
{
	t_shape shape;
	// orientation
	int		length;
	double	radius;
	//int(*hit);
}	t_cylinder;

#endif