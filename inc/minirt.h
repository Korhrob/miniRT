#ifndef MINIRT_H
# define MINIRT_H

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

#endif