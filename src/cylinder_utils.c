#include <stdlib.h>
#include "vector.h"
#include "cylinder.h"

void	add_caps(t_cylinder *this)
{
	t_vec3	offset;

	offset = v_mul(unit_vector(this->orientation), this->length / 2.0);
	this->top = new_plane(
			vv_sum(this->shape.pos, offset),
			v_mul(vec3(this->radius, this->radius, this->radius), 2),
			this->orientation, this->shape.color);
	this->top->radius = this->radius;
	this->top->hit = hit_cylinder_cap;
	this->bot = new_plane(
			vv_sub(this->shape.pos, offset),
			v_mul(vec3(this->radius, this->radius, this->radius), 2),
			v_mul(this->orientation, -1), this->shape.color);
	this->bot->radius = this->radius;
	this->bot->hit = hit_cylinder_cap;
}

void	free_cylinder(t_cylinder *this)
{
	if (!this)
		return ;
	if (this->top)
		free(this->top);
	if (this->bot)
		free(this->bot);
	free(this);
}
