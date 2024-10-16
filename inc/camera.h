/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:33:31 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:33:32 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "image.h"
# include "scene.h"
# include "../mlx42/include/MLX42/MLX42.h"

typedef struct s_camera
{
	double	fov_radian;
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	t_point	center;
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
	t_vec3	viewport_ul;
	t_vec3	pixel00_loc;
}	t_camera;

t_camera	init_camera(t_point from, t_point to, t_image image, double fov_d);
void		render(mlx_image_t *img, t_image image, t_scene *scene);

#endif
