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

int	main(void)
{
	t_image		image = init_image(16.0 / 9.0, 1280);
	t_camera	camera = init_camera(vec3(0,5,-15), vec3(0, -2, -1), image, 60);
	t_scene		scene;

	scene.camera = &camera;
	// Object list
	t_list *list = 0;
	t_list *temp = 0;
	{
		t_sphere *data;

		data = new_sphere(vec3(-4.5, -1, 0), 1, vec3(1, 0, 0));
		data->shape.id = 0;
		temp = new_list(data, SPHERE);
		list_add(&list, temp);

		data = new_sphere(vec3(0, 17, -3), 20, vec3(0, 1, 0));
		data->shape.id = 1;
		temp = new_list(data, SPHERE);
		list_add(&list, temp);
	}
	{
		t_plane *data;

		data = new_plane(vec3(0, -2, 0), vec3(10, 10, 10), vec3(0, 1, 0), vec3(1, 1, 1));
		data->shape.id = 2;
		temp = new_list(data, PLANE);
		list_add(&list, temp);

		data = new_plane(vec3(6, 4, 0), vec3(5, 10, 10), vec3(0, 1, 0), vec3(0, 0, 1));
		data->shape.id = 4;
		temp = new_list(data, PLANE);
		list_add(&list, temp);
	}
	{
		t_cylinder	*data;

		data = new_cylinder(vec3(0, -1, 0), vec3(0.5, 1.0, 0.0), vec3(0, 1, 1), vec3(1, 0, 0));
		data->shape.id = 6;
		data->top->shape.id = 6;
		data->bot->shape.id = 6;
		temp = new_list(data, CYLINDER);
		list_add(&list, temp);

		temp = new_list(data->top, CYLINDER_CAP);
		list_add(&list, temp);

		temp = new_list(data->bot, CYLINDER_CAP);
		list_add(&list, temp);

		data = new_cylinder(vec3(2, -1, 0), vec3(0.5, 2.0, 0), vec3(0, 1, 0), vec3(1, 0, 0));
		data->shape.id = 7;
		data->top->shape.id = 7;
		data->bot->shape.id = 7;
		temp = new_list(data, CYLINDER);
		list_add(&list, temp);

		temp = new_list(data->top, CYLINDER_CAP);
		list_add(&list, temp);

		temp = new_list(data->bot, CYLINDER_CAP);
		list_add(&list, temp);

		data = new_cylinder(vec3(-2, -1, 0), vec3(1.0, 1.0, 0.0), vec3(1, 0, 1), vec3(1, 0, 0));
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
	scene.light.pos = (t_point) { 0, 8, 0 };
	scene.light.strength = 1;

	scene.ambient.color = (t_color) { 1, 0, 0 };
	scene.ambient.strength = 0.1;

	render(image, &scene);

	// list_clean
	temp = list;
	t_list *next = list->next;
	while (temp != NULL)
	{
		next = temp->next;
		//printf("type %d\n", temp->type);
		if (temp->type == CYLINDER)
			free_cylinder(temp->d.cylinder);
		else if (temp->type == SPHERE)
			free(temp->d.sphere);
		else if (temp->type == PLANE)
			free(temp->d.plane);
		free(temp);
		temp = next;
	}
}

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
