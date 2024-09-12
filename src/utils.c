
#include "vector.h"

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

t_vec3	v_clamp(t_vec3 v)
{
	t_vec3	o;

	o.x = v.x;
	o.y = v.y;
	o.z = v.z;
	if (o.x > 1)
		o.x = 1;
	if (o.y > 1)
		o.y = 1;
	if (o.z > 1)
		o.z = 1;
	return (o);
}
