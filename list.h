#ifndef LIST_H
# define LIST_H

#include "minirt.h"

typedef	struct s_list
{
	void			*data;
	struct s_list	*next;
	enum e_shape	type;
}	t_list;

t_list	*new_list(void *data, enum e_shape shape);
void	list_add(t_list **list, t_list *element);

#endif