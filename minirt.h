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
	CYLINDER,
	CYLINDER_CAP
};

#ifndef INFINITY
# define INFINITY 1.7976931348623157E+308
#endif
#ifndef PI
# define PI 3.1415926535897932385
#endif

void displayProgressBar(int progress, int total);

// inline double degrees_to_radians(double degrees)
// {
// 	return degrees * pi / 180.0;
// }

#endif