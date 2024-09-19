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
