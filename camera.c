
#include <unistd.h> // close
#include <stdio.h> // printf
#include <math.h> // tan

#include "minirt.h"
#include "camera.h"
#include "vector.h"
#include "ray.h"
#include "image.h"
#include "list.h"

t_camera	init_camera(t_image image, double fov_degree)
{
	t_camera camera;

	camera.fov_radian = fov_degree * PI / 180.0;

	camera.focal_length = 1.0;
	// camera.viewport_height = 2.0;
	// camera.viewport_width = camera.viewport_height * ((double)image.width / image.height);
	camera.viewport_height = 2.0 * camera.focal_length * tan(camera.fov_radian / 2.0);
	camera.viewport_width = camera.viewport_height * image.aspect_ratio;
	camera.center = vec3(0, 0, 0);

	camera.viewport_u = vec3(camera.viewport_width, 0, 0);
	camera.viewport_v = vec3(0, -camera.viewport_height, 0);

	camera.pixel_delta_u = v_div(camera.viewport_u, image.width);
	camera.pixel_delta_v = v_div(camera.viewport_v, image.height);

	camera.viewport_ul = vv_sub(camera.center, vec3(0, 0, camera.focal_length));
	camera.viewport_ul = vv_sub(camera.viewport_ul, v_div(camera.viewport_u, 2));
	camera.viewport_ul = vv_sub(camera.viewport_ul, v_div(camera.viewport_v, 2));

	camera.pixel00_loc = vv_sum(camera.viewport_ul, v_mul(vv_sum(camera.pixel_delta_u, camera.pixel_delta_v), 0.5));

	return (camera);
}

void	render(t_camera camera, t_image image, t_list *list)
{
	//dprintf(fd, "P3\n%d %d\n255\n", image_width, image_height);
	printf("rendering...\n");
	for (int y = 0; y < image.height; y++)
	{
		//displayProgressBar(y, image_height);
		for (int x = 0; x < image.width; x++)
		{
			t_point	pixel_center = vvec3(camera.pixel00_loc);
			pixel_center = vv_sum(pixel_center, v_mul(camera.pixel_delta_u, x));
			pixel_center = vv_sum(pixel_center, v_mul(camera.pixel_delta_v, y));

			t_vec3	ray_direction = vv_sub(pixel_center, camera.center);
			t_ray	ray = { camera.center, ray_direction };

			write_color(image.fd, ray_color(&ray, list));
		}
	}
	close(image.fd);
	printf("\ndone\n");
}