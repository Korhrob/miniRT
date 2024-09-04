#ifndef CAMERA_H
# define CAMERA_H

#include "vector.h"
#include "image.h"
#include "scene.h"

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

t_camera	init_camera(t_point look_from, t_point look_at, t_image image, double fov_degree);
void		render(t_camera camera, t_image image, t_scene *scene);

#endif