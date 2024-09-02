#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"
#include "list.h"
#include "sphere.h"

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
	t_point	camera_center = vec3(0, 0, 0);

	t_vec3	viewport_u = vec3(viewport_width, 0, 0);
	t_vec3	viewport_v = vec3(0, -viewport_height, 0);

	t_vec3	pixel_delta_u = v_div(viewport_u, image_width);
	t_vec3	pixel_delta_v = v_div(viewport_v, image_height);

	t_vec3	viewport_ul = vv_sub(camera_center, vec3(0, 0, focal_length));
	viewport_ul = vv_sub(viewport_ul, v_div(viewport_u, 2));
	viewport_ul = vv_sub(viewport_ul, v_div(viewport_v, 2));

	t_vec3	pixel00_loc = vv_sum(viewport_ul, v_mul(vv_sum(pixel_delta_u, pixel_delta_v), 0.5));

	// Object list - fake list for now
	t_list *list;
	list = malloc(sizeof(t_list));
	t_sphere *data = new_sphere(vec3(0, 0, -1), 0.5);
	list->data = data;
	list->next = NULL;
	list->type = SPHERE;

	t_list *list_temp;
	list_temp = malloc(sizeof(t_list));
	t_sphere *data_temp = new_sphere(vec3(0, -100.5, -1), 100);
	list_temp->data = data_temp;
	list_temp->next = NULL;
	list_temp->type = SPHERE;
	list->next = list_temp;

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
			t_point	pixel_center = vvec3(pixel00_loc);
			pixel_center = vv_sum(pixel_center, v_mul(pixel_delta_u, x));
			pixel_center = vv_sum(pixel_center, v_mul(pixel_delta_v, y));

			t_vec3	ray_direction = vv_sub(pixel_center, camera_center);
			t_ray	ray = { camera_center, ray_direction };

			write_color(fd, ray_color(&ray, list));
		}
	}

	close(fd);
	printf("\ndone\n");
}