#pragma once
#include "vector.h"

typedef t_vec3 t_color;

void write_color(int fd, t_color color);
t_color	color(double r, double g, double b);