/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:57:14 by avegis            #+#    #+#             */
/*   Updated: 2024/10/02 18:57:15 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"
#include "list.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"
#include "image.h"
#include "camera.h"
#include "scene.h"
#include "../libft/libft.h"
#include "parsing.h"

void	init_ambient(t_scene *scene, t_parse info)
{
	scene->ambient.color = info.color;
	scene->ambient.strength = info.v1;
}

void	init_light(t_scene *scene, t_parse info)
{
	scene->light.pos = info.pos;
	scene->light.strength = info.v1;
}

void	init_plane(t_list **list, t_parse info, int *id)
{
	t_list	*temp;
	t_plane	*data;
	t_vec3	size;

	size = vec3(INFINITY, INFINITY, INFINITY);
	temp = 0;
	data = new_plane(info.pos, size, info.orien, info.color);
	data->shape.id = *id;
	temp = new_list(data, PLANE);
	list_add(list, temp);
}

void	init_sphere(t_list **list, t_parse info, int *id)
{
	t_list		*temp;
	t_sphere	*data;

	data = new_sphere(info.pos, info.v1, info.color);
	data->shape.id = *id;
	temp = new_list(data, SPHERE);
	list_add(list, temp);
}

void	init_cylinder(t_list **list, t_parse info, int *id)
{
	t_list		*temp;
	t_cylinder	*data;
	t_vec3		vec;

	vec = vec3(info.v1, info.v2, 0);
	data = new_cylinder(info.pos, vec, info.orien, info.color);
	data->shape.id = *id;
	data->top->shape.id = *id;
	data->bot->shape.id = *id;
	temp = new_list(data, CYLINDER);
	list_add(list, temp);
	temp = new_list(data->top, CYLINDER_CAP);
	list_add(list, temp);
	temp = new_list(data->bot, CYLINDER_CAP);
	list_add(list, temp);
}
