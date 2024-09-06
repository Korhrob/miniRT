
#include <stdlib.h>
#include "minirt.h"
#include "list.h"

t_list	*new_list(void *data, enum e_shape shape)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	if (shape == SPHERE)
		list->d.sphere = data;
	else if (shape == PLANE || shape == CYLINDER_CAP)
		list->d.plane = data;
	else if (shape == CYLINDER)
		list->d.cylinder = data;
	list->type = shape;
	list->next = NULL;
	return (list);
}

void	list_add(t_list **list, t_list *element)
{
	t_list	*temp;

	if (*list == NULL)
	{
		*list = element;
		return;
	}
	temp = *list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = element;
}
