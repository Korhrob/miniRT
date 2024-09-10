#ifndef LIGHT_H
# define LIGHT_H

#include "vector.h"
#include "color.h"
#include "scene.h"
#include "hit.h"

t_color	calc_light(t_hit *rec, t_scene *scene);

#endif