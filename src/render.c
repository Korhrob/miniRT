/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:25:43 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:25:44 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "scene.h"
#include "camera.h"
#include "render.h"
#include "../mlx42/include/MLX42/MLX42.h"

static void	esc_hook(void *ptr)
{
	mlx_t	*mlx;

	mlx = ptr;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	render_start(t_image image, t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(image.width, image.height, "miniRT", true);
	if (!mlx)
		return (0);
	img = mlx_new_image(mlx, image.width, image.height);
	if (!img)
		return (0);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		return (0);
	render(img, image, scene);
	mlx_loop_hook(mlx, esc_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (1);
}
