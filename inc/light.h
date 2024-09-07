#ifndef LIGHT_H
# define LIGHT_H

#include "vector.h"
#include "color.h"

typedef struct s_light
{
	t_point	pos;
	// direction
	double	strength;
	t_color	color;
}	t_light;

typedef struct s_ambient
{
	double	strength;
	t_color	color;
}	t_ambient;


#endif