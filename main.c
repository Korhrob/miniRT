#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"
#include "list.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"
#include "image.h"
#include "camera.h"
#include "scene.h"
#include "get_next_line/get_next_line.h"
#include "parsing.h"

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

int	main(int argc, char **argv)
{
	t_image		image = init_image(16.0 / 9.0, 400);
	t_camera	camera = init_camera(vec3(0,2,-6), vec3(0, -2, -1), image, 45.0);
	t_scene		scene;

	char	*line;
	int 	fd;
	t_parse	info;
	(void)argc;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (check_valid(line))
		{
			info = set_info(line);
		}
		printf("%s", line);
		free(line);
	}
	printf("\n");

	// Object list - fake list for now
	t_list *list = 0;
	t_list *temp = 0;
	{
		t_sphere *data;

		// data = new_sphere(vec3(0, -0.5, -3), 0.5, vec3(1, 0, 0));
		// data->shape.id = 0;
		// temp = new_list(data, SPHERE);
		// list_add(&list, temp);

		// data = new_sphere(vec3(0, -100.5, -3), 98, vec3(0, 1, 0));
		// data->shape.id = 1;
		// temp = new_list(data, SPHERE);
		// list_add(&list, temp);
	}
	{
		t_plane *data;

		data = new_plane(vec3(0, -2, 0), vec3(10, 10, 10), vec3(0, 1, 0), vec3(1, 1, 1));
		data->shape.id = 2;
		temp = new_list(data, PLANE);
		list_add(&list, temp);

		// data = new_plane(vec3(-1, 0, -3), vec3(1, 1, 1), vec3(0, 0, 1), vec3(0, 0, 1));
		// data->shape.id = 4;
		// temp = new_list(data, PLANE);
		// list_add(&list, temp);

		// data = new_plane(vec3(2, -2, -3), vec3(1, 1, 1), vec3(0, -1, 0), vec3(1, 0, 0));
		// data->shape.id = 5;
		// temp = new_list(data, PLANE);
		// list_add(&list, temp);
	}
	{
		t_cylinder	*data;

		data = new_cylinder(vec3(0, -1, 0), 0.5, 1.0, vec3(0, 1, 1), vec3(1, 0, 0));
		data->shape.id = 6;
		data->top->shape.id = 6;
		data->bot->shape.id = 6;
		temp = new_list(data, CYLINDER);
		list_add(&list, temp);

		temp = new_list(data->top, CYLINDER_CAP);
		list_add(&list, temp);

		temp = new_list(data->bot, CYLINDER_CAP);
		list_add(&list, temp);

		data = new_cylinder(vec3(2, -1, 0), 0.5, 2.0, vec3(0, 1, 0), vec3(1, 0, 0));
		data->shape.id = 7;
		data->top->shape.id = 7;
		data->bot->shape.id = 7;
		temp = new_list(data, CYLINDER);
		list_add(&list, temp);

		temp = new_list(data->top, CYLINDER_CAP);
		list_add(&list, temp);

		temp = new_list(data->bot, CYLINDER_CAP);
		list_add(&list, temp);

		data = new_cylinder(vec3(-2, -1, 0), 1.0, 1.0, vec3(1, 0, 1), vec3(1, 1, 0));
		data->shape.id = 8;
		data->top->shape.id = 8;
		data->bot->shape.id = 8;
		temp = new_list(data, CYLINDER);
		list_add(&list, temp);

		temp = new_list(data->top, CYLINDER_CAP);
		list_add(&list, temp);

		temp = new_list(data->bot, CYLINDER_CAP);
		list_add(&list, temp);
	}
	scene.objects = list;
	scene.light.pos = (t_point) { 0, 3, 0 };
	scene.light.strength = 1;

	scene.ambient.color = (t_color) { 1, 1, 1 };
	scene.ambient.strength = 0.2;

	render(camera, image, &scene);
}
