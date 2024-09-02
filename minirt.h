#ifndef MINIRT_H
# define MINIRT_H

// #include "vector.h"
// #include "color.h"
// #include "ray.h"
// #include "shape.h"
// #include "list.h"

#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

enum	e_shape
{
	SPHERE,
	PLANE,
	CYLINDER
};

// const double infinity = 1.7976931348623157E+308;
// const double pi = 3.1415926535897932385;

// inline double degrees_to_radians(double degrees)
// {
// 	return degrees * pi / 180.0;
// }

#endif