#ifndef LIST_H
# define LIST_H

#include "minirt.h"

typedef	struct s_list
{
	void			*data;
	struct s_list	*next;
	enum e_shape	type;
}	t_list;

#endif