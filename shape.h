#pragma once
#include "minirt.h"
#include "vector.h"

typedef struct s_hit_record
{
	t_point	p;
	t_vec3	normal;
	double	t;
	int		front;
}	t_hit;

typedef	struct s_shape
{
	t_hit	rec;
	t_point	position;
	t_vec3	orientation;
	double(*hit)();
}	t_shape;


typedef struct s_sphere
{
	t_shape shape;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_shape shape;
	int		width;
	int		height;
}	t_plane;

typedef struct s_cylinder
{
	t_shape shape;
	int		length;
	double	radius;
}	t_cylinder;