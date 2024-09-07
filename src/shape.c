
#include <math.h>
#include "shape.h"
#include "vector.h"

t_vec3 get_perpendicular(t_vec3 vec)
{
    if (fabs(vec.x) > fabs(vec.y) && fabs(vec.x) > fabs(vec.z))
        return cross(vec, vec3(0, 1, 0));  // Use Y axis if X is dominant
    return cross(vec, vec3(1, 0, 0));      // Use X axis otherwise
}