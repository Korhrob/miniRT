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
#include "../libft/libft.h"
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

static void init_ambient(t_scene *scene, t_parse info)
{
	scene->ambient.color = info.color;
	scene->ambient.strength = info.v1;
}

static void init_light(t_scene *scene, t_parse info)
{
	scene->light.pos = info.pos;
	scene->light.strength = info.v1;
}

static void init_plane(t_list **list, t_parse info, int *id)
{
	t_list	*temp;
	t_plane	*data;
	t_vec3	size;

	size = vec3(INFINITY, INFINITY, INFINITY);
	temp = 0;
	data = new_plane(info.pos, size, info.orien, info.color);
	data->shape.id = *id;
	temp = new_list(data, PLANE);
	list_add(list, temp);
}
static void init_sphere(t_list **list, t_parse info, int *id)
{
	t_list		*temp;
	t_sphere	*data;

	data = new_sphere(info.pos, info.v1, info.color);
	data->shape.id = *id;
	temp = new_list(data, SPHERE);
	list_add(list, temp);
}

static void init_cylinder(t_list **list, t_parse info, int *id)
{
	t_list		*temp;
	t_cylinder	*data;

	data = new_cylinder(info.pos, info.v1, info.v2, info.orien, info.color);
	data->shape.id = *id;
	data->top->shape.id = *id;
	data->bot->shape.id = *id;
	temp = new_list(data, CYLINDER);
	list_add(list, temp);
	temp = new_list(data->top, CYLINDER_CAP);
	list_add(list, temp);
	temp = new_list(data->bot, CYLINDER_CAP);
	list_add(list, temp);
}

static void init_shape(t_list **list, t_parse info, int *id)
{
	printf("id = %d\n", *id);
	if (info.id == ID_PLANE)
	{
		printf("creating plane\n\n");
		init_plane(list, info, id);
	}
	if (info.id == ID_SPHERE)
	{
		printf("creating sphere\n\n");
		init_sphere(list, info, id);
	}
	if (info.id == ID_CYLINDER)
	{
		printf("creating cylinder\n\n");
		init_cylinder(list, info, id);
	}
	(*id)++;
}

static void handle_info(t_scene *scene, t_camera *camera, t_image *image, int fd)
{
	char	*line;
	t_parse	info;
	int		id;

	line = "";
	id = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (check_valid(line) == 0)
		{
			set_info(line, &info);
			if (info.id == ID_CAMERA)
				*camera = init_camera(info.pos, info.orien, *image, info.v1);
			if (info.id == ID_AMBIENT)
				init_ambient(scene, info);
			if (info.id == ID_LIGHT)
				init_light(scene, info);
			if (info.id == ID_CYLINDER || info.id == ID_PLANE || info.id == ID_SPHERE)
				init_shape(&scene->objects, info, &id);
		}
		if (line)
			free(line);
	}
}

int	main(int argc, char **argv)
{
	t_image		image;
	t_camera	camera;
	t_scene		scene;
	int 		fd;

	if (argc != 2)
	{
		// error
		return (1);
	}
	image = init_image(16.0 / 9.0, 400);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	scene.objects = 0;
	handle_info(&scene, &camera, &image, fd);
	render(camera, image, &scene);
	close (fd);
	return (0);
}
