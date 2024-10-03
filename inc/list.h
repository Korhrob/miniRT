/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:33:50 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:33:50 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "minirt.h"

struct	s_sphere;
struct	s_plane;
struct	s_cylinder;

typedef union u_shape {
	struct s_sphere		*sphere;
	struct s_plane		*plane;
	struct s_cylinder	*cylinder;
}	t_shape_type;

typedef struct s_list
{
	t_shape_type	d;
	struct s_list	*next;
	enum e_shape	type;
}	t_list;

t_list	*new_list(void *data, enum e_shape shape);
void	list_add(t_list **list, t_list *element);

#endif
