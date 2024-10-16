/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:24:08 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:24:11 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "image.h"
#include "scene.h"
#include "color.h"
#include "../mlx42/include/MLX42/MLX42.h"

static void	set_base(t_camera *cam, t_image *image)
{
	cam->focal_length = 1;
	cam->viewport_width = 2.0 * tan(cam->fov_radian
			/ (2.0 * cam->focal_length));
	cam->viewport_height = cam->viewport_width / image->aspect_ratio;
}

t_camera	init_camera(t_point look_from, t_point look_at,
	t_image image, double fov_degree)
{
	t_camera	cam;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;

	cam.fov_radian = fov_degree * PI / 180.0;
	set_base(&cam, &image);
	cam.center = vvec3(look_from);
	look_at = v_mul(look_at, -1);
	w = unit_vector(look_at);
	u = unit_vector(cross(vec3(0, 1, 0), w));
	if (look_at.x < 1e-6 && look_at.z < 1e-6)
		u = unit_vector(cross(vec3(1, 0, 0), w));
	v = cross(w, u);
	cam.viewport_u = v_mul(u, cam.viewport_width);
	cam.viewport_v = v_mul(v_mul(v, -1), cam.viewport_height);
	cam.pixel_delta_u = v_div(cam.viewport_u, image.width);
	cam.pixel_delta_v = v_div(cam.viewport_v, image.height);
	cam.viewport_ul = vv_sub(cam.center, v_mul(w, cam.focal_length));
	cam.viewport_ul = vv_sub(cam.viewport_ul, v_div(cam.viewport_u, 2));
	cam.viewport_ul = vv_sub(cam.viewport_ul, v_div(cam.viewport_v, 2));
	cam.pixel00_loc = vv_sum(cam.viewport_ul,
			v_mul(vv_sum(cam.pixel_delta_u, cam.pixel_delta_v), 0.5));
	return (cam);
}

static t_color	get_pixel_color(t_scene *scene, int x, int y)
{
	t_point		pixel_center;
	t_vec3		ray_direction;
	t_ray		ray;
	t_camera	*cam;

	cam = (t_camera *)scene->camera;
	pixel_center = vvec3(cam->pixel00_loc);
	pixel_center = vv_sum(pixel_center, v_mul(cam->pixel_delta_u, x));
	pixel_center = vv_sum(pixel_center, v_mul(cam->pixel_delta_v, y));
	ray_direction = unit_vector(vv_sub(pixel_center, cam->center));
	ray.origin = cam->center;
	ray.dir = ray_direction;
	return (ray_color(&ray, scene));
}

static int32_t	color_to_pixel(t_color color)
{
	int32_t	pixel;
	int		ir;
	int		ig;
	int		ib;

	ir = 255.99 * linear_to_gamma(color.x);
	ig = 255.99 * linear_to_gamma(color.y);
	ib = 255.99 * linear_to_gamma(color.z);
	pixel = (ir << 24 | ig << 16 | ib << 8 | 255);
	return (pixel);
}

void	render(mlx_image_t *img, t_image image, t_scene *scene)
{
	t_color		color;
	int			x;
	int			y;

	y = 0;
	while (y < image.height)
	{
		x = 0;
		while (x < image.width)
		{
			color = get_pixel_color(scene, x, y);
			mlx_put_pixel(img, x, y, color_to_pixel(color));
			x++;
		}
		y++;
	}
}
