
#include <unistd.h> // close
#include <stdio.h> // printf
#include <math.h> // tan

#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "image.h"
#include "scene.h"

t_camera	init_camera(t_point look_from, t_point look_at, t_image image, double fov_degree)
{
	t_camera	camera;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;

	camera.fov_radian = fov_degree * PI / 180.0;

	//camera.focal_length = 1.0; 
	camera.focal_length = v_len(vv_sub(look_from, look_at));
	camera.viewport_height = 2.0 * camera.focal_length * tan(camera.fov_radian / 2.0);
	camera.viewport_width = camera.viewport_height * image.aspect_ratio;
	camera.center = vvec3(look_from);

	w = unit_vector(vv_sub(look_from, look_at));
	u = unit_vector(cross(vec3(0, 1, 0), w));
	v = cross(w, u);

	// camera.viewport_u = vec3(camera.viewport_width, 0, 0);
	// camera.viewport_v = vec3(0, -camera.viewport_height, 0);
	camera.viewport_u = v_mul(u, camera.viewport_width);
	camera.viewport_v = v_mul(v_mul(v, -1), camera.viewport_height);

	camera.pixel_delta_u = v_div(camera.viewport_u, image.width);
	camera.pixel_delta_v = v_div(camera.viewport_v, image.height);

	//camera.viewport_ul = vv_sub(camera.center, vec3(0, 0, camera.focal_length));
	camera.viewport_ul = vv_sub(camera.center, v_mul(w, camera.focal_length));
	camera.viewport_ul = vv_sub(camera.viewport_ul, v_div(camera.viewport_u, 2));
	camera.viewport_ul = vv_sub(camera.viewport_ul, v_div(camera.viewport_v, 2));

	camera.pixel00_loc = vv_sum(camera.viewport_ul, v_mul(vv_sum(camera.pixel_delta_u, camera.pixel_delta_v), 0.5));

	return (camera);
}

void	render(t_camera camera, t_image image, t_scene *scene)
{
	printf("rendering...\n");
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

			write_color(image.fd, ray_color(&ray, scene));
		}
	}
	close(image.fd);
	printf("\ndone\n");
}