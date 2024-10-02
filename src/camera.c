#include <math.h>
#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "image.h"
#include "scene.h"
#include "color.h"
#include "../mlx42/include/MLX42/MLX42.h"

t_camera	init_camera(t_point look_from, t_point look_at,
	t_image image, double fov_degree)
{
	t_camera	cam;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;

	cam.fov_radian = fov_degree * PI / 180.0;
	cam.focal_length = 1;
	cam.viewport_width = 2.0 * tan(cam.fov_radian / (2.0 * cam.focal_length));
	cam.viewport_height = cam.viewport_width / image.aspect_ratio;
	cam.center = vvec3(look_from);
	w = unit_vector(vv_sub(look_from, look_at));
	u = unit_vector(cross(vec3(0, 1, 0), w));
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

void	esc_hook(void *ptr)
{
	mlx_t	*mlx;

	mlx = ptr;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static t_color	get_pixel_color(mlx_image_t	*img, t_scene *scene, int x, int y)
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

void	render(t_image image, t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_color		color;
	int			x;
	int			y;

	mlx = mlx_init(image.width, image.height, "miniRT", true);
	if (!mlx)
		return ;
	img = mlx_new_image(mlx, image.width, image.height);
	if (!img)
		return ;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_image_to_window(mlx, img, 0, 0);
	y = 0;
	while (y < image.height)
	{
		x = 0;
		while (x < image.width)
		{
			color = get_pixel_color(img, scene, x, y);
			mlx_put_pixel(img, x, y, color_to_pixel(color));
			x++;
		}
		y++;
	}
	mlx_loop_hook(mlx, esc_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
