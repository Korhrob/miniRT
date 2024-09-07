#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "color.h"

void write_color(int fd, t_color color)
{
	int	ir = 255.999 * color.x;
	int	ig = 255.999 * color.y;
	int ib = 255.999 * color.z;
	dprintf(fd, "%d %d %d\n", ir, ig, ib);
}

t_color	color(double r, double g, double b)
{
	t_color	color = { r, g, b };

	return (color);
}