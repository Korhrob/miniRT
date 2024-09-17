#ifndef COLOR_H
# define COLOR_H

#include "vector.h"

typedef t_vec3 t_color;

t_color	color(double r, double g, double b);
double	linear_to_gamma(double lin);

#endif