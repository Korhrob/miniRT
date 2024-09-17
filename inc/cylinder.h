#ifndef CYLINDER_H
# define CYLINDER_H

# include "shape.h"
# include "ray.h"
# include "range.h"
# include "hit.h"
# include "color.h"
# include "plane.h"

typedef struct s_cl_calc
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;
	double	root;
	double	y;
}	t_cl_calc;

typedef struct s_cylinder	t_cylinder;

struct s_cylinder
{
	t_shape	shape;
	t_vec3	orientation;
	int		length;
	double	radius;
	t_plane	*top;
	t_plane	*bot;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	int		(*hit)(t_ray *ray, t_range ran, t_cylinder *this, t_hit *rec);
};

int			hit_cylinder(t_ray *ray, t_range r, t_cylinder *this, t_hit *rec);
int			hit_cylinder_cap(t_ray *ray, t_range r, t_plane *this, t_hit *rec);
t_cylinder	*new_cylinder(t_point pos, t_vec3 size, t_vec3 dir, t_color color);

// cylinder_utils
void		add_caps(t_cylinder *this);
void		free_cylinder(t_cylinder *this);

#endif