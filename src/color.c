#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "color.h"

t_color	color(double r, double g, double b)
{
	t_color	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

double	linear_to_gamma(double lin)
{
	if (lin > 0)
		return (sqrt(lin));
	return (0);
}
