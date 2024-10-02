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

static void free_shape_list(t_list *list, int fd)
{
	t_list *next;
	
	while (list != NULL)
	{
		next = list->next;
		if (list->type == CYLINDER)
			free_cylinder(list->d.cylinder);
		else if (list->type == SPHERE)
			free(list->d.sphere);
		else if (list->type == PLANE)
			free(list->d.plane);
		free(list);
		list = next;
	}
	close (fd);
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

	data = new_cylinder(info.pos, vec3(info.v1, info.v2, 0), info.orien, info.color);
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
	if (info.id == ID_PLANE)
		init_plane(list, info, id);
	if (info.id == ID_SPHERE)
		init_sphere(list, info, id);
	if (info.id == ID_CYLINDER)
		init_cylinder(list, info, id);
	(*id)++;
}

static int handle_info(t_scene *scene, t_camera *camera, t_image *image, int fd)
{
	t_parse	info;
	int		id;

	id = 0;
	info.original = "";
	while (info.original)
	{
		info.original = get_next_line(fd);
		if (check_valid(&info))
		{
			if (set_info(&info) == 1)
				return (1);
			if (info.id == ID_CAMERA)
				*camera = init_camera(info.pos, info.orien, *image, info.v1);
			if (info.id == ID_AMBIENT)
				init_ambient(scene, info);
			if (info.id == ID_LIGHT)
				init_light(scene, info);
			if (info.id == ID_CYLINDER || info.id == ID_PLANE || info.id == ID_SPHERE)
				init_shape(&scene->objects, info, &id);
			free(info.original);
		}
	}
	return (0);
}

int check_error(int argc, int *fd, char *file)
{
	if (argc != 2)
	{
		ft_printf("Invalid argument count!!!\n");
		return (1);
	}
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		perror(file);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_image		image;
	t_camera	camera;
	t_scene		scene;
	int 		fd;

	if (check_error(argc, &fd, argv[1]) == 1)
		return (1);
	image = init_image(16.0 / 9.0, 1600);
	scene.objects = 0;
	if (handle_info(&scene, &camera, &image, fd) == 1)
	{
		printf("Error parsing!!!\n");
		free_shape_list(scene.objects, fd);
		return (1);
	}
	scene.camera = &camera;
	render(image, &scene);
	free_shape_list(scene.objects, fd);
	return (0);
}
