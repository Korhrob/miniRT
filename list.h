#ifndef LIST_H
# define LIST_H

#include "minirt.h"

// union test
// #include "sphere.h"
// #include "plane.h"
// #include "cylinder.h"

typedef	struct s_list
{
	void			*data;
	struct s_list	*next;
	enum e_shape	type;
	// union { // test
	// 	t_sphere	sphere;
	// 	t_plane		plane;
	// 	t_cylinder	cylinder;
	// };
}	t_list;

t_list	*new_list(void *data, enum e_shape shape);
void	list_add(t_list **list, t_list *element);

#endif