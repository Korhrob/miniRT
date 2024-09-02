#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"

void displayProgressBar(int progress, int total) {
    int barWidth = 16;  // Width of the progress bar in characters
    float percentage = (float)(progress + 1) / total;  // Calculate the completion ratio
    int position = barWidth * percentage;  // Determine the current position on the bar

    // Print the progress bar
    printf("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < position) printf("#");  // Filled portion of the bar
        else printf(" ");  // Unfilled portion of the bar
    }
    printf("] %d%%\r", (int)(percentage * 100));  // Print the percentage complete and carriage return

    fflush(stdout);  // Flush the output buffer to ensure immediate display
}

int	main(void)
{
	int		fd;
	double	aspect_ratio = 16.0 / 9.0;
	int		image_width = 400;

	int		image_height = (int)((double)image_width / aspect_ratio);
	if (image_height < 1)
		image_height = 1;

	double	focal_length = 1.0;
	double	viewport_height = 2.0;
	double	viewport_width = viewport_height * ((double)image_width / image_height);
	t_point	camera_center = { 0, 0, 0 };

	t_vec3	viewport_u = { viewport_width, 0, 0 };
	t_vec3	viewport_v = { 0, -viewport_height, 0 };

	t_vec3	pixel_delta_u = v_div(&viewport_u, image_width);
	t_vec3	pixel_delta_v = v_div(&viewport_v, image_height);

	t_vec3	temp;
	t_vec3	viewport_ul = vvec3(&camera_center);
	temp = vec3(0, 0, focal_length);
	viewport_ul = vv_sub(&viewport_ul, &temp);
	temp = v_div(&viewport_u, 2);
	viewport_ul = vv_sub(&viewport_ul, &temp);
	temp = v_div(&viewport_v, 2);
	viewport_ul = vv_sub(&viewport_ul, &temp);

	t_vec3	pixel00_loc = vvec3(&viewport_ul);
	temp = vv_sum(&pixel_delta_u, &pixel_delta_v);
	temp = v_mul(&temp, 0.5);
	pixel00_loc = vv_sum(&pixel00_loc, &temp);

	//t_list shapes;
	//list_add(new_sphere(0, 0, -1, 0.5));


	printf("create file\n");
	fd = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		printf("failed to create file\n");
		exit(1);
	}
	close(fd);
	fd = open("image.ppm", O_WRONLY | O_CREAT | O_APPEND);

	dprintf(fd, "P3\n%d %d\n255\n", image_width, image_height);
	printf("rendering...\n");
	
	for (int y = 0; y < image_height; y++)
	{
		displayProgressBar(y, image_height);
		for (int x = 0; x < image_width; x++)
		{
			t_point	pixel_center = vvec3(&pixel00_loc);
			temp = v_mul(&pixel_delta_u, x);
			pixel_center = vv_sum(&pixel_center, &temp);
			temp = v_mul(&pixel_delta_v, y);
			pixel_center = vv_sum(&pixel_center, &temp);

			t_vec3	ray_direction = vv_sub(&pixel_center, &camera_center);
			t_ray	ray = { camera_center, ray_direction };

			t_color	color = ray_color(&ray);
			write_color(fd, color);
		}
	}

	close(fd);
	printf("\ndone\n");

}