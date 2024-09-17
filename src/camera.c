
#include <unistd.h> // close
#include <stdio.h> // printf
#include <math.h> // tan
#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "image.h"
#include "scene.h"
#include "color.h"
#include "../mlx42/include/MLX42/MLX42.h"

t_camera	init_camera(t_point look_from, t_point look_at, t_image image, double fov_degree)
{
	t_camera	camera;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;

	camera.fov_radian = fov_degree * PI / 180.0;
	camera.focal_length = 1;
	camera.viewport_width = 2.0 * tan(camera.fov_radian / (2.0 * camera.focal_length));
	camera.viewport_height = camera.viewport_width * image.aspect_ratio;
	camera.center = vvec3(look_from);
	w = unit_vector(vv_sub(look_from, look_at));
	u = unit_vector(cross(vec3(0, 1, 0), w));
	v = cross(w, u);
	camera.viewport_u = v_mul(u, camera.viewport_width);
	camera.viewport_v = v_mul(v_mul(v, -1), camera.viewport_height);
	camera.pixel_delta_u = v_div(camera.viewport_u, image.width);
	camera.pixel_delta_v = v_div(camera.viewport_v, image.height);
	camera.viewport_ul = vv_sub(camera.center, v_mul(w, camera.focal_length));
	camera.viewport_ul = vv_sub(camera.viewport_ul, v_div(camera.viewport_u, 2));
	camera.viewport_ul = vv_sub(camera.viewport_ul, v_div(camera.viewport_v, 2));
	camera.pixel00_loc = vv_sum(camera.viewport_ul, v_mul(vv_sum(camera.pixel_delta_u, camera.pixel_delta_v), 0.5));
	return (camera);
}

void	esc_hook(void *ptr)
{
	mlx_t	*mlx;
	
	mlx = ptr;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	render(t_camera camera, t_image image, t_scene *scene)
{
	mlx_t	*mlx;
	mlx = mlx_init(image.width, image.height, "miniRT", true);
	if (!mlx)
		return;
	mlx_image_t	*img;
	img = mlx_new_image(mlx, image.width, image.height);
	if (!img)
		return;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_image_to_window(mlx, img, 0, 0);
	// if fail close window, return
	for (int y = 0; y < image.height; y++)
	{
		displayProgressBar(y, image.height);
		for (int x = 0; x < image.width; x++)
		{
			t_point	pixel_center = vvec3(camera.pixel00_loc);
			pixel_center = vv_sum(pixel_center, v_mul(camera.pixel_delta_u, x));
			pixel_center = vv_sum(pixel_center, v_mul(camera.pixel_delta_v, y));

			t_vec3	ray_direction = unit_vector(vv_sub(pixel_center, camera.center));
			t_ray	ray = { camera.center, ray_direction };

			t_color	color = ray_color(&ray, scene);
			int	ir = 255.99 * linear_to_gamma(color.x);
			int	ig = 255.99 * linear_to_gamma(color.y);
			int ib = 255.99 * linear_to_gamma(color.z);
			int a = 255;

			int32_t pixel = (ir << 24 | ig  << 16 | ib << 8 | a);
			mlx_put_pixel(img, x, y, pixel);
		}
	}
	printf("\ndone\n");
	mlx_loop_hook(mlx, esc_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}
