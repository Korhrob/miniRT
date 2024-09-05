#include "vector.h"
#include <math.h>

t_vec3	vec3(double x, double y, double z)
{
	t_vec3 o;

	o.x = x;
	o.y = y;
	o.z = z;
	return (o);
}

t_vec3	vvec3(t_vec3 v)
{
	t_vec3 o;

	o.x = v.x;
	o.y = v.y;
	o.z = v.z;
	return (o);
}

// vec.xyz * t
t_vec3	v_mul(t_vec3 v, double t)
{
	t_vec3	o;

	o.x = (v.x * t);
	o.y = (v.y * t);
	o.z = (v.z * t);
	return (o);
}

// vec.xyz * (1/t)
t_vec3	v_div(t_vec3 v, double t)
{
	t_vec3	o;

	if (t == 0)
	{
		o.x = 0;
		o.y = 0;
		o.z = 0;
		return (o);
	}
	o.x = v.x * (1/t);
	o.y = v.y * (1/t);
	o.z = v.z * (1/t);
	return (o);
}

double	v_len(t_vec3 v)
{
	return (sqrt(v_len_squared(v)));
}

double	v_len_squared(t_vec3 v)
{
	double len_squared = 
		(v.x * v.x) + 
		(v.y * v.y) +
		(v.z * v.z);
	return (len_squared);
}

// vec3.xyz + vec3.xyz
t_vec3	vv_sum(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.x + b.x);
	o.y = (a.y + b.y);
	o.z = (a.z + b.z);
	return (o);
}

// vec3.xyz - vec3.xyz
t_vec3	vv_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.x - b.x);
	o.y = (a.y - b.y);
	o.z = (a.z - b.z);
	return (o);
}

// vec3.xyz * vec3.xyz
t_vec3	vv_mul(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.x * b.x);
	o.y = (a.y * b.y);
	o.z = (a.z * b.z);
	return (o);
}

// (vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z)
double	vv_dot(t_vec3 a, t_vec3 b)
{
	double dot = 
		(a.x * b.x) + 
		(a.y * b.y) +
		(a.z * b.z);
	return (dot);
}

//	vec3.xyz / vec3 len
t_vec3	unit_vector(t_vec3 v)
{
	t_vec3	o;

	o = v_div(v, v_len(v));
	return (o);
}

t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	o;

	o.x = (a.y * b.z - a.z * b.y);
	o.y = (a.z * b.x - a.x * b.z);
	o.z = (a.x * b.y - a.y * b.x);
	return (o);
}

t_vec3	local(t_vec3 vec, t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_vec3	o;

	o.x = vv_dot(vec, u);
	o.y = vv_dot(vec, v);
	o.z = vv_dot(vec, w);
	return (o);
}