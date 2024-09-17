#ifndef SHAPE_H
# define SHAPE_H

# include <math.h>
# include "minirt.h"
# include "vector.h"
# include "ray.h"
# include "color.h"

typedef struct s_shape
{
	t_point			pos;
	t_color			color;
	int				id;
}	t_shape;

t_vec3	get_perpendicular(t_vec3 vec);

#endif