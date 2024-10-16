/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:35:03 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:35:04 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "list.h"
# include "color.h"

typedef struct s_light
{
	t_point	pos;
	double	strength;
	t_color	color;
}	t_light;

typedef struct s_scene
{
	t_light	ambient;
	t_light	light;
	t_list	*objects;
	void	*camera;
}	t_scene;

#endif
