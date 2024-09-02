#ifndef SHAPE_H
# define SHAPE_H

#include "minirt.h"
#include "vector.h"
#include "ray.h"

/*
* p = position
* n = normal
* t = distance
* f = is front face
*/
typedef struct s_hit_record
{
	t_point	point;
	t_vec3	normal;
	double	t;
	int		front;
}	t_hit;

typedef	struct s_shape
{
	t_point			pos; // position
	enum e_shape	type;
}	t_shape;

typedef struct s_plane
{
	t_shape shape;
	// orientation
	int		width;
	int		height;
	//int(*hit);
}	t_plane;

typedef struct s_cylinder
{
	t_shape shape;
	// orientation
	int		length;
	double	radius;
	//int(*hit);
}	t_cylinder;

#endif